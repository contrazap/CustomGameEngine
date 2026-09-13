# Progress Log

## Current state

- **Phase:** Native C++ development loop complete.
- **Active milestone:** [R01 — Native C++ development loop](roadmap.md), complete; R02 is next but not started.
- **Active plan:** [IP-001 — Establish the C++ Build and Debug Loop](implementation-plans/IP-001-cpp-build-and-debug-loop.md), complete.
- **Resume at:** Await the user's request to generate the next implementation plan for R02, Console game model.
- **User-managed next action:** When ready, request the next implementation plan; no R02 implementation guidance should be given before then.
- **Known blockers:** None. Windows PowerShell currently uses its default `Restricted` execution policy, so launching the developer-shell script from ordinary PowerShell needs a process-scoped bypass, a user-scoped policy change, or the Developer Command Prompt.
- **Latest verification:** From Developer PowerShell, a fresh `build/ip001-repeatability-arm64` tree configured with Visual Studio 18 2026 for ARM64, built Debug without reported warnings, printed `(2, 3)`, `(3, 3)`, and `(1, 2)`, and was identified by `dumpbin` as `AA64 machine (ARM64)`. The generated tree is covered by the root `/build/` ignore rule.
- **Manual reporting:** IP-001 steps 1–5 build, run, architecture, and debugger results are confirmed by the user; document-viewing behavior remains unreported.
- **Open details:** Confirm phone variant, RAM, OS, and actual refresh behavior when Android testing becomes relevant. Record graphics driver/backend capabilities during the portability milestone.
- **Technical decisions:** [AD-001](architecture-decisions/AD-001-initial-engine-direction.md), [AD-002](architecture-decisions/AD-002-documentation-and-continuity.md).

## Recording conventions

Keep the current-state summary above authoritative for resuming. Add short entries below only when meaningful state changes. Update the active plan's step table at the same checkpoint; avoid copying long narratives between documents.

An entry should normally include date, plan/step, result, verification evidence, limitations, and next action. Record environment and Git revision when available. For a dirty worktree, state that evidence applies to working files and identify relevant changes; do not imply it tested only the named commit.

Manual results are **unreported**, **confirmed**, or **issue reported**. Unreported means no observation was recorded, not that testing did not happen. Keep progression independent from optional reporting. Known issues should link follow-up work or carry a clear deferral note.

Do not store large raw logs, binaries, or captures here. Reference evidence artifacts when needed. Once history becomes cumbersome, move older entries into dated archives with an index and preserve useful links.

## Checkpoint history

### 2026-09-13 — IP-001 step 5 and plan complete

- Added `projects/exercises/01-tank-state/README.md` with exact ARM64 configure, build, run, expected-output, and VS Code CMake Tools debug instructions.
- In Developer PowerShell, the user configured the new `build/ip001-repeatability-arm64` directory with Visual Studio 18 2026 targeting ARM64, built Debug without reported warnings, and ran the executable with the expected `(2, 3)`, `(3, 3)`, and `(1, 2)` output. `dumpbin` reported `AA64 machine (ARM64)`.
- `git check-ignore` confirms the root `/build/` rule covers the fresh generated tree. Evidence applies to the working tree at Git revision `6655a52` with the new exercise README and documentation checkpoint edits; no source or build configuration changed.
- IP-001 and R01 are complete with no unresolved ARM64 or debugger limitation. Next action: wait for the user to request the implementation plan for R02, Console game model.

### 2026-09-13 — IP-001 step 5 started

- The user initiated step 5 with one instruction at a time. Reconciled the implementation-plan index status and the active plan's description of existing VS Code settings.
- Added `projects/exercises/01-tank-state/README.md` with the verified ARM64 configure, build, run, expected-output, and VS Code CMake Tools debug workflow. No presets or build configuration were added.
- Environment: clean worktree at Git revision `6655a52` before this documentation checkpoint. No source or build configuration changed.
- Next action: configure into a second fresh build directory using the documented ARM64 command.

### 2026-09-13 — IP-001 step 4 complete

