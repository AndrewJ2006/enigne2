# Engine2

My first C++ game engine.  
I am no longer expanding this project, as I’ve moved on to more efficient designs that are rapildy growing.

### Overview

Engine2 is a lightweight experimental C++ game engine built around **OpenGL**.  
It combines rendering, physics, and procedural terrain to provide a simple sandbox for experimenting with game engine concepts.  

---

### Key Features
- **OpenGL-based rendering**
- **Multiple libraries integrated** for graphics, physics, and math
- **JSON parsing** for loading geometry files
- **PhysX physics engine** for realistic collisions and interactions
- **Procedural terrain** generation using Noise
- **Two camera modes**
  - Free-fly camera  
  - First-person style walking/jumping camera  
- **Player movement mechanics**
  - **Walk:** Arrow keys  
  - **Jump:** Spacebar  
  - **Fly:** `E` (up), `Q` (down)  
  - **Open doors:** `F`
  - **Change Cameras** `C`
- **Collision handling** (player vs. world and objects)

---

## Build

### Prerequisites
- C++17 or later  
- CMake 3.16+  
- OpenGL 3.3+  
- Libraries used:  
  - [GLFW](https://www.glfw.org/)  
  - [GLAD](https://glad.dav1d.de/)  
  - [GLM](https://github.com/g-truc/glm)  
  - [PhysX](https://github.com/NVIDIAGameWorks/PhysX)  
  - [stb](https://github.com/nothings/stb)  
  - [FastNoiseLite](https://github.com/Auburn/FastNoiseLite)  
  - A JSON parsing library (e.g., [nlohmann/json](https://github.com/nlohmann/json))  
---
### Build Instructions

- git clone https://github.com/AndrewJ2006/engine2.git
- cd engine2
- mkdir build && cd build
- cmake ..
- cmake --build .
### Run
- ./Engine2

---

<img width="1915" height="1029" alt="Screenshot 2025-09-04 185131" src="https://github.com/user-attachments/assets/b982c363-f4a9-43ce-ac53-6a845ebf2b09" />
<img width="1913" height="1028" alt="Screenshot 2025-09-04 184822" src="https://github.com/user-attachments/assets/124befbc-cbf2-428c-a338-18f5157a0e72" />
<img width="1914" height="1026" alt="Screenshot 2025-09-04 184729" src="https://github.com/user-attachments/assets/f19116c2-3ff2-4654-9d1a-50f267f307e6" />
