*This project has been created as part of the 42 curriculum by adias-do, anferrei.*

# cub3D

## Description

cub3D is a 3D maze renderer built in C using the miniLibX graphics library, inspired by Wolfenstein 3D — the first true First Person Shooter in history. The program reads a `.cub` scene file describing a map, textures, and colors, then renders a first-person view of the maze using **raycasting**: a technique that simulates 3D perspective by casting rays from the player's viewpoint into a 2D grid map.

The project explores: window management, pixel-level image rendering, mathematical raycasting, keyboard event handling, and map parsing with strict error handling.

## Instructions

### Dependencies (Linux)
\```bash
sudo apt-get install libx11-dev libxext-dev libbsd-dev
\```

### Compilation
\```bash
make
\```

### Usage
\```bash
./cub3D map.cub
\```

### Controls
| Key | Action |
|-----|--------|
| W / A / S / D | Move forward / left / back / right |
| ← → | Rotate camera left / right |
| ESC | Quit |

### Map format (.cub)
The scene file must contain, in any order (but map always last):
- `NO / SO / WE / EA` — paths to wall textures for each cardinal direction
- `F r,g,b` — floor color
- `C r,g,b` — ceiling color
- The map itself: only `0` (empty), `1` (wall), `N/S/E/W` (player start + direction)

The map must be fully enclosed by walls. Any misconfiguration causes an explicit error.

## Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — primary reference for the DDA raycasting algorithm
- [Medium: 3D Ray-casting with Cub3D by Abdilah CH](https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a)
- [mcombeau's cub3D reference](https://github.com/mcombeau/cub3D)
- [miniLibX Linux docs](https://harm-smits.github.io/42docs/libs/minilibx)
- [MiniLibX guide by Gontjarow](https://gontjarow.github.io/MiniLibX/)
- [Xlib reference](https://tronche.com/gui/x/xlib/)

### AI usage
Claude (claude.ai) was used throughout this project for: environment setup and debugging (MLX compilation, Makefile fixes), understanding raycasting math concepts, code structure guidance, and README writing. All generated code was reviewed, tested, and understood before integration.

*This project has been created as part of the 42 curriculum by adias-do, anferrei.*

# cub3D

## Description

cub3D is a 3D maze renderer written in C using the MiniLibX graphics library, inspired by *Wolfenstein 3D*. It simulates a first-person perspective in a 2D grid-based map using a technique called **raycasting**.

Instead of rendering true 3D geometry, the program casts rays from the player's position into a 2D map. Each ray travels through the grid (using the DDA algorithm) until it hits a wall, allowing the program to calculate distances and create a 3D illusion.

This project covers:

* Low-level graphics rendering (pixels, images)
* Raycasting and grid traversal (DDA algorithm)
* Event handling (keyboard input)
* Memory management and parsing
* Robust error handling

---

## Current Progress 🚧

* ✅ Map file parsing (`.cub`)
* ✅ Map validation (closed map, player detection)
* ✅ Player initialization (position + direction vectors)
* ✅ Raycasting setup (direction + camera plane)
* ✅ DDA algorithm (ray traversal through grid)

> ⚠️ Rendering of walls (3D projection) is currently in progress.

---

## How Raycasting Works (Simplified)

For each vertical column of the screen:

1. A ray is cast from the player’s position
2. The ray moves through the grid step by step (DDA)
3. When it hits a wall (`1`), the distance is calculated
4. This distance is used to draw a vertical line (wall slice)

This creates the illusion of a 3D world from a 2D map.

---

## Instructions

### Dependencies (Linux)

```bash
sudo apt-get install libx11-dev libxext-dev libbsd-dev
```

### Compilation

```bash
make
```

### Usage

```bash
./cub3D map.cub
```

---

## Controls (Planned)

| Key           | Action |
| ------------- | ------ |
| W / A / S / D | Move   |
| ← →           | Rotate |
| ESC           | Exit   |

---

## Map Format (.cub)

The configuration file includes:

* `NO / SO / WE / EA` → wall textures
* `F r,g,b` → floor color
* `C r,g,b` → ceiling color
* Map layout:

  * `1` → wall
  * `0` → empty space
  * `N/S/E/W` → player start + orientation

The map must be:

* Fully enclosed by walls
* Rectangular (after normalization)
* Contain exactly one player

---

## Resources

* https://lodev.org/cgtutor/raycasting.html
* https://harm-smits.github.io/42docs/libs/minilibx
* https://ambientcg.com/
* https://github.com/mlaraki/cub3D_leaks_maps_tester
---

## AI Usage

Claude (claude.ai) was used for:

* Understanding raycasting concepts
* Structuring the parsing logic
* Debugging segmentation faults and memory leaks
* Incremental development guidance