- VS Code CMake Tools built and launched the ARM64 Debug target with symbols and stopped at the first movement breakpoint with `tank` at `(2, 3)`.
- User screenshots confirmed stepping into `moveTank`, its stack frame and arguments `deltaX = 1` and `deltaY = 0`, `x` changing to `3`, and return to `main` with `tank` at `(3, 3)`. An earlier run showed the later `(1, 2)` state and exit code `0`.
- Evidence applies to the working tree at Git revision `51f66a3` with documentation checkpoint edits. Next action: wait for the user to initiate IP-001 step 5, make the loop repeatable.

### 2026-09-13 — IP-001 step 4 started

- Reconciled the active plan's stale state table with the completed step 3 evidence and marked step 4 in progress at the user's request.
- The workspace has no `launch.json`; VS Code CMake Tools launched `build/Debug/tank_state.exe` directly with symbols and stopped on the first movement breakpoint. User screenshots showed the state at `(2, 3)`, `(3, 3)`, and `(1, 2)`, then exit code `0`.
- The `build/CMakeCache.txt` generator platform is `arm64`, confirming that this separate CMake Tools build tree also targets ARM64. Evidence applies to the working tree at Git revision `51f66a3` with documentation checkpoint edits.
- Next action: repeat the debug run, stop before the first `moveTank` call, and step into the function.

### 2026-09-13 — IP-001 step 3 complete

- Implemented a `TankState` aggregate with owned `std::string` name and integer coordinates, a mutating `moveTank(TankState&, int, int)` operation, and a read-only `printTankState(const TankState&)` observer.
- The user built and ran the ARM64 Debug target in Developer PowerShell. An agent repeated the build with the explicit Visual Studio CMake path. Both runs produced `Player is at (2, 3)`, `(3, 3)`, and `(1, 2)` in sequence, covering positive and negative deltas.
- Formatting review found consistent spacing and braces and exactly one final CRLF newline. Git reports that it will normalize the working file to LF when it next touches it; no whitespace error was reported.
- Environment: Git revision `2391617`; evidence applies to a dirty worktree containing the step 3 source, plan/progress checkpoint edits, and the requested `AGENTS.md` CMake-shell instruction.
- Next action: wait for the user to initiate IP-001 step 4, debug a state transition.

### 2026-09-13 — IP-001 step 3 started

- The user selected the native `Visual Studio Community 2026 Release - arm64` CMake kit in VS Code and explicitly started step 3 with one instruction at a time.
- Added a `TankState` aggregate with a string name and integer coordinates, initialized `Player` at `(2, 3)`, and printed that initial state. The user confirmed the ARM64 Debug build and output `Player starts at (2, 3)` from Developer PowerShell.
- Agent-run PowerShell does not inherit the developer-shell `PATH`; `AGENTS.md` now requires agents to use the verified Visual Studio CMake executable directly instead of first retrying a known-failing bare `cmake` command.
- Evidence applies to the dirty worktree at the start of step 3. Next action: add the movement function, then inspect it before calling it.

### 2026-09-12 — IP-001 step 2 complete

- Created the CMake project under `projects/`, the initial `tank_state` source, and a root `/build/` ignore rule.
- In Developer PowerShell, Visual Studio 18 2026 configuration for ARM64 and the Debug build succeeded. The executable printed `Tank state exercise` and returned exit code `0`; `dumpbin /headers` reported `AA64 machine (ARM64)`.
- Environment: Git revision `760fd50`; evidence applies to a dirty worktree containing the new `.gitignore` and `projects/` files, documentation checkpoint changes, and an unrelated modified `.vscode/settings.json`.
- Next action: wait for the user to initiate IP-001 step 3.

### 2026-09-12 — IP-001 step 2 layout started

