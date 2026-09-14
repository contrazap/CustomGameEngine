# IP-002 — Playable Console Tank Grid

| Field | Value |
| --- | --- |
| Roadmap milestone | [R02 — Console game model](../roadmap.md) |
| Status | In progress |
| Implementation owner | User; agent provides explanations, hints, review, and verification unless asked to implement |
| Depends on | [IP-001](IP-001-cpp-build-and-debug-loop.md), complete; existing C++20 CMake project and verified Windows ARM64 development loop |
| Resume at | Await the user initiating step 4, finish and restart rounds |

## Outcome

A playable, turn-based console exercise: guide a tank through a small grid, avoid walls and mines, and reach extraction. Read a command, update the game state, and print the result. A round ends with a clear win or loss; the player can restart or quit.

Build on the structs, references, constness, and debugging already practiced. Introduce containers, branching, loops, input handling, and source/header separation as the game needs them.

## Scope and working assumptions

- Add `projects/exercises/02-console-tank-grid/` and a separate C++20 executable target, `tank_grid`, in `projects/CMakeLists.txt`. Preserve the existing `tank_state` target and exercise.
- Use one small rectangular arena defined in source, approximately 8 columns by 6 rows, with a known start, walls, at least one mine, and one reachable extraction tile. No external map parser is needed.
- Use integer coordinates: `x` increases rightward, `y` downward, and the upper-left cell is `(0, 0)`. Store terrain separately from the tank's position so moving does not erase map tiles.
- Use portable standard-library console input/output. Commands require Enter; each redraw appends a complete board without terminal clearing or cursor-control APIs.
- The rules below are scoped planning choices. They can be revised with the user during implementation; they do not change the engine architecture in [AD-001](../architecture-decisions/AD-001-initial-engine-direction.md).
- Shooting, enemies, real-time input, graphics, sound, procedural maps, engine modules, manual memory allocation, and new third-party dependencies are outside this plan. Native portability work follows in R03.

## Game contract

| Situation | Expected behavior |
| --- | --- |
| Board display | Distinguish floor `.`, wall `#`, mine `*`, extraction `E`, and tank `T`; print a legend and command help |
| Movement | `w`, `a`, `s`, `d` request exactly one cell up, left, down, or right |
| Wall or outside the grid | Reject movement, preserve position and terrain, and explain the blocked move |
| Floor | Move the tank and continue the round |
| Extraction | Move onto the tile and mark the round won |
| Mine | Move onto the tile and mark the round lost |
| Finished round | Further movement leaves state unchanged; display the outcome and restart/quit choices |
| Restart | `r` restores the initial arena, tank position, and playing status, including during an unfinished round |
| Quit or end of input | `q` or EOF ends the session cleanly with exit code `0` |
| Invalid input | Blank lines, unknown commands, and multiple commands on one line produce a helpful message and leave game state unchanged |

Accept lowercase commands with optional surrounding spaces or tabs. Uppercase support is optional; document it if added. An input stream failure other than ordinary EOF should produce a diagnostic and unsuccessful exit status. A gameplay loss is a normal result, not a process failure.

## Completion criteria

- The Windows ARM64 Debug `tank_grid` executable renders a consistent arena and supports the game contract above.
- The initial layout has a demonstrated route to extraction and a demonstrated route to a mine. Terrain remains intact through movement and restart.
- Bounds are checked before indexing the board; wall and edge attempts cannot put the tank outside a valid traversable cell.
- Win, loss, restart, invalid input, quit, and EOF are exercised with recorded results. Finished rounds cannot continue moving.
- Game rules can be exercised without console input/output through a small source/header boundary and focused repeatable checks.
- The exercise README contains the map legend, controls, rules, exact build/run/check commands, and reproducible win/loss input sequences for the implemented layout.
- The original `tank_state` exercise still builds and produces its documented output. Record any remaining verification gaps separately from implementation status.

## Implementation steps

These steps define the requested plan. Implementation remains pending until the user initiates each step; deliver detailed session guidance at that pace.

Completed and active steps are identified in their headings for at-a-glance navigation: ✅ **Complete** or 🚧 **In progress**. Pending steps have no indicator because implementation proceeds sequentially. The detailed evidence remains in the state table below.

### 1. Display a small tank arena — ✅ Complete

