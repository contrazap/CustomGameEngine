# Custom Game Engine

A long-term project to develop C++ expertise by building games and a portable, lean, extensible game engine.

## Start here

- [Project Overview](docs/project-overview.md): destination, constraints, reference devices, and scope.
- [Roadmap](docs/roadmap.md): staged outcomes and the capabilities they introduce.
- [Progress Log](docs/progress-log.md): current state, evidence, and next action.
- [Implementation Plans](docs/implementation-plans/README.md): actionable work generated as needed.
- [Architecture Decisions](docs/architecture-decisions/README.md): decisions and their rationale.

The first plan is [IP-001 — Establish the C++ Build and Debug Loop](docs/implementation-plans/IP-001-cpp-build-and-debug-loop.md). Engine implementation has not started.

## Working with agents

[AGENTS.md](AGENTS.md) is the agent entry point. Planning follows the reusable [Engineering Practice Profile](docs/engineering-practice-profile.md) and project-specific [Plan Generation Instructions](docs/plan-generation-instructions.md).

Useful requests:

- "Resume from the Progress Log. Review the current files before suggesting the next action."
- "Explain IP-001, step 2, and let me implement it."
- "Review my changes and run the checks appropriate to this step."
- "Implement this step for me and explain the relevant decisions."
- "Generate the next implementation plan using the Plan Generation Instructions."
- "Record a checkpoint; I am pausing here."

## Reading Markdown in VS Code

The workspace's [.vscode/settings.json](.vscode/settings.json) configures `.md` files to open in the rendered Markdown editor and disables temporary editor tabs. Markdown link validation is also enabled. These are workspace settings, not global changes.

If your VS Code version does not support the rendered editor association, remove that association and use the built-in preview:

1. Open a Markdown file and press `Ctrl+Shift+V`.
2. Focus the preview and run **Markdown: Toggle Preview Locking** from the Command Palette.
3. Open another document in a separate preview when needed. Locking keeps a preview attached to its document; it does not freeze the contents.

Use **View: Reopen Editor With... → Text Editor** to edit a document as source. If the setting is not recognized, the plans remain readable as plain text. See [VS Code Markdown documentation](https://code.visualstudio.com/docs/languages/markdown).

## Folder and repository setup

These documents use relative local links and no fixed workspace path. You can rename this directory to `CustomGameEngine`, reopen it in VS Code, then create and push your Git repository. No repository has been initialized and no dependencies have been installed as part of creating these plans.

Keep source documents and small reusable test inputs in Git. Once build tooling exists, ignore its generated outputs, local caches, credentials, and machine-specific configuration. Keep bulky benchmark captures outside the ordinary documentation history, with references to relevant evidence in the Progress Log.
