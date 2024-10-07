# Cub3D

Cub3D is a 42 school team project to create a dynamic view inside a 3D maze. Using the [MiniLibX library](https://github.com/42Paris/minilibx-linux), we must implement raycasting in the style of the famous [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D) game, the first true FPS in video game history.

## Status

NA

## Clone

Clone the repository including the MiniLibX submodule:

```sh
git clone https://github.com/Josip2504/cub3d.git
```
## Comple and Run

There are two versions of the program, the mandatory part and the bonus part. The bonus part adds wall collision, a minimap, and the ability to rotate the view by moving the mouse.

To compile the mandatory part, cd into the cloned directory and:
```sh
make
```
Note: you may need to make fclean to switch between the mandatory and bonus compilations (working on a fix for this!).

To run the program:
```sh
./cub3d <path/to/map.cub>
```
The program takes a map file as an argument. Maps are available in the maps directory. There are good maps which the program should run smoothly with, and bad maps which the program should reject. For example:

- `./cub3d maps/good/library.cub` should run.

- `./cub3d maps/bad/filetype_wrong.buc` should print an error and abort.

## Controls

Controls for movement and rotation are:

- `W`: move forward
- `S`: move backward
- `A`: strafe left
- `D`: strafe right
- `left arrow`: rotate left
- `right arrow`: rotate right
