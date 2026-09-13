# IP-001 — Establish the C++ Build and Debug Loop

| Field | Value |
| --- | --- |
| Roadmap milestone | [R01](../roadmap.md) |
| Status | Complete |
| Implementation owner | User; agent provides setup assistance, explanation, review, and checks unless asked to implement |
| Depends on | No earlier implementation; directory rename and Git setup are complete |
| Resume at | Plan complete; continue with [IP-002](IP-002-console-tank-grid.md) when the user starts it |

## Outcome

Build and debug a small C++20 executable that reports a tank's state before and after a movement command. Establish a repeatable terminal build/run workflow and a usable debugger. The purpose is a dependable native development loop and the first game-related C++ code.

This plan does not create a game engine, install graphics libraries, or require a complete console game.

## Completion criteria

- A fresh build directory can configure and compile the executable using documented commands.
- The Surface executable targets ARM64; if temporarily using another architecture, explicitly record the limitation rather than claiming the native target passed.
- The program shows a tank at an initial position, applies one bounded movement change, and prints the resulting state predictably.
- A debug session can stop before the state change and step through it while inspecting the position.
- An invalid command-line input, if command-line input is introduced in this plan, produces a clear error and unsuccessful exit status. Do not add an argument parser solely to satisfy this optional case.
- Build/run evidence and debugger reporting state are recorded. Unreported manual debugger checks do not prevent continuing.

## 1. Confirm the development environment

**Build:** After the user renames/reopens the folder, inspect available C++ tools before changing the machine. Identify the operating system and host architecture, compiler and supported target, build system, and debugger. Use the current official setup documentation for the chosen toolchain.

On the Snapdragon Surface, prefer a supported MSVC ARM64 target toolchain and CMake. Compiler tools may require a developer shell; absence from the ordinary terminal's PATH does not prove they are uninstalled. Choose exact generator, architecture, and debugger settings from what is actually installed.

Read-only discovery examples for PowerShell:

```powershell
Get-CimInstance Win32_Processor | Select-Object Name, Architecture
Get-Command cmake, cl, clang++, ninja -ErrorAction SilentlyContinue
```

These discovery commands do not install anything. If tools are missing, ask the agent for a focused setup procedure based on current official documentation. Record the selected tools and versions, and verify the target compiler rather than relying only on the terminal process architecture.

**Context:** The compiler translates source files; the linker assembles an executable from compiled objects and libraries. CMake generates build instructions for a selected toolchain. A debugger consumes executable/debug information. These are separate responsibilities.

**Check:** Identify a supported way to compile and debug Windows ARM64. Record missing tools and an actionable next step if setup is incomplete.

**Checkpoint:** Toolchain route recorded; no engine dependency decision is needed.

**Recorded discovery (2026-09-12):** The host is Windows 11 25H2 build 26200.9445 on ARM64; both the OS and VS Code 1.137.0 processes are native ARM64. No Visual Studio installation, MSVC/Clang compiler, CMake, Ninja, MSBuild, or native debugger was found. The selected route is native MSVC targeting ARM64, CMake with a Visual Studio generator, and the Microsoft C++ debugger in VS Code. Install the Visual Studio C++ build tools with the ARM64 compiler tools, Windows 11 SDK, and CMake tools for Windows, plus the Microsoft C/C++ and CMake Tools VS Code extensions. After installation, repeat discovery in the matching ARM64 developer environment and record actual versions and target output before completing this step.

**Installed verification (2026-09-12):** Visual Studio Community 2026 18.10.0 is installed with MSVC 19.51.36257, CMake 4.3.1-msvc1, MSBuild 18.10.1.42706, and Windows SDK 10.0.26100.0. Developer-shell variables and compiler paths confirm native ARM64 host and ARM64 target tools. CMake selects `Visual Studio 18 2026` as its default generator and also provides Ninja. VS Code 1.137.0 has Microsoft C/C++ 1.34.4 and CMake Tools 1.24.42. The Windows PowerShell effective default policy is `Restricted`, so direct invocation of `Launch-VsDevShell.ps1` requires a process-scoped bypass, a `CurrentUser` policy such as `RemoteSigned`, or use of the Developer Command Prompt; this does not invalidate the toolchain verification.

## 2. Create the smallest buildable project

**Build:** Create a CMake project rooted at `projects/` and `projects/exercises/01-tank-state/main.cpp`. Define one executable target, `tank_state`, with C++20 required and compiler extensions disabled. Keep generated build files under a dedicated root-level `build/` directory. Add ignore rules for generated output after the actual generator is selected.

Start with one source file that prints a recognizable message and returns success. Do not add classes, custom allocators, engine modules, or test dependencies yet.

**Context:** Learn the role of `main`, includes, the standard library, compilation diagnostics, and exit status. Understand why compiler settings belong to the target and why generated files stay separate from source.

**Check:** Configure, build, and run from the terminal. Record the exact working commands. Generator-independent command shapes are:

```text
cmake -S . -B build/<preset-or-target> <generator-and-toolchain-options>
cmake --build build/<preset-or-target> --config Debug
```

These contain placeholders and are not ready-to-run commands. Executable location depends on the chosen generator. Resolve it in the implementation session and document the actual command.

**Checkpoint:** One working executable and repeatable commands. This is a useful stopping point even if later steps remain pending.

**Recorded verification (2026-09-12):** From the repository root in Developer PowerShell, `cmake -S projects -B build/windows-arm64 -G "Visual Studio 18 2026" -A ARM64` configured successfully, `cmake --build build/windows-arm64 --config Debug` built the Debug target, and `.\build\windows-arm64\Debug\tank_state.exe` printed `Tank state exercise` with exit code `0`. `dumpbin /headers` reported `AA64 machine (ARM64)`. The root `/build/` directory is ignored by Git.

