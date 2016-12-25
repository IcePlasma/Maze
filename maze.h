#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "windows.h"
#include "disjSet.h"
using namespace std;




class maze
{
	public:
		//Output function for the maze.
		void outputMaze();
		maze();
		~maze();
	private:
		//Keeps track of what space is ucrrently being looked at.
		int* currentSpace;
		disjSet* mazeySet;
		//Returns a random direction between NORTH, SOUTH, EAST, and WEST
		char randDir();
		//Determines if a direction is valid for breaking down a wall.
		bool detValidDir(char);
		//Keeps track of what direction the program is going in relative to the maze.
		char direction;
		//Used to change colors in output function.
		HANDLE consoleHandle;
		//Changes the color of text based on the left four bits in the character passed to it.
		void changeColor(char*);
		//Converts the right four bits in the character passed to it into an ascii character that is a maze piece.
		char codeToPiece(char);
		//Converts directions like NORTH and SOUTH into values that can be used to move around the maze array.
		int convertDir(char);
		//Returns the reverse of the direction passed to it.
		char reverseDir(char);
		//Generates the maze.
		void startMaze();
		//adds (MAP_SIZE_X + MAP_SIZE_Y) / 7 treasures to tthe maze in random locations.
		void addTreasures();
		//This function sets the starting values for traerseMaze() and calls traverseMaze().
		void solveMaze();
		//Completes a recursive depth first traversal of the maze and marks dead ends as being dead ends.
		void traverseMaze(char);
		//Checks if there is a wall between the current space and the space that is in the direcion that is passed to it.
		//Also checks if that space is a dead end.
		bool traversable(char);
		//Checks if the curent spot is part of a dead end.
		bool checkSpot(char&);

};

#endif