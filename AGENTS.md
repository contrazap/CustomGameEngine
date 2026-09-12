# Agent Instructions

## Purpose and authority

This repository supports user-led implementation of C++ programs, games, and a portable custom game engine. The user normally writes the implementation. Provide planning, explanations, hints, debugging, review, and appropriate verification. Implement code when requested; do not interpret a request to resume, explain, or review as permission to implement the next feature.

User instructions in the current conversation take precedence over this workflow. Do not introduce approval gates for routine authorized work. Do not rename the project, initialize Git, commit, or push unless requested. The initial directory rename and Git setup are reserved for the user.

## User-paced plan steps

Treat implementation-plan steps as user-paced. When a step is completed or verified, state its result and identify the next step by name, but do not provide instructions, implementation details, starter code, or commands for that next step unless the user explicitly says they are starting it or asks for its instructions. Wait for the user to initiate each upcoming step. Read-only reconciliation and required checkpoint updates may still be performed without advancing implementation.

## Reading order

At the beginning of relevant project work:

1. Read [Engineering Practice Profile](docs/engineering-practice-profile.md).
2. Read the current-state section of [Progress Log](docs/progress-log.md).
3. Read the active implementation plan linked there and inspect relevant working files and Git status, if a repository exists.
4. Follow relevant links to [Project Overview](docs/project-overview.md), [Roadmap](docs/roadmap.md), and [Architecture Decisions](docs/architecture-decisions/README.md). Do not load all historical plans and logs by default.
5. Before generating or substantially revising a plan, read [Plan Generation Instructions](docs/plan-generation-instructions.md).

Check for more local instructions when working in subdirectories. If recorded state disagrees with files, reconcile the discrepancy before treating work as complete. A missing record is not evidence that the user did not do the work.

## Checkpoints and records

Update the active plan and Progress Log at meaningful checkpoints: completed steps, verification results, significant blockers or decisions, requested pauses, and the end of an active work session when state changed. Do not generate an entry for every conversation or tool call.

Record concise evidence: affected step, change, command/result when relevant, environment, remaining uncertainty, and exact next action. Record Git revision and dirty-worktree context when available. Never fabricate command results, commits, device access, or manual confirmation.

Maintain separate implementation and verification states. Manual verification may be **unreported**, **confirmed**, or **issue reported**. User progression does not imply a passing manual check. Unreported manual checks do not block progression or require repeated questions. A milestone may be complete with explicitly documented manual evidence gaps; avoid claiming that all device or user acceptance checks passed.

On resume, inspect changes since the last checkpoint. Checkpoints are written during active work; there is no guarantee of a write during an abrupt interruption and no background tracking service.

## Verification

Use the smallest set of checks that addresses the change's actual risks. Run incremental builds and focused tests first. Broaden to integration, platform, visual, or performance checks when shared behavior, device compatibility, or milestone acceptance requires them. Do not rerun unchanged checks without a reason.

Verify behavior and meaningful boundaries, not private implementation details. A successful compile does not prove runtime correctness; a host build does not prove another target runs. Use sanitizers and analysis where supported and appropriate. When tools or devices are unavailable, record exactly what remains unverified and provide a short reproducible check for the user.

Keep controls, game feel, visual quality, audio quality, and physical-device observations available for user review without requiring a report for each step. Treat unreported checks as evidence gaps to revisit during relevant debugging, not presumed causes.

## Documentation discipline

- Use stable `IP-NNN` implementation plan and `AD-NNN` architecture decision identifiers. Never recycle them.
- Keep all internal links relative so directory renames remain safe.
- Keep one authoritative home for each fact; reference it elsewhere.
- Do not add unrelated personal history or technology background to project plans.
- Keep the Engineering Practice Profile reusable and independent of this project's technologies.
- Record significant technical choices as proposed, accepted, or superseded; distinguish recommendations from confirmed measurements.
- Do not generate the complete long-term backlog. Generate the next useful plan on demand.
- Evolve folder structure when navigation or history size warrants it, preserving identifiers and references.
