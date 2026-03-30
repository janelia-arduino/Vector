# Changelog

## Unreleased

## 1.4.0 - 2026-03-30

- Declared the library explicitly header-only and removed the stub source file.
- Added optional access checks for `operator[]()`, `at()`, `front()`, and
  `back()` via `VECTOR_ENABLE_BOUNDS_CHECKS` or a custom
  `VECTOR_ACCESS_CHECK(condition)` hook.
- Expanded native tests to cover bounds-check hooks, cross-type assignment
  truncation, and invalid external-storage setup.
- Hardened repo tooling so local scripts resolve the correct project root even
  when `PIXI_PROJECT_ROOT` points at the sibling repository.
- Changed the default release-check matrix to representative `uno` and `pico`
  builds instead of a Teensy-centered default.

## 1.3.0 - 2026-03-30

- Added Pixi-managed development tasks for formatting, testing, and PlatformIO
  example builds.
- Added repository tooling for version sync, release checks, and formatting of
  embedded code blocks in documentation.
- Added native test coverage for both the documentation tooling and the Vector
  container behavior.
- Fixed PlatformIO packaging so the library builds correctly when installed as a
  dependency.
- Removed the undeclared `Streaming.h` dependency from examples and verified the
  Pico example build with Pixi and PlatformIO.
- Added const `front()` and `back()` overloads, clamped externally supplied
  storage sizes to capacity, and fixed iterator equality across distinct
  containers.
