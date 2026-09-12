# AD-002 — Documentation and Continuity

- **Status:** Accepted
- **Date:** 2026-09-12
- **Related work:** [Engineering Practice Profile](../engineering-practice-profile.md), [Plan Generation Instructions](../plan-generation-instructions.md)

## Context

The project will grow over a long period and span many implementation sessions. The user wants practical plans, resumable work, fast proportional verification, and minimal reporting overhead. Agents should find relevant state without loading all history. Folder renames and repository moves must not break navigation.

## Decision

Use Markdown as the authoritative planning format, with relative links and stable `IP-NNN` and `AD-NNN` identifiers. Keep a human entry point in the root README and agent instructions in AGENTS.md.

Use Project Overview, Roadmap, Plan Generation Instructions, Implementation Plans, Progress Log, and Architecture Decisions. Maintain a separate reusable Engineering Practice Profile without project-specific technologies or personal background references.

Generate implementation plans on demand. Keep the Progress Log's current-state summary small and write factual checkpoints at meaningful boundaries. Git owns code history once initialized; documentation owns intent, rationale, evidence, and the resume pointer.

Track implementation separately from verification. Manual reporting states are unreported, confirmed, and issue reported. Missing manual reports do not block progression and are not presumed failures. Later debugging may revisit relevant unreported checks as evidence gaps.

Configure rendered Markdown viewing in workspace settings, with preview-lock instructions as a fallback. Do not require a documentation website or duplicate plain-text copies.

## Consequences and revisit conditions

- Agents must reconcile recorded state with working files when resuming, especially after interruptions.
- Checkpoint updates happen during active sessions; no background tracking or guaranteed interruption-time write is implied.
- Milestones may retain explicit manual/device evidence gaps without claiming all checks passed.
- Keep indexes and links valid when plans are added or archived.
- Archive history or introduce subsystem indexes only when a fresh agent can no longer find current work and relevant context efficiently.
- A future browser viewer may render the same Markdown sources; it must not create a second authoritative plan store.
