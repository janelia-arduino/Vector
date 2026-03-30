#!/usr/bin/env python3
"""Run clang-format over the repository's C/C++ and Arduino sources."""

from __future__ import annotations

import argparse
import difflib
import os
import subprocess
import sys
from pathlib import Path


def _project_root() -> Path:
    script_root = Path(__file__).resolve().parents[1]
    env_root = os.environ.get("PIXI_PROJECT_ROOT")
    if env_root:
        resolved = Path(env_root).resolve()
        if (resolved / "tools").resolve() == script_root / "tools":
            return resolved
    return script_root


def _source_files(root: Path) -> list[Path]:
    roots = ("src", "test", "examples")
    suffixes = {".h", ".hpp", ".c", ".cc", ".cpp", ".ino"}
    paths: list[Path] = []
    for rel in roots:
        base = root / rel
        if not base.exists():
            continue
        for path in sorted(base.rglob("*")):
            if path.is_file() and path.suffix in suffixes:
                paths.append(path)
    return paths


def _run_clang_format(path: Path, *, inplace: bool) -> subprocess.CompletedProcess[str]:
    cmd = ["clang-format", str(path)]
    if inplace:
        cmd.insert(1, "-i")
    return subprocess.run(cmd, text=True, capture_output=True, check=False)


def _format(root: Path) -> int:
    for path in _source_files(root):
        completed = _run_clang_format(path, inplace=True)
        if completed.returncode != 0:
            sys.stderr.write(completed.stderr)
            return int(completed.returncode)
        print(path.relative_to(root))
    return 0


def _check(root: Path) -> int:
    failed = False
    for path in _source_files(root):
        original = path.read_text(encoding="utf-8")
        completed = _run_clang_format(path, inplace=False)
        if completed.returncode != 0:
            sys.stderr.write(completed.stderr)
            return int(completed.returncode)
        formatted = completed.stdout
        if formatted != original:
            failed = True
            print(f"Needs formatting: {path.relative_to(root)}")
            diff = difflib.unified_diff(
                original.splitlines(True),
                formatted.splitlines(True),
                fromfile=str(path.relative_to(root)),
                tofile=str(path.relative_to(root)),
            )
            sys.stdout.writelines(diff)
    return 1 if failed else 0


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(prog="clang_format.py")
    parser.add_argument(
        "command",
        choices=("format", "check"),
        help="Apply formatting or verify formatting.",
    )
    args = parser.parse_args(argv)

    root = _project_root()
    if args.command == "format":
        return _format(root)
    return _check(root)


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