**Build:** Add the new directory, `main.cpp`, and `tank_grid` CMake target with C++20 required and compiler extensions disabled, following the existing target's settings. Begin with one source file. Define the fixed arena, starting position, and a renderer that overlays the tank on terrain. A `std::vector<std::string>` is a suitable initial board representation. Keep rows nonempty and equal in length and choose an in-bounds start on floor. Print the board and legend once, then exit.

**Context:** A container owns a collection of values; each row string owns its characters. Nested iteration visits rows and columns. Rendering observes state rather than modifying the terrain to draw the tank. Grid coordinates and container indices have different signedness, so validate coordinates before converting for indexing.

**Check:** Configure and build using the commands below, then run once. Check row widths, tank placement, legend, and the existence of a safe path to extraction. No movement or input loop is required yet.

**Checkpoint:** The new target displays the initial arena. Record the chosen layout and start in source; keep implementation details there authoritative.

### 2. Apply movement with boundaries and walls — ✅ Complete

**Build:** Introduce a movement command type using `enum class` and a game update function. Compute a candidate position, check the grid bounds, then inspect terrain before committing the move. Return enough information for the caller to describe a moved or blocked result; keep output in the caller. For now, exercise a short fixed sequence from `main`; mines and extraction remain traversable markers until step 4.

**Context:** Scoped enumeration values express a closed set of actions. A `switch` maps actions to direction changes. Checking a proposed state before updating the live state makes rejected operations leave the game unchanged.

**Check:** Exercise all four directions, a wall, and attempts beyond each of the four grid edges. Use a small open test layout where the main arena cannot reach an edge. Confirm rejected moves preserve position and terrain. Build incrementally and inspect one rejected move in the debugger if its behavior is unclear.

**Checkpoint:** Movement rules work independently of keyboard input; record tested boundaries.

### 3. Play through console commands — ✅ Complete

**Build:** Replace the fixed command sequence with a line-based loop using `std::getline`. Parse exactly one supported command after trimming spaces/tabs, then update and redraw. Support movement and `q` now; step 4 adds `r`. Invalid input should display help and request another line without moving. Handle EOF and other stream failures according to the game contract.

**Context:** Parsing converts external text into a valid command before the game sees it. Line-based input gives a clear boundary for rejecting extra text. Distinguish ordinary end of input from an invalid command and from an I/O failure; avoid repeatedly prompting on a failed stream.

**Check:** Run a movement session with successful and blocked moves. Try an empty line, spaces only, an unknown command, and a line such as `ww`; verify state is unchanged. Try a command surrounded by whitespace. Exercise quit and piped input ending without `q`, confirming clean termination instead of an input loop.

**Checkpoint:** The player can navigate the arena and leave the program predictably.

### 4. Finish and restart rounds

**Build:** Add explicit playing, won, and lost states. After a successful move, inspect the destination tile and apply the outcome. Print the final board and a clear outcome message. Ignore movement after a round ends, and support `r` and `q`. Use one initial-state construction path for both startup and restart so all round state resets together.

**Context:** A state machine limits which transitions are valid. Separate the lifetime of a round from the lifetime of the console session: finishing a round still allows another round to start.

**Check:** Reach extraction, attempt another movement, and restart. Repeat for a mine. Restart once during play. Verify position, terrain, and playing status are restored each time. Repeat a known input sequence after restart and confirm the same result.

**Checkpoint:** The exercise has a complete playable win/lose/restart loop. Optional user observation: are symbols, blocked-move messages, and end-of-round choices understandable? Reporting is optional.

### 5. Separate and verify game rules

**Build:** With behavior established, move game state declarations and the public rule operations into `game.h`, and definitions into `game.cpp`; keep console parsing, rendering, and session control in `main.cpp`. Add a header guard and update the target's source list. Keep the interface narrow: initial state, commands, state updates, and observable results are sufficient.

Add a small dependency-free `tank_grid_checks` executable in this exercise, linking the same `game.cpp`. Use explicit failure reporting and a nonzero exit code on failed checks rather than checks that disappear when assertions are disabled. No test framework or reusable engine library is needed.

**Context:** Headers declare the shared interface; separately compiled source files provide definitions that the linker resolves. Each executable has its own `main`. Tests should call the same game rules as the playable program while avoiding terminal interaction.

**Check:** Cover observable behavior: four movement directions, four boundaries, wall rejection, unchanged terrain, extraction and mine outcomes, movement after both outcomes, and restart from playing/won/lost states. Use small controlled layouts for edge cases and the actual initial layout for reset and route checks. Build and run the checks, then run a short console session to catch integration mistakes introduced by the split. Parser/EOF behavior remains covered by the console cases from step 3.

