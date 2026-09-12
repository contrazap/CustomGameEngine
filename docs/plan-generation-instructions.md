# Plan Generation Instructions

Generate actionable implementation plans for this project on demand. Apply the [Engineering Practice Profile](engineering-practice-profile.md) faithfully: practical outcomes, user-led implementation, concise domain explanations, and proportional verification.

## Inputs and preparation

1. Read the current state in [Progress Log](progress-log.md), the active plan, and relevant working files. Inspect Git status if a repository exists.
2. Read relevant sections of [Project Overview](project-overview.md), [Roadmap](roadmap.md), and [Architecture Decisions](architecture-decisions/README.md).
3. Identify the next useful result, prerequisites actually present, and unresolved choices that affect that result. Do not infer completed work or device verification from intent.
4. Use current official documentation when selecting toolchain versions, dependencies, or platform-specific commands. Inspect installed tools before proposing installation or environment changes.
5. Resolve ordinary scoped choices with stated assumptions. Ask only about missing information that materially changes the work; keep independent planning moving.

## Scope and sequence

- Generate one implementation plan by default. Keep future work in the Roadmap until requested or needed.
- Use the next unused `IP-NNN` identifier and a descriptive kebab-case filename: `IP-002-console-tank-grid.md`, for example. Allocate identifiers only when creating plans.
- Aim for one useful outcome in a handful of independently resumable steps. Split the plan if unrelated outcomes or substantial unknowns accumulate.
- Teach C++ through the required implementation where practical. Use a focused standalone exercise if graphics or engine infrastructure would obscure the concept.
- Favor a working skeleton followed by incremental behavior. Avoid large tutorial sequences, complete supplied solutions, quizzes, and required reflection.
- Keep engine implementation, sample game behavior, tooling, and platform work distinguishable without forcing a separate plan for every tiny task.
- Use source files, stable data formats, CLI commands, and existing content tools to make results accessible to agents and humans.

## Required plan contents

Start from the [Implementation Plan Template](templates/implementation-plan.md), adapting sections to the task rather than filling them mechanically.

Include:

1. Identifier, title, roadmap milestone, status, ownership, dependencies, and resume pointer.
2. Concrete outcome, scope boundaries, and observable acceptance criteria.
3. Brief unfamiliar concepts introduced at their point of use, with focused references when needed.
4. Ordered steps specifying what to change, expected behavior, and a suitable verification checkpoint.
5. Exact commands once the toolchain/environment is known. Label illustrative or environment-dependent commands clearly; do not present guesses as ready-to-run instructions.
6. User checks for subjective or inaccessible device behavior, kept short and optional to report.
7. A compact current-state table and links to relevant evidence and decisions.

Do not duplicate the entire device table, long-term vision, or standard workflow in each plan. Link to their authoritative documents.

## Status model

Plan or step status:

- **Pending:** not started.
- **In progress:** active work.
- **Implemented:** intended changes exist; relevant checks are incomplete.
- **Verified:** scoped agent/automated checks passed; manual reporting state is tracked separately.
- **Blocked:** a concrete obstacle prevents this work; identify independent work if available.
- **Complete:** scoped work and suitable verification are finished, or explicitly accepted with documented limitations. Do not imply that every device or manual check passed.

Implementation and verification are separate dimensions. A useful verification entry includes check, environment, revision or file state, result, and scope. A code change invalidates prior results only where it affects their conclusions.

Manual state is **unreported**, **confirmed**, or **issue reported**. Passing to the next step does not confirm a manual check. Unreported manual checks are not blockers. Known failures remain visible and should be addressed or explicitly deferred with rationale.

## Verification design

- Begin with the smallest check that can establish the expected behavior. Use build diagnostics, focused tests, and controlled runtime cases.
- Test relevant boundary and error behavior. Avoid brittle tests of private structure or tests that simply restate the implementation.
- Add automated tests when repeatability and risk justify their maintenance. Do not add a test framework just to assert trivial scaffolding output.
- Use broader regression checks for foundational changes and milestones. Device claims require device evidence.
- For performance work, specify scene/workload, resolution, quality, power conditions, duration, and the metric being evaluated. Preserve a reproducible baseline.
- When a check cannot run, state the limitation and provide a practical reproduction procedure. Never turn missing access into a claim of success.

## Plan maintenance and handoff

After generation, validate local links, add the plan to [Implementation Plans](implementation-plans/README.md), and update the active-plan pointer in the Progress Log if it becomes current. Do not mark implementation started just because a plan exists.

During execution, update step state and checkpoints after meaningful progress. Rewrite the resume pointer to the exact next action. Keep detailed historical evidence in the Progress Log and reference it from the plan.

If scope changes, update the plan and briefly record why. Preserve earlier evidence with its original context. Significant architecture changes require an `AD-NNN` record; ordinary local implementation choices do not.

Archive completed plans or historical logs only when navigation becomes difficult. Keep identifiers, links, and a short index. Add subsystem documentation when a real subsystem becomes hard to understand through code and decisions alone.
