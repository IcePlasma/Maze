#ifndef DEFINE_H
#define DEFINE_H
//All of the defined constants are here.

//Ascii characters for maze pieces.
#define LEFT_DOWN_CORNER 187
#define RIGHT_DOWN_CORNER 201
#define LEFT_UP_CORNER 188
#define RIGHT_UP_CORNER 200
#define T_UP 202
#define T_DOWN 203
#define T_LEFT 185
#define T_RIGHT 204
#define VERTICAL 186
#define HORIZONTAL 205

//Ascii representation of pieces in the maze.
#define DOWN_CAP 208
#define UP_CAP 210
#define LEFT_CAP 181
#define RIGHT_CAP 198
#define CROSS 206
#define NONE 219
//Cardinal direction representations as numbers
#define NORTH 1
#define SOUTH 4
#define EAST 2
#define WEST 8
//Used to show that a space has treasure in it.
#define TREASURE 16
//Used to show which space is the entrance.
#define ENTRANCE 32
//Used to show which space is the exit.
#define EXIT 64
//Used to show that a space is a dead end.
#define DEAD_END 128
//Dimensions of the maze.
#define MAP_SIZE_X 75
#define MAP_SIZE_Y 75

#endif