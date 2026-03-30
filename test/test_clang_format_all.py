#!/usr/bin/env python3
"""Regression tests for embedded doc block formatting."""

from __future__ import annotations

import importlib.util
import sys
import tempfile
import unittest
from pathlib import Path


def _load_clang_format_all():
    module_path = Path(__file__).resolve().parents[1] / "tools" / "clang_format_all.py"
    spec = importlib.util.spec_from_file_location("clang_format_all", module_path)
    if spec is None or spec.loader is None:
        raise RuntimeError(f"Failed to load module from {module_path}")

    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


clang_format_all = _load_clang_format_all()


class ClangFormatAllDocBlockTests(unittest.TestCase):
    maxDiff = None

    def setUp(self) -> None:
        self._tmpdir = tempfile.TemporaryDirectory()
        self.root = Path(self._tmpdir.name)
        (self.root / ".clang-format").write_text(
            "BasedOnStyle: LLVM\n"
            "IndentWidth: 2\n"
            "AllowShortFunctionsOnASingleLine: None\n",
            encoding="utf-8",
            newline="",
        )

    def tearDown(self) -> None:
        self._tmpdir.cleanup()

    def _format_doc(self, relative_path: str, text: str) -> tuple[str, int]:
        path = self.root / relative_path
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8", newline="")
        original = clang_format_all._read_text_preserve_newlines(path)
        return clang_format_all._format_embedded_blocks(path, original)

    def test_org_formats_supported_cpp_block_with_header_args(self) -> None:
        original = (
            "* Example\n\n"
            "#+BEGIN_SRC cpp :results none\n"
            "int main(){return 0;}\n"
            "#+END_SRC\n\n"
            "After text.\n"
        )
        expected = (
            "* Example\n\n"
            "#+BEGIN_SRC cpp :results none\n"
            "int main() {\n"
            "  return 0;\n"
            "}\n"
            "#+END_SRC\n\n"
            "After text.\n"
        )

        formatted, changed = self._format_doc("README.org", original)

        self.assertEqual(expected, formatted)
        self.assertEqual(1, changed)

    def test_org_leaves_unsupported_language_unchanged(self) -> None:
        original = (
            "* Example\n\n"
            "#+BEGIN_SRC python\n"
            "print(1)\n"
            "#+END_SRC\n"
        )

        formatted, changed = self._format_doc("README.org", original)

        self.assertEqual(original, formatted)
        self.assertEqual(0, changed)

    def test_markdown_formats_fenced_cpp_block(self) -> None:
        original = (
            "# Example\n\n"
            "```cpp title=\"demo\"\n"
            "int main(){return 0;}\n"
            "```\n"
        )
        expected = (
            "# Example\n\n"
            "```cpp title=\"demo\"\n"
            "int main() {\n"
            "  return 0;\n"
            "}\n"
            "```\n"
        )

        formatted, changed = self._format_doc("README.md", original)

        self.assertEqual(expected, formatted)
        self.assertEqual(1, changed)

    def test_markdown_preserves_list_indentation(self) -> None:
        original = (
            "- Example:\n\n"
            "  ~~~cpp\n"
            "  int main(){return 0;}\n"
            "  ~~~\n"
        )
        expected = (
            "- Example:\n\n"
            "  ~~~cpp\n"
            "  int main() {\n"
            "    return 0;\n"
            "  }\n"
            "  ~~~\n"
        )

        formatted, changed = self._format_doc("notes.md", original)

        self.assertEqual(expected, formatted)
        self.assertEqual(1, changed)

    def test_formatting_is_idempotent(self) -> None:
        original = (
            "```cpp\n"
            "int main(){return 0;}\n"
            "```\n"
        )

        formatted_once, changed_once = self._format_doc("README.md", original)
        formatted_twice, changed_twice = self._format_doc("README.md", formatted_once)

        self.assertNotEqual(original, formatted_once)
        self.assertEqual(1, changed_once)
        self.assertEqual(formatted_once, formatted_twice)
        self.assertEqual(0, changed_twice)


if __name__ == "__main__":
    unittest.main()
