# Crimson Vector

FPS játékmotor C nyelven, OpenGL + SDL2 alapokon.

## Technológiák

- **C (C99)** — fő programozási nyelv
- **OpenGL** — fixed-function 3D renderelés
- **SDL2** — ablakkezelés, input, OpenGL context
- **GLAD** — OpenGL function loader
- **CMake** — build rendszer (Windows + Linux)

## Funkciók

- First-person kamera (egér alapú yaw/pitch)
- WASD mozgás, gravitáció, ugrás
- Box-alapú 3D világ renderelés
- Fényforrás (ambient + diffúz)
- Crosshair HUD
- Respawn rendszer
- Start-to-finish versenyidő mérő

## Build

**Linux:**
```bash
mkdir build && cd build
cmake ..
make
```

**Windows (MSYS2 / ucrt64):**
```bash
mkdir build && cd build
cmake .. -G "Unix Makefiles"
make
```

## Struktúra

```
src/
├── main.c          # Belépési pont, game loop
├── renderer.c/h    # OpenGL renderelés
├── player.c/h      # Játékos mozgás, fizika, időmérő
├── camera.c/h      # First-person kamera
├── world.c/h       # Világ adatstruktúra (dobozok)
├── collision.c     # AABB ütközésvizsgálat (WIP)
├── math3d.c/h      # Vec3, Mat4 matematika
└── shader.c        # Shader kezelés (WIP)
```

## Státusz

Aktív fejlesztés alatt. Tervezett következő lépések: modern OpenGL pipeline (VBO/VAO/shaderek), teljes ütközésvizsgálat, textúrázás.
