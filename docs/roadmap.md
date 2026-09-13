# Roadmap

This is the long-term sequence, not a pre-generated backlog. Generate implementation plans on demand using [Plan Generation Instructions](plan-generation-instructions.md). [Project Overview](project-overview.md) owns goals and constraints; [Progress Log](progress-log.md) owns current state.

R01 is complete; R02–R10 remain planned. A completion result includes a runnable artifact, enough documentation to use it again, and honest verification records. Manual results may remain unreported without blocking progress.

| ID | Milestone | Useful completion result |
| --- | --- | --- |
| R01 | Native C++ development loop | A small game-themed executable built, run, and debugged through a repeatable command-line workflow |
| R02 | Console game model | A playable console tank-grid exercise with movement, commands, collisions, and a win/lose loop |
| R03 | Portable window and rendering foundation | A sprite/input/audio smoke sample with early Windows ARM64, Linux x86-64, and Android ARM64 build/runtime evidence |
| R04 | Playable 2D engine | A packaged tank arena with sprites, tilemap, collisions, sound, basic HUD/menu, restart, and editable game data |
| R05 | Authoring and fast iteration | A second arena made through content and gameplay changes; CLI validation, asset reload, selected scripting, and generated inspection |
| R06 | Bounded 3D world | An angled-view environment with meshes, cameras, basic lighting, picking, collision, and a recorded device benchmark |
| R07 | Mixed content and extension proof | The 2D game displayed interactively in a 3D screen, a 3D menu preview, and one second-language native module |
| R08 | Vehicle playground | A vehicle with suspension, steering, drivetrain, terrain collision, and movable obstacles in a small test course |
| R09 | Terrain and traction experiments | One measured improvement at a time in surface grip, slip, load effects, and selected deformation behavior |
| R10 | Incremental delivery and server runtime | A local chunk-update demonstration, followed by an offscreen server execution/export proof; thin client remains out of scope |

## R01–R02: C++ through small working programs

Introduce the compiler/linker model, source/header boundaries, values and types, control flow, functions, structs, standard containers, references, constness, ownership, resource lifetime, and error handling as work requires them. Practice the debugger with actual program state and meaningful failures.

Keep the console game small. Do not require an ECS, allocator framework, templates library, scripting runtime, or graphics layer to exercise fundamentals. Reuse useful game rules later, while allowing the initial representation to be replaced when requirements change.

The first plan is [IP-001](implementation-plans/IP-001-cpp-build-and-debug-loop.md). Future plan numbers are allocated when generated.

## R03–R04: First engine and portability proof

Validate dependencies and native targets before deep integration. Build window/input/lifecycle handling, a small sprite renderer, a fixed-step simulation loop, assets, simple collision, audio, and minimal UI behavior. Separate game code from reusable runtime code without over-generalizing.

Establish at least a CLI build/run path, actionable diagnostics, selective module boundaries, an asset manifest, and a performance capture convention. Run small physical-device checks early; unavailable devices remain visible evidence gaps rather than assumed successes.

## R05: Improve the development experience

Select the scripting runtime using a small typed gameplay example and device/footprint evidence. Add reload rules, content validation, reusable object templates, scene persistence, and property metadata for generated inspection. Reuse external content editors before investing in custom authoring UI.

The second arena is evidence that game creation no longer requires changing engine internals for ordinary content changes. Keep the original sample runnable. Agent access uses the same documented operations as human tooling.

## R06–R07: Extend into 3D and composition

Introduce transforms, projections, depth, basic materials and lighting, model import, scene picking, and 3D collision in a bounded scene. Compare device frame times at explicitly recorded settings.

Render-to-texture and input-coordinate mapping enable mixed content. Prove the native extension boundary with one concrete integration, not a universal multi-language runtime. Strengthen interfaces where actual callers reveal a need.

## R08–R09: Simulation as a measured specialty

Integrate or implement general rigid-body behavior according to a recorded decision. Add vehicle features incrementally and expose parameters for tuning. Use controlled tests for suspension, steering, braking, stability, and terrain interaction.

Advanced tire/soil modeling is an experimental track with scoped hypotheses and observable results. Reorder individual experiments according to priorities and evidence. Do not treat a mature off-road simulation's fidelity as one milestone-sized feature.

## R10: Delivery options

Begin with local manifests, content-addressed chunks, cache behavior, version compatibility, and an interrupted-update test. Build on the earlier asynchronous asset interface.

Then prove server execution with injected input, offscreen frames, and audio/export boundaries. Encoder/transport integration may be a selected adapter, with hosting and client work planned separately. Keep ordinary local games independently usable.

## Practices that grow throughout

- Native portability checks and device-specific input/lifecycle behavior.
- Selective runtime packaging and size reports.
- Focused correctness tests and repeatable benchmark scenes.
- Readable project files, stable identifiers, and schema validation.
- CLI access, structured diagnostics, runtime inspection, and capture.
- Documented ownership, resource lifetime, save/asset versioning, and dependency boundaries.

Milestones may be split or reordered when implementation evidence warrants it. Preserve stable identifiers, record significant changes, and generate only the next useful plan. No calendar estimates are imposed before implementation pace and scope are known.