## 3. Represent and update tank state

**Completed (2026-09-13):** `TankState` contains an owned string name and integer coordinates. `moveTank(TankState&, int, int)` mutates the original state, while `printTankState(const TankState&)` observes it without copying or mutation. ARM64 Debug builds run successfully and print `(2, 3)`, `(3, 3)`, and `(1, 2)` in sequence, verifying positive and negative movement. Both the user and agent observed the final output.

**Build:** Replace the initial message with a small `TankState` value containing a name and integer grid position. Print its initial state, apply a movement operation through a function, and print the result. Use standard-library facilities and automatic storage/ownership; no manual allocation is needed.

Keep the operation deterministic. For example, starting at `(2, 3)` and moving one cell right should result in `(3, 3)`. Choosing an equivalent small example is fine.

**Context:** Introduce structs, initialization, `std::string`, value copying, references, and `const` through the function signatures. Explain which function changes the state and which only observes it. Do not introduce inheritance for this model.

**Check:** Build and compare the before/after output to the intended operation. Try a second movement case such as a zero movement or a negative direction. Use the simplest check that makes a wrong result visible; a test framework is unnecessary here.

**Checkpoint:** Small state model and functions work; record the cases actually checked.

## 4. Debug a state transition

**Completed (2026-09-13):** VS Code CMake Tools built and launched the ARM64 Debug target with symbols. A breakpoint stopped before the first movement with `tank` at `(2, 3)`. The user stepped into `moveTank`, inspected its stack frame and arguments `deltaX = 1`, `deltaY = 0`, observed `x` change to `3`, and returned to `main` with the state at `(3, 3)`. The earlier run also showed the second transition to `(1, 2)` and exit code `0`.

**Build:** Configure a debugger for the selected toolchain, using workspace-relative paths. Set a breakpoint before movement, inspect the position, step into the function, and inspect the changed result.

If an agent runs this check, record its actual evidence. Otherwise provide the user with the short checklist above. The user may continue without reporting the observation.

**Context:** Explain debug symbols, breakpoints, stack frames, stepping, and the difference between a build error and incorrect runtime behavior only as needed during this check.

**Check:** A reported successful check identifies the debugger/target and the observed transition. If no result is reported, record `Unreported`; do not infer success from later progress.

**Checkpoint:** Debug configuration exists or its remaining setup is documented. Avoid turning this step into an assessment of proficiency.

## 5. Make the loop repeatable

**Completed (2026-09-13):** Added a short exercise README with the exact ARM64 configure, build, run, expected-output, and VS Code CMake Tools debug workflow. From Developer PowerShell, the user configured a new `build/ip001-repeatability-arm64` directory, built Debug without reported warnings, ran the executable with the expected three positions, and verified `AA64 machine (ARM64)` using `dumpbin`. The root `/build/` ignore rule covers the fresh generated tree.

**Build:** Add a short exercise README with exact configure/build/run/debug instructions and expected output. Use CMake presets if they reduce repeated options; keep machine-specific paths out of shared presets. Ensure generated files are excluded from version control.

**Check:** Configure into a second fresh build directory and build/run there to check that instructions do not depend on stale generated state. No deletion is required for this check. Inspect warnings and address relevant ones. Check the resulting target architecture using the selected toolchain's appropriate inspection facility.

**Checkpoint:** Update this plan, its index, and the [Progress Log](../progress-log.md). Record verification scope and any unresolved ARM64/debugger limitation. Do not commit or push automatically.

## State and verification

| Step | Implementation status | Agent/automated evidence | Manual reporting state |
| --- | --- | --- | --- |
| 1. Environment | Complete | Visual Studio Community 2026 18.10.0; MSVC 19.51.36257 for ARM64 using `HostARM64/ARM64`; CMake 4.3.1-msvc1; MSBuild 18.10.1.42706; Windows SDK 10.0.26100.0; VS Code C++ and CMake extensions installed | Confirmed: user showed Developer PowerShell discovering CMake, MSVC, and Ninja; Clang is absent and is not required for the selected route |
| 2. Buildable project | Complete | Configure and Debug build succeeded; executable printed `Tank state exercise`, returned `0`, and was verified as `AA64 machine (ARM64)` | Confirmed: user supplied terminal output for configure, build, run, and exit code |
| 3. Tank state | Complete | ARM64 Debug build succeeded; output showed `(2, 3)`, `(3, 3)`, and `(1, 2)` | Confirmed: user and agent observed the expected transitions |
| 4. Debug transition | Complete | VS Code CMake Tools built and launched the ARM64 Debug target with symbols; breakpoint, stack frame, arguments, step-into behavior, and state changes were observed | Confirmed: user supplied screenshots showing `(2, 3)` to `(3, 3)`, the later `(1, 2)` state, and exit code `0` |
| 5. Repeatability | Complete | Fresh ARM64 configure and Debug build succeeded without reported warnings; expected output and `AA64 machine (ARM64)` were verified; generated tree is ignored | Confirmed: user supplied terminal screenshots for configure, build, run, and architecture inspection |

The initial C++ source, CMake target, ignored build tree, and verified Windows ARM64 Debug executable now exist. VS Code settings cover document viewing and the CMake source directory; no checked-in `launch.json` or `tasks.json` is required for the verified CMake Tools workflow.

## Resume and follow-up

IP-001 is complete. The next milestone is R02, Console game model, now covered by [IP-002 — Playable Console Tank Grid](IP-002-console-tank-grid.md). Its implementation remains pending until the user initiates the first step.
