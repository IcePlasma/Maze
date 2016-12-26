#ifndef DEFINE_H
#define DEFINE_H
//All of the defined constants are here.

//Ascii characters for maze pieces.
#define RIGHT_DOWN_CORNER "\u2554"
#define LEFT_DOWN_CORNER "\u2557"
#define RIGHT_UP_CORNER "\u255A"
#define LEFT_UP_CORNER "\u255D"
#define T_UP "\u2569"
#define T_DOWN "\u2566"
#define T_LEFT "\u2563"
#define T_RIGHT "\u2560"
#define VERTICAL "\u2551"
#define HORIZONTAL "\u2550"

//Ascii representation of pieces in the maze.
#define DOWN_CAP "\u2568"
#define UP_CAP "\u2565"
#define LEFT_CAP "\u2561"
#define RIGHT_CAP "\u255E"
#define CROSS "\u256C"
#define NONE "\u2554"
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
#define TOTAL_SIZE MAP_SIZE_X * MAP_SIZE_Y

#endif