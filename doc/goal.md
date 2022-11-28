# Project goals

## Focus areas
* Multithreaded entity component system.
* Service oriented API for external tools.
* Modular architecture with configurable plugin dependencies.
* Web editor (React/Vue).
* UWP/.NET/.NET MAUI editor?
* ZeroMQ communication (cross-thread/inter-process).
* NoSQL based asset database (MongoDB/Redis).
* WebAssembly support / WebGL rendering via Emscripten.

## Future ideas
- Physics engine based on Box3D or some other available library?
- Scripting system?
- Improved renderer?

# Year 2018
*Simple Service Oriented Game Engine, "shoe"*

## Stage 1
- First working prototype of ECS and OpenGL rendering.

  **Goal:** Proof of Concept and project kickoff.

  **Done:** 29.9.2018

## Stage 2
- Add entity transformation gizmos (ImGuizmo).
- Add entity and scene creation (ImGui). **[postponed]**
- Raycast mouse picking.
- More components?
- More systems?
- Improve input handling?

  **Goal:** Implement test bench for entity manipulation.

  **Done:** 15.11.2018

## Stage 3 
- Convert to WebGL using Emscripten.

  **Goal:** Render viewport in a web browser and accept input.

## Stage 4
- Implement web editor controls (entity list, entity editor, etc.)

  **Goal:** Web based test bench for entity manipulation.

# Year 2019~
- Refactoring, minor improvements, *uuttu* branch.

# Year 2022
- Reboot: rewrite build system, add GitHub CI for Windows and Linux.