**Checkpoint:** The game remains playable and its rule checks pass independently of console interaction.

### 6. Document and verify the complete exercise

**Build:** Add an exercise README with rules, symbols, commands, Windows ARM64 build/run/check instructions, and concrete win/loss/restart input sequences for the final map. Include the familiar CMake Tools debug route with `tank_grid` selected, linking the earlier exercise where useful.

**Check:** Run the focused rule checks and the documented console sequences, including invalid input, quit, and EOF. Rebuild and run `tank_state` once because the shared CMake file changed. Reuse the verified ARM64 build tree; no second fresh toolchain setup or additional device test is required for this standard-library exercise. Record actual results and any unreported readability/playability observations.

**Checkpoint:** Update this plan, the plan index, the Roadmap milestone status, and the [Progress Log](../progress-log.md). R02 is complete when the scoped behavior and suitable verification are complete, with any remaining manual evidence gaps explicit. The next milestone is R03, Portable window and rendering foundation; wait for the user to request its plan.

## Build and verification commands

These commands use the already verified Visual Studio generator and ARM64 build tree. Run from the repository root in Developer PowerShell. They are planned commands: `tank_grid` becomes available in step 1 and `tank_grid_checks` in step 5; neither exists at plan creation. Agents use the explicit CMake executable required by [AGENTS.md](../../AGENTS.md).

After adding the step 1 target:

```powershell
cmake -S projects -B build/windows-arm64 -G "Visual Studio 18 2026" -A ARM64
cmake --build build/windows-arm64 --config Debug --target tank_grid
.\build\windows-arm64\Debug\tank_grid.exe
```

For incremental work, repeat only the relevant build and run commands. After adding step 5 checks:

```powershell
cmake --build build/windows-arm64 --config Debug --target tank_grid tank_grid_checks
.\build\windows-arm64\Debug\tank_grid_checks.exe
```

From step 3 onward, this input checks rejection followed by EOF; it should print an invalid-command message and exit successfully after consuming the line:

```powershell
'invalid' | .\build\windows-arm64\Debug\tank_grid.exe
$LASTEXITCODE
```

At the final shared-build regression checkpoint:

```powershell
cmake --build build/windows-arm64 --config Debug --target tank_state
.\build\windows-arm64\Debug\tank_state.exe
```

Compare the original exercise's output with its [README](../../projects/exercises/01-tank-state/README.md). Record console transcripts or concise results, not large raw logs. Successful compilation alone does not establish the game rules.

## State and verification

| Step | Implementation status | Agent/automated evidence | Manual reporting state |
| --- | --- | --- | --- |
| 1. Display a small tank arena | Complete | Windows ARM64 Debug build/run exits `0`, prints the expected 8-by-6 arena and legend, and has safe routes to extraction and mine. Focused source whitespace check passes. | Confirmed: user screenshot matches the expected rendered board and legend. |
| 2. Apply movement with boundaries and walls | Complete | Source review plus a warning-free Windows ARM64 Debug build/run confirm candidate-first updates, wall rejection, exit `0`, the final fixed route, mine restoration, and final position `(2, 3)`. Temporary open-board runs covered all four boundaries. | Confirmed: screenshots cover all directions, wall rejection, all four boundaries, the restored arena, and the corrected fixed sequence. |
| 3. Play through console commands | Complete | Warning-free Windows ARM64 Debug builds pass. Scripted runs cover successful movement, wall rejection, empty/spaces/unknown/`ww` rejection, space/tab-padded commands, quit, and piped EOF with exit `0`; source review covers the non-EOF failure branch. A focused rerun passed after correcting the boundary-message typo. | Confirmed: user reports the implementation tested and working. |
| 4. Finish and restart rounds | Pending | Not run | Unreported |
| 5. Separate and verify game rules | Pending | Not run | Unreported |
| 6. Document and verify the complete exercise | Pending | Not run | Unreported |

Planning baseline: Windows/PowerShell, clean worktree at revision `8b40a8b` before plan creation. The existing `tank_state` source and CMake target agree with the completed IP-001 checkpoint. No IP-002 source, build, runtime, or device verification exists yet. Evidence and subsequent checkpoints belong in the [Progress Log](../progress-log.md).

## Resume and follow-up

Steps 1–3 are complete. Await the user initiating step 4, **Finish and restart rounds**. No known blocker prevents continuing, and no later step has started.
