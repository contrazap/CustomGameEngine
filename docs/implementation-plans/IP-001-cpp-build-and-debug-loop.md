# IP-001 — Establish the C++ Build and Debug Loop

| Field | Value |
| --- | --- |
| Roadmap milestone | [R01](../roadmap.md) |
| Status | Pending |
| Implementation owner | User; agent provides setup assistance, explanation, review, and checks unless asked to implement |
| Depends on | No earlier implementation; directory rename/Git setup are user-managed |
| Resume at | Step 1: inspect the native toolchain and select a supported build/debug route |

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

## 2. Create the smallest buildable project

**Build:** Create a root CMake project and `exercises/01-tank-state/main.cpp`. Define one executable target, `tank_state`, with C++20 required and compiler extensions disabled. Keep generated build files under a dedicated `build/` directory. Add ignore rules for generated output after the actual generator is selected.

Start with one source file that prints a recognizable message and returns success. Do not add classes, custom allocators, engine modules, or test dependencies yet.

**Context:** Learn the role of `main`, includes, the standard library, compilation diagnostics, and exit status. Understand why compiler settings belong to the target and why generated files stay separate from source.

**Check:** Configure, build, and run from the terminal. Record the exact working commands. Generator-independent command shapes are:

```text
cmake -S . -B build/<preset-or-target> <generator-and-toolchain-options>
cmake --build build/<preset-or-target> --config Debug
```

These contain placeholders and are not ready-to-run commands. Executable location depends on the chosen generator. Resolve it in the implementation session and document the actual command.

**Checkpoint:** One working executable and repeatable commands. This is a useful stopping point even if later steps remain pending.

## 3. Represent and update tank state

**Build:** Replace the initial message with a small `TankState` value containing a name and integer grid position. Print its initial state, apply a movement operation through a function, and print the result. Use standard-library facilities and automatic storage/ownership; no manual allocation is needed.

Keep the operation deterministic. For example, starting at `(2, 3)` and moving one cell right should result in `(3, 3)`. Choosing an equivalent small example is fine.

**Context:** Introduce structs, initialization, `std::string`, value copying, references, and `const` through the function signatures. Explain which function changes the state and which only observes it. Do not introduce inheritance for this model.

**Check:** Build and compare the before/after output to the intended operation. Try a second movement case such as a zero movement or a negative direction. Use the simplest check that makes a wrong result visible; a test framework is unnecessary here.

**Checkpoint:** Small state model and functions work; record the cases actually checked.

## 4. Debug a state transition

**Build:** Configure a debugger for the selected toolchain, using workspace-relative paths. Set a breakpoint before movement, inspect the position, step into the function, and inspect the changed result.

If an agent runs this check, record its actual evidence. Otherwise provide the user with the short checklist above. The user may continue without reporting the observation.

**Context:** Explain debug symbols, breakpoints, stack frames, stepping, and the difference between a build error and incorrect runtime behavior only as needed during this check.

**Check:** A reported successful check identifies the debugger/target and the observed transition. If no result is reported, record `Unreported`; do not infer success from later progress.

**Checkpoint:** Debug configuration exists or its remaining setup is documented. Avoid turning this step into an assessment of proficiency.

## 5. Make the loop repeatable

**Build:** Add a short exercise README with exact configure/build/run/debug instructions and expected output. Use CMake presets if they reduce repeated options; keep machine-specific paths out of shared presets. Ensure generated files are excluded from version control.

**Check:** Configure into a second fresh build directory and build/run there to check that instructions do not depend on stale generated state. No deletion is required for this check. Inspect warnings and address relevant ones. Check the resulting target architecture using the selected toolchain's appropriate inspection facility.

**Checkpoint:** Update this plan, its index, and the [Progress Log](../progress-log.md). Record verification scope and any unresolved ARM64/debugger limitation. Do not commit or push automatically.

## State and verification

| Step | Implementation status | Agent/automated evidence | Manual reporting state |
| --- | --- | --- | --- |
| 1. Environment | Pending | Not run | Unreported |
| 2. Buildable project | Pending | Not run | Not applicable |
| 3. Tank state | Pending | Not run | Unreported |
| 4. Debug transition | Pending | Not run | Unreported |
| 5. Repeatability | Pending | Not run | Not applicable |

No C++ source, toolchain configuration, or executable has been created by this plan's generation. The only existing VS Code settings concern document viewing.

## Resume and follow-up

Next action: inspect the available native C++ toolchain after the user has reopened the renamed directory. Do not assume tool installation or Git setup has happened.

The likely next outcome is a small console tank-grid loop with input commands and boundaries, introducing translation-unit separation, containers, and error handling when useful. Generate that plan only when requested or when moving to it is authorized; adapt to actual progress rather than a fixed syllabus.
