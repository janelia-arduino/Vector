#!/usr/bin/env python3
"""Format (or check) tracked C-family files and embedded doc snippets."""

from __future__ import annotations

import argparse
import re
import subprocess
import sys
import tempfile
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path


_SOURCE_EXTS = {
    ".c",
    ".cc",
    ".cpp",
    ".cxx",
    ".h",
    ".hh",
    ".hpp",
    ".hxx",
    ".ino",
}

_DOC_EXTS = {
    ".md",
    ".org",
}

_CLANG_LANG_TO_EXT = {
    "arduino": "ino",
    "c": "c",
    "cc": "cc",
    "cpp": "cpp",
    "cxx": "cxx",
    "c++": "cpp",
    "cuda": "cu",
    "cu": "cu",
    "h": "h",
    "hh": "hh",
    "hpp": "hpp",
    "hxx": "hxx",
    "ino": "ino",
    "objc": "m",
    "objective-c": "m",
    "objcpp": "mm",
    "objective-c++": "mm",
}


@dataclass(frozen=True)
class EmbeddedBlock:
    content_start: int
    content_end: int
    extension: str


def _repo_root() -> Path:
    return Path(__file__).resolve().parents[1]


def _git_ls_files(root: Path) -> list[Path]:
    proc = subprocess.run(
        ["git", "ls-files"],
        cwd=str(root),
        check=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    if proc.returncode != 0:
        print(proc.stderr, file=sys.stderr)
        raise RuntimeError("Failed to run 'git ls-files'. Are you in a git repo?")

    paths: list[Path] = []
    for line in proc.stdout.splitlines():
        if not line:
            continue
        path = (root / line).resolve()
        if path.suffix.lower() in (_SOURCE_EXTS | _DOC_EXTS) and path.exists():
            paths.append(path)
    return paths


def _read_text_preserve_newlines(path: Path) -> str:
    with path.open("r", encoding="utf-8", newline="") as handle:
        return handle.read()


def _write_text_preserve_newlines(path: Path, text: str) -> None:
    with path.open("w", encoding="utf-8", newline="") as handle:
        handle.write(text)


def _clang_format_bytes(path: Path) -> bytes:
    proc = subprocess.run(
        ["clang-format", "--style=file", str(path)],
        cwd=str(path.parent),
        check=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
    )
    if proc.returncode != 0:
        sys.stderr.buffer.write(proc.stderr)
        raise RuntimeError(f"clang-format failed on {path}")
    return proc.stdout


def _clang_format_text(text: str, extension: str, directory: Path) -> str:
    tmp_path: Path | None = None
    try:
        with tempfile.NamedTemporaryFile(
            mode="w",
            encoding="utf-8",
            newline="",
            suffix=f".{extension}",
            prefix="embedded-clang-format-",
            dir=directory,
            delete=False,
        ) as handle:
            handle.write(text)
            tmp_path = Path(handle.name)

        proc = subprocess.run(
            ["clang-format", "-i", "--style=file", str(tmp_path)],
            cwd=str(directory),
            check=False,
            stderr=subprocess.PIPE,
            text=True,
        )
        if proc.returncode != 0:
            print(proc.stderr, file=sys.stderr, end="")
            raise RuntimeError(f"clang-format failed on embedded block in {directory}")

        return _read_text_preserve_newlines(tmp_path)
    finally:
        if tmp_path is not None:
            tmp_path.unlink(missing_ok=True)


def _leading_whitespace(line: str) -> str:
    return line[: len(line) - len(line.lstrip(" \t"))]


def _split_text_lines(text: str) -> list[str]:
    return text.splitlines(keepends=True)


def _common_whitespace_prefix(strings: Iterable[str]) -> str:
    strings = list(strings)
    if not strings:
        return ""

    prefix = strings[0]
    for value in strings[1:]:
        limit = min(len(prefix), len(value))
        index = 0
        while index < limit and prefix[index] == value[index]:
            index += 1
        prefix = prefix[:index]
        if not prefix:
            break
    return prefix


def _block_indent_prefix(text: str) -> str:
    return _common_whitespace_prefix(
        _leading_whitespace(line)
        for line in _split_text_lines(text)
        if line.strip(" \t\r\n")
    )


def _strip_prefix(text: str, prefix: str) -> str:
    if not prefix:
        return text

    stripped_lines: list[str] = []
    for line in _split_text_lines(text):
        if line.startswith(prefix):
            stripped_lines.append(line[len(prefix) :])
        else:
            stripped_lines.append(line)
    return "".join(stripped_lines)


def _add_prefix(text: str, prefix: str) -> str:
    if not prefix:
        return text

    prefixed_lines: list[str] = []
    for line in _split_text_lines(text):
        if line.strip(" \t\r\n"):
            prefixed_lines.append(prefix + line)
        else:
            prefixed_lines.append(line)
    return "".join(prefixed_lines)


def _lang_to_extension(lang: str) -> str | None:
    cleaned = lang.strip().lower()
    if not cleaned:
        return None
    return _CLANG_LANG_TO_EXT.get(cleaned)


def _org_blocks(text: str) -> list[EmbeddedBlock]:
    begin_re = re.compile(r"^[ \t]*#\+begin_src\b(?P<rest>.*)$", re.IGNORECASE)
    end_re = re.compile(r"^[ \t]*#\+end_src\b", re.IGNORECASE)

    lines = _split_text_lines(text)
    blocks: list[EmbeddedBlock] = []
    offset = 0
    index = 0

    while index < len(lines):
        line = lines[index]
        match = begin_re.match(line.rstrip("\r\n"))
        if match is None:
            offset += len(line)
            index += 1
            continue

        rest = match.group("rest").strip()
        language = rest.split(None, 1)[0] if rest else ""
        extension = _lang_to_extension(language)

        content_start = offset + len(line)
        running_offset = content_start
        end_index = index + 1
        while end_index < len(lines):
            end_line = lines[end_index]
            if end_re.match(end_line.rstrip("\r\n")):
                if extension is not None:
                    blocks.append(
                        EmbeddedBlock(
                            content_start=content_start,
                            content_end=running_offset,
                            extension=extension,
                        )
                    )
                break
            running_offset += len(end_line)
            end_index += 1

        while index < end_index and index < len(lines):
            offset += len(lines[index])
            index += 1
        if index < len(lines):
            offset += len(lines[index])
            index += 1

    return blocks


def _markdown_language(info_string: str) -> str:
    info = info_string.strip()
    if not info:
        return ""
    return re.split(r"[ \t{]", info, maxsplit=1)[0]


def _markdown_blocks(text: str) -> list[EmbeddedBlock]:
    lines = _split_text_lines(text)
    blocks: list[EmbeddedBlock] = []
    offset = 0
    index = 0

    while index < len(lines):
        line = lines[index]
        stripped = line.lstrip(" \t")
        indent_len = len(line) - len(stripped)
        if not stripped:
            offset += len(line)
            index += 1
            continue

        fence_char = stripped[0]
        if fence_char not in ("`", "~"):
            offset += len(line)
            index += 1
            continue

        fence_len = len(stripped) - len(stripped.lstrip(fence_char))
        if fence_len < 3:
            offset += len(line)
            index += 1
            continue

        info = stripped[fence_len:].rstrip("\r\n")
        language = _markdown_language(info)
        extension = _lang_to_extension(language)
        opening_fence = fence_char * fence_len
        content_start = offset + len(line)
        running_offset = content_start
        end_index = index + 1

        while end_index < len(lines):
            end_line = lines[end_index]
            end_stripped = end_line.lstrip(" \t")
            end_indent_len = len(end_line) - len(end_stripped)
            end_fence_len = len(end_stripped) - len(end_stripped.lstrip(fence_char))
            trailing = end_stripped[end_fence_len:].strip(" \t\r\n")

            if (
                end_indent_len <= indent_len
                and end_fence_len >= fence_len
                and end_stripped.startswith(opening_fence)
                and trailing == ""
            ):
                if extension is not None:
                    blocks.append(
                        EmbeddedBlock(
                            content_start=content_start,
                            content_end=running_offset,
                            extension=extension,
                        )
                    )
                break

            running_offset += len(end_line)
            end_index += 1

        while index < end_index and index < len(lines):
            offset += len(lines[index])
            index += 1
        if index < len(lines):
            offset += len(lines[index])
            index += 1

    return blocks


def _embedded_blocks(path: Path, text: str) -> list[EmbeddedBlock]:
    suffix = path.suffix.lower()
    if suffix == ".org":
        return _org_blocks(text)
    if suffix == ".md":
        return _markdown_blocks(text)
    return []


def _format_embedded_blocks(path: Path, text: str) -> tuple[str, int]:
    blocks = _embedded_blocks(path, text)
    if not blocks:
        return text, 0

    changed = 0
    result = text
    for block in reversed(blocks):
        original = result[block.content_start:block.content_end]
        prefix = _block_indent_prefix(original)
        code = _strip_prefix(original, prefix)
        formatted = _clang_format_text(code, block.extension, path.parent)
        final = _add_prefix(formatted, prefix)
        if final != original:
            result = result[:block.content_start] + final + result[block.content_end:]
            changed += 1
    return result, changed


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(prog="clang_format_all.py")
    parser.add_argument(
        "--check",
        action="store_true",
        help="Do not write files; exit non-zero if formatting changes are needed.",
    )
    args = parser.parse_args(argv)

    root = _repo_root()
    files = _git_ls_files(root)

    if not files:
        print("No tracked source or documentation files found.")
        return 0

    needs_format: list[Path] = []
    formatted_source_files = 0
    formatted_doc_files = 0
    formatted_blocks = 0

    for path in files:
        suffix = path.suffix.lower()

        if suffix in _SOURCE_EXTS:
            original = path.read_bytes()
            formatted = _clang_format_bytes(path)

            if original != formatted:
                if args.check:
                    needs_format.append(path)
                else:
                    path.write_bytes(formatted)
                    formatted_source_files += 1
            continue

        if suffix in _DOC_EXTS:
            original = _read_text_preserve_newlines(path)
            formatted, changed_blocks = _format_embedded_blocks(path, original)

            if original != formatted:
                if args.check:
                    needs_format.append(path)
                else:
                    _write_text_preserve_newlines(path, formatted)
                    formatted_doc_files += 1
                    formatted_blocks += changed_blocks

    if args.check:
        if needs_format:
            print("Files need formatting:")
            for path in needs_format:
                try:
                    print(f"  {path.relative_to(root)}")
                except Exception:
                    print(f"  {path}")
            return 1
        print("Formatting OK.")
        return 0

    print(
        "Formatted "
        f"{formatted_source_files} source file(s) and "
        f"{formatted_blocks} embedded block(s) in {formatted_doc_files} doc file(s)."
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
