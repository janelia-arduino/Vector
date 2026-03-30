# Changelog

## Unreleased

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
