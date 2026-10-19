# FdF — 3D Wireframe Renderer

A wireframe renderer in C that turns a grid of height values into a 3D landscape, drawn in **isometric projection**. Graphics are rendered with [MLX42](https://github.com/codam-coding-college/MLX42).

The input is a `.fdf` file: every number is the height (z) of a point on an x/y grid, optionally followed by a colour.

```
0  0  0  0  0
0 10 10 10  0
0 10 20,0xFF0000 10  0
0  0  0  0  0
```

## How it works

1. **Parsing and validation.** The map is read line by line, checked for a consistent width, and converted into a 2D array of points `(x, y, z, colour)`. Hex colours (`,0xRRGGBB`) are parsed per point.
2. **Isometric projection.** Each 3D point is mapped to 2D screen coordinates:

   ```
   screen_x = (x - y) · cos(θ) + offset_x
   screen_y = (x + y) · sin(θ) - z + offset_y
   ```

   The x and y axes are rotated towards the viewer, and the height lifts the point upwards on screen.
3. **Line drawing.** Neighbouring points are connected with **Bresenham's line algorithm**, which uses only integer steps. Colours are interpolated pixel by pixel along each line, giving smooth gradients between points.
4. **Interaction.** Arrow keys move the model; `Esc` or closing the window exits cleanly.

## Build and run

Requires `cmake` and `glfw` for MLX42.

```bash
make
./FDF maps/test_maps/42.fdf
```

| Key | Action |
|---|---|
| Arrow keys | Move the model |
| `Esc` | Quit |

## Project structure

```
src/
├── parser/   # reading and validating the .fdf map, building the point grid
├── render/   # isometric projection, Bresenham lines, colour interpolation
└── fdf/      # entry point, window setup, key handling, error handling
maps/         # test maps
```

Part of the [Codam](https://www.codam.nl/) (42 Network) curriculum.
