# AD-001 — Initial Engine Direction

- **Status:** Accepted working direction; supporting library selections remain provisional.
- **Date:** 2026-09-12
- **Related work:** [Project Overview](../project-overview.md), [Roadmap](../roadmap.md)

## Context

The engine should support 2D, angled and general 3D, mixed UI/world content, and later vehicle simulation. It should build natively for the reference devices, keep shipping games lean, support rapid authoring and agents, and leave room for later cloud delivery. The user will implement most features while acquiring C++ and domain experience.

## Decision

Use C++20 as the working core-language direction. Start with small game-related programs, then reusable runtime code and playable samples. Prefer clear ownership and focused components; do not start with a large framework.

Evaluate Luau as the first gameplay scripting runtime when scripting becomes useful. Lua is an alternative. Defer a custom language until concrete limitations justify its compiler, debugger, and tooling costs.

Evaluate SDL3 for platform services and bgfx for graphics portability. Neither dependency is adopted or installed yet. Verify Windows ARM64, Linux x86-64, and Android ARM64 requirements with actual build/runtime evidence before committing deeply. In particular, SDL GPU alone is not assumed to cover every Android graphics requirement.

Select runtime modules at build time by default, with optional dynamic extensions where justified. Expose versioned C-compatible interfaces for cross-language modules using opaque handles, explicit ownership, and compatible data layouts. Build an actual second-language example later rather than implementing every binding now.

Make the development CLI and shared tooling APIs first-class interfaces. MCP can be an adapter later. Authoritative scenes and configuration remain readable and versionable, while runtime assets may be optimized generated formats.

Own the scene model, gameplay API, asset and packaging contracts, rendering behavior, and tooling integration. Use libraries for mature supporting subsystems where this accelerates usable results. Keep focused replacement boundaries; implement one provider first. General physics, advanced UI, and compression providers are not selected by this decision.

## Alternatives and reasoning

Rust can deliver comparable native performance and stronger memory/concurrency checks in safe code. C++ is the working choice for direct integration with the likely native graphics and physics ecosystem. This is an integration judgment, not a claim that Rust cannot meet the targets.

A custom scripting language could provide close engine integration but would expand scope before ordinary gameplay requirements are understood. Luau's gradual typing and analysis tools fit the intended iteration workflow, subject to embedding and footprint checks.

Writing all supporting libraries would increase implementation work before the first playable result. Using them behind selected boundaries retains ownership of the engine's design while keeping replacement possible. Replacing a provider may still change capabilities or behavior.

## Consequences and revisit conditions

- C++ requires explicit ownership practices, diagnostic tooling, and appropriate runtime checks.
- Dependency support must include the actual target architectures; operating-system support alone is insufficient.
- Shipping module selection and asset dependency tracking require deliberate build/pipeline work.
- Dynamic plugin hot reload, threading, custom allocators, and custom languages remain separate decisions.
- Cloud foundations are interfaces for assets, input, rendering, and state; hosting and thin-client implementation are outside early milestones.
- Revisit language or provider choices if native target support, measured footprint/performance, integration effort, or user preference changes materially.

No performance target or dependency compatibility has been verified yet. Reference documentation is linked in the Project Overview.
