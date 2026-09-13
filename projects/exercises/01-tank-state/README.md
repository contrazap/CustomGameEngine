# Tank State Exercise

A small C++20 program that updates and prints a tank's grid position. It is the first exercise in the native C++ build-and-debug workflow.

## Prerequisites

- Visual Studio Community 2026 with the MSVC ARM64 tools and Windows SDK installed.
- A Developer PowerShell for Visual Studio session targeting ARM64.
- VS Code with the Microsoft C/C++ and CMake Tools extensions for debugging.

Run the terminal commands below from the repository root.

## Configure

```powershell
cmake -S projects -B build/windows-arm64 -G "Visual Studio 18 2026" -A ARM64
```

## Build

```powershell
cmake --build build/windows-arm64 --config Debug
```

## Run

```powershell
.\build\windows-arm64\Debug\tank_state.exe
```

Expected output:

```text
Player is at (2, 3)
Player is at (3, 3)
Player is at (1, 2)
```

## Debug in VS Code

1. Open the repository root in VS Code.
2. Run `CMake: Select a Kit` from the Command Palette and select `Visual Studio Community 2026 Release - arm64`.
3. Select the `Debug` build configuration.
4. Set a breakpoint on the first `moveTank` call in `main.cpp`.
5. Run `CMake: Debug` from the Command Palette.
6. At the breakpoint, inspect `tank`, step into `moveTank`, and observe `x` change from `2` to `3`.

CMake Tools may use its workspace build directory instead of `build/windows-arm64`; the selected ARM64 kit and `Debug` configuration determine the debugger target.