- Adopted `projects/` as the implementation umbrella, separate from `docs/`; exercises, the future reusable engine, games, and samples remain distinct categories beneath it as they become necessary.
- Verified `projects/CMakeLists.txt` and `projects/exercises/01-tank-state/main.cpp` exist in the intended layout. Both files are empty, so configure/build/run verification is not yet available.
- Step 2 is in progress. Next action: populate the two files, then configure, build, and run `tank_state`.
- The worktree also contains an unrelated modified `.vscode/settings.json`; it was not changed during this verification.

### 2026-09-12 — Step-paced guidance and pause before IP-001 step 2

- The user confirmed in Developer PowerShell that CMake, MSVC, and Ninja are discoverable. Clang is absent and is not required for the selected MSVC route.
- Added a repository instruction requiring agents to wait for the user to initiate each upcoming implementation-plan step before providing its instructions, implementation details, starter code, or commands.
- IP-001 step 2 has not started. Next action: wait for the user to initiate it.
- Environment: Git revision `0adfa66`; evidence applies to the current worktree with documentation changes.

### 2026-09-12 — IP-001 step 1 toolchain verified

- Completed environment confirmation with Visual Studio Community 2026 18.10.0 and the native MSVC/CMake route.
- Evidence: the developer environment reports `VSCMD_ARG_HOST_ARCH=arm64` and `VSCMD_ARG_TGT_ARCH=arm64`; `cl /Bv` identifies MSVC 19.51.36257 for ARM64 from `HostARM64/ARM64`; CMake 4.3.1-msvc1 defaults to the `Visual Studio 18 2026` generator; MSBuild is 18.10.1.42706; the selected Windows SDK is 10.0.26100.0.
- VS Code 1.137.0 has Microsoft C/C++ 1.34.4, CMake Tools 1.24.42, and the C++ development tools dependency installed.
- PowerShell policy check found every explicit scope undefined, producing the Windows PowerShell default effective `Restricted` policy. Verification used a process-only bypass; no persistent execution-policy setting was changed.
- Environment: Git revision `0adfa66`; evidence applies to the current worktree with the IP-001 and Progress Log documentation changes.
- Next action: IP-001 step 2, create and build the smallest CMake project.

### 2026-09-12 — IP-001 step 1 environment discovery

- Selected native MSVC targeting ARM64, CMake with a Visual Studio generator, and the Microsoft C++ debugger in VS Code as the initial Windows route.
- Evidence: Windows 11 25H2 build 26200.9445; OS architecture and PowerShell process architecture both ARM64; VS Code 1.137.0 reports ARM64. `Get-Command` found no MSVC/Clang compiler, CMake, Ninja, Make, or MSBuild; Visual Studio Installer discovery found no Visual Studio installation.
- The Microsoft C/C++ and CMake Tools extensions are also absent. No compiler version or generated executable target can be verified until installation.
- Environment: Git revision `0adfa66`; worktree was clean before this documentation checkpoint.
- Next action: install the selected build tools and extensions, use the ARM64 developer environment, and record the compiler/CMake versions and verified ARM64 target.

### 2026-09-12 — Planning scaffold

- Created the Project Overview, Roadmap, reusable Engineering Practice Profile, Plan Generation Instructions, templates, initial Implementation Plan, Architecture Decisions, and agent entry instructions.
- Added workspace Markdown preview settings and reading instructions. Changes are local to this workspace.
- Preserved user-led implementation, optional manual reporting, on-demand plan generation, and proportional verification as explicit instructions.
- No C++ code, engine dependencies, build outputs, Git repository, or commits were created. No device tests or toolchain checks were run.
- Verification: PowerShell file-link scan passed for 14 Markdown files and 46 local references; `ConvertFrom-Json` parsed `.vscode/settings.json` and an explicit property check confirmed the Markdown association. A text scan found no project references to excluded technology background or fixed workspace paths. Content review confirmed user-led implementation and provisional dependency choices.
- Environment: current Windows/PowerShell workspace; no Git revision exists. Evidence applies to the generated documentation, not engine behavior. The VS Code interface itself was not exercised, so rendered-editor behavior remains unreported.
- Next action: user folder rename/Git setup, then IP-001 step 1. No implementation or device check is marked complete.
