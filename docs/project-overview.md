# Project Overview

## Goal

Develop C++ and game-engine engineering capability through user-led implementation of progressively useful games and a portable custom engine. Produce a usable result at each milestone while retaining a clear path to more demanding rendering and simulation.

## Intended capabilities

- 2D sprites, tilemaps, animation, collision, audio, and games in the style of a classic tank arena.
- A true 3D world viewed through an angled orthographic camera, with depth, picking, and occlusion behavior suitable for top-down games.
- General 3D scenes and later vehicle/object physics, terrain, suspension, drivetrain, and progressively richer traction behavior.
- Mixed content: a 2D game or UI on a screen in a 3D world, and a 3D preview inside a menu.
- Engine-integrated HUD and menu creation, sharing rendering resources with 2D while retaining UI-specific layout and interaction behavior.
- Fast authoring and iteration through readable assets, scripting, live reload, existing content tools, and a small generated inspector.
- Portable builds, selectable modules, and interfaces for extensions implemented in other languages.
- Later incremental asset delivery and a server-rendered streaming runtime. The thin client is a separate project and outside this plan.

The named game styles define directions, not a promise to reproduce those games' internal architecture, scale, or fidelity.

## Engineering principles

1. Build useful increments; keep previous sample games runnable as the engine grows.
2. The user implements by default, supported by agents as described in the [Engineering Practice Profile](engineering-practice-profile.md).
3. Own the engine's public behavior and architecture. Supporting libraries are candidates for reusable subsystems; self-written replacements remain possible where justified.
4. Keep the development distribution capable while making each shipping game select only required runtime modules, dependencies, and assets.
5. Establish portability early through actual builds and smoke tests, then expand platform coverage and polish.
6. Measure on reference devices. Language choice alone does not establish performance, footprint, or compatibility.
7. Prefer CLI-accessible, schema-validated operations and structured results. MCP may wrap those operations later but is not required.
8. Use narrow interfaces where replacement is valuable. Do not build a universal abstraction or multiple providers before there is a concrete use.

## Reference devices and targets

| Device | Native target | Performance objective | Important conditions |
| --- | --- | --- | --- |
| Steam Deck LCD, 64 GB with microSD | Linux x86-64 | 120 FPS rendering benchmark; 60 FPS normal internal-display presentation | Start at 1280 x 800; test actual microSD loading and sustained operation |
| iQOO 7 | Android ARM64 | 60 FPS baseline; 120 FPS stretch for appropriate scenes | Indian Snapdragon 870 model provisionally assumed; exact variant, RAM, OS, and allowed refresh modes remain to be recorded |
| Surface Pro 12-inch, Snapdragon X Plus | Windows ARM64 | 60 FPS baseline | Native ARM64 dependencies and configurable internal rendering resolution |

120 FPS permits approximately 8.33 ms per frame; 60 FPS permits approximately 16.67 ms. These are whole-workload objectives, not measured results. Record scene version, workload, resolution, quality settings, power conditions, and duration with results. Track CPU and GPU times, frame-time distributions, memory, startup, loading stalls, and package size. Rendering and simulation frequencies are separately configurable.

The Deck LCD's internal display is 60 Hz. The Indian iQOO 7 has a 120 Hz display, but application refresh behavior must be verified. Do not count display interpolation as engine-rendered frames. No universal 120 FPS promise applies to arbitrary 3D scenes or advanced terrain simulation.

## Technical direction

- **C++20:** working direction for native engine implementation. Keep ownership explicit, prefer automatic resource cleanup, and introduce concurrency only when useful.
- **Luau:** leading scripting candidate for typed gameplay iteration. Validate embedding, bindings, footprint, and device builds before adopting. Lua remains a comparison candidate. A custom language is deferred.
- **SDL3 and bgfx:** candidates for platform and graphics portability. Validate required device/backend combinations before adoption; do not infer compatibility from a platform list alone.
- **Native modules:** versioned C-compatible boundaries for cross-language integrations; prefer build-time selection for shipping. Dynamic loading and hot reload are separate optional features.
- **Tooling:** a CLI backed by shared APIs; readable source assets and generated optimized runtime assets. Existing tools such as Tiled and Blender may supply content.
- **Physics/UI:** start with scoped engine behavior and evaluate libraries for mature subsystems when needed. No physics or UI dependency is selected yet.

See [AD-001](architecture-decisions/AD-001-initial-engine-direction.md) for rationale and decision status. Recommendations are not evidence of installed or validated toolchains.

## Cloud foundations and deferred infrastructure

Plan stable asset identities, dependency manifests, asynchronous loading, versioned saves, and separation of simulation from presentation. Later evaluate content-addressed chunks, caching, partial availability, and recoverable package updates for small incremental downloads.

Local execution still needs a compatible per-platform runtime and sufficient hardware. Pixel streaming instead needs a server GPU runtime with injected input, audio output, offscreen rendering, and efficient encoder integration. A renderer-free simulation server is a different executable profile.

CDN/provider selection, transport, session orchestration, hosting operations, and the thin client are deferred. Availability on arbitrary devices depends on the selected delivery approach and eventual client support.

## Initial scope and exclusions

Start with the native C++ build/debug loop and a small console game model. Grow into a playable 2D tank arena, then improve authoring and add a bounded 3D scene. Introduce concepts and infrastructure as those results require them.

Do not initially build a large visual editor, custom scripting language, advanced soil simulation, universal plugin marketplace, cloud platform, multiplayer stack, or seamless native-code hot reload. The engine architecture must not require implementing all future features up front.

## References

Reference links were consulted during planning; verify current requirements when selecting dependencies or setting up tools.

- [Steam Deck LCD specifications](https://www.steamdeck.com/en/tech/deck)
- [iQOO 7 India specifications and display notes](https://www.iqoo.com/in/products/iqoo7)
- [Surface Pro 12-inch information](https://support.microsoft.com/en-US/surface/models/surface-pro-12-inch-features)
- [SDL3 documentation](https://wiki.libsdl.org/SDL3/FrontPage)
- [SDL GPU requirements](https://wiki.libsdl.org/SDL3/CategoryGPU)
- [bgfx overview](https://bkaradzic.github.io/bgfx/overview.html)
- [Luau introduction](https://luau.org/getting-started/)
- [Luau compatibility](https://luau.org/compatibility/)
