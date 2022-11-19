# Simple Service Oriented Game Engine _"Shoe"_

## Focus areas
* Multithreaded entity component system.
* Good, service oriented API for external tools.
* Highly modular architecture with configurable "plugin" dependencies.
* Web based editor using modern web technologies (NodeJs+React/Vue?)
* UWP based editor as well?
* ZeroMQ communication (cross-thread/inter-process?)
* NoSQL based asset database (MongoDB/Redis?)
* WebGL rendering via Emscripten.

### Future ideas
- Physics engine based on Box3D or some other available library?
- Scripting system?
- Renderer improvements?

---

## Stage 1 - **Done** 29.9.2018
- First working prototype of ECS and OpenGL rendering.

  **Goal:** Proof of Concept and project kickoff.

## Stage 2 - **Done** 15.11.2018
- Add entity transformation gizmos (ImGuizmo).
- Add entity and scene creation (ImGui). **[postponed]**
- Raycast mouse picking.
- More components?
- More systems?
- Improve input handling?

  **Goal:** Implement test bench for entity manipulation.

## Stage 3 
- Convert to WebGL using Emscripten.

  **Goal:** Render viewport in a web browser and accept input.

## Stage 4
- Implement web editor controls (entity list, entity editor, etc.)

  **Goal:** Web based test bench for entity manipulation.
