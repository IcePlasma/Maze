#include "maze.h"
maze::maze()
{

	//handle used for changing text color attributes.
	//consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	currentSpace = new int;
	*currentSpace = rand() % TOTAL_SIZE;

	mazeySet = new disjSet(TOTAL_SIZE, 0);

	mazeySet->changeValue(ENTRANCE, 0);
	mazeySet->changeValue(EXIT, TOTAL_SIZE - 1);

	/*
	//Used for testing.
	for (int x = 0; x < 100; x++)
	{
		mazeySet = new disjSet(TOTAL_SIZE, 0);

		mazeySet->changeValue(ENTRANCE, 0);
		mazeySet->changeValue(EXIT, TOTAL_SIZE - 1);
		startMaze();
		delete mazeySet;
	}
	*/

	//Creates the maze
	startMaze();
	outputMaze();
	solveMaze();
	outputMaze();
}
maze::~maze()
{
	delete currentSpace;
	delete mazeySet;
}

//Sets up conditions for traverseMaze().
void maze::solveMaze()
{
	direction = NULL;
	*currentSpace = 0;
	traverseMaze(NORTH);
}

//Does a recursive depth first traversal of the entire maze and marks all of the dead ends as being dead ends.
void maze::traverseMaze(char sourceDirection)
{
	if ( sourceDirection != NORTH && traversable(NORTH))
	{
		*currentSpace += convertDir(NORTH);
		traverseMaze(SOUTH);
		*currentSpace -= convertDir(NORTH);
	}
	if ( sourceDirection != EAST && traversable(EAST))
	{
		*currentSpace += convertDir(EAST);
		traverseMaze(WEST);
		*currentSpace -= convertDir(EAST);
	}
	if ( sourceDirection != SOUTH && traversable(SOUTH))
	{
		*currentSpace += convertDir(SOUTH);
		traverseMaze(NORTH);
		*currentSpace -= convertDir(SOUTH);
	}
	if ( sourceDirection != WEST && traversable(WEST))
	{
		*currentSpace += convertDir(WEST);
		traverseMaze(EAST);
		*currentSpace -= convertDir(WEST);
	}
	if (!(checkSpot(sourceDirection)))
	{
		mazeySet->changeValue(DEAD_END, *currentSpace);
	}
}

//This function checks to see if an adjacent square in the maze is marked as a dead end or has a wall between it and the current square.
bool maze::traversable(char directy)
{
	char temp = mazeySet->getValue(*currentSpace);
	if (temp & directy && !(mazeySet->getValue((*currentSpace) + convertDir(directy)) & DEAD_END))
	{
		return true;
	}
	return false;
}

//This function determines whether or not a square in the maze is a dead end. Returns true if it isn't a dead end. False means it
//is a dead end.
bool maze::checkSpot(char& srcDirect)
{
	for (short testDirect = NORTH; testDirect <= WEST; testDirect = testDirect << 1)
	{
		if ((mazeySet->getValue(*currentSpace) & TREASURE) || (mazeySet->getValue(*currentSpace) & EXIT) || (testDirect != srcDirect && traversable(testDirect)))
		{
			return true;
		}
	}
	return false;
}

//This function generates the maze.
void maze::startMaze()
{
	addTreasures();
	//Keeps track of how many unions have been done while generating the maze. Total number of unions done will be equal to the 
	//product of the dimensions of the array minus 1.
	int* tempInt = new int;
	*tempInt = 0;
	//int x = 0;
	do
	{
		//Moves onto the next space here.
		*currentSpace += 1;
		// Was used to test what the average number of passes through the maze is while generating.
		/*
		if ((*currentSpace) == 1)
		{
			x++;
			cout << x;
		}
		*/
		
		//Making sure it doesn't exceed the bounds of the array.
		*currentSpace %= TOTAL_SIZE;
		//Picking a random direction from North, South, East, and West.
		direction = randDir();
		//Determining if the direction chosen will leave the bounds of the array or if that wall has already been broken down.
		if (detValidDir(direction))
		{
			//Checking if the sets are disjoint. Unioning them if they are.
			if (mazeySet->unionDisjSet(*currentSpace, *(currentSpace) + convertDir(direction)))
			{
				//Adjusting the array that serves as a map of the maze.
				mazeySet->changeValue(direction, *currentSpace);
				mazeySet->changeValue(reverseDir(direction),*currentSpace + convertDir(direction));
				//Counting unions.
				(*tempInt)++;
			}
		}
	}while((*tempInt) < TOTAL_SIZE - 1); //Check if maze is done.
	delete tempInt;
	cout << endl;
}

//Converts a direction into the position in the maze relative to the current position.
int maze::convertDir(char directy)
{
	switch (directy)
	{
	case NORTH:
		return -MAP_SIZE_X;
	case EAST:
		return 1;
	case SOUTH:
		return MAP_SIZE_X;
	case WEST:
		return -1;
	default:
		return NULL;
	}
}
//Reverses a direction. Useful for breaking down walls. If a Northern wall is broken, 
//then the room to the North has to have its southern wall broken.
char maze::reverseDir(char directy)
{
	switch (directy)
	{
	case NORTH:
		return SOUTH;
	case EAST:
		return WEST;
	case SOUTH:
		return NORTH;
	case WEST:
		return EAST;
	default:
		return NULL;
	}
}

//Determines a random direction.
char maze::randDir()
{
	switch (rand() & 3)
	{
	case 0:
		return NORTH;
	case 1:
		return EAST;
	case 2:
		return SOUTH;
	case 3:
		return WEST;
	default:
		return NULL;
	}
}

//Determines if a direction is valid. It's invalid if it will break out of the maze or target an already broken wall.
bool maze::detValidDir(char directy)
{
	switch (directy)
	{
		case NORTH:
			if ((*currentSpace) - MAP_SIZE_X >= 0 && !(mazeySet->getValue(*currentSpace) & NORTH))
				return true;
			else
				return false;
		case EAST:
			if ((*currentSpace) % MAP_SIZE_X + 1 != MAP_SIZE_X && !(mazeySet->getValue(*currentSpace) & EAST) && (*currentSpace) + 1 < TOTAL_SIZE)
				return true;
			else
				return false;
		case SOUTH:
			if ((*currentSpace) + MAP_SIZE_X < TOTAL_SIZE && !(mazeySet->getValue(*currentSpace) & SOUTH))
				return true;
			else
				return false;
		case WEST:
			if ((*currentSpace) % MAP_SIZE_X - 1 != -1 && !(mazeySet->getValue(*currentSpace) & WEST))
				return true;
			else
				return false;
		default:
			return false;
	}
}



void maze::outputMaze()
{
	char* code = new char;
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			(*code) = mazeySet->getValue(x + y * MAP_SIZE_X);
			changeColor(code);
			cout << (codeToPiece(*code));
			cout << "\033[0m";
		}
		cout << endl;
	}
	cout << endl << endl;
	delete code;
}

void maze::changeColor(char* mazeCode)
{
	if ((*mazeCode) & 240)
	{
		if ((*mazeCode) & ENTRANCE)
		{
			//Sets the background color for spaces marked as the entrance. (Green)
			cout << "\033[42m";
			if (!(*mazeCode & NORTH))
				(*mazeCode) += NORTH;
		}
		else if((*mazeCode) & EXIT)
		{
			//Sets the background color for the space marked as the Exit. (Red)
			cout << "\033[41m";
			if (!(*mazeCode & SOUTH))
				(*mazeCode) += SOUTH;
		}
		else if ((*mazeCode) & DEAD_END)
		{
			cout << "\033[44m";
		}
		else if((*mazeCode) & TREASURE)
		{
			//Sets the background color for spaces that contain treasure. (Yellow)
			cout << "\033[43m";
		}

	}
}


/*
//Outputs the maze.
void maze::outputMaze()
{
	char temp;
	char* code = new char;
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			(*code) = mazeySet->getValue(x + y * MAP_SIZE_X);
			changeColor(code);
			(temp) = codeToPiece(*code);
			cout << (temp);
		}
		//Resets Color to default. (White on Black.)
		SetConsoleTextAttribute(consoleHandle, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
		cout << endl;
	}
	cout << endl << endl;
	delete code;
}
*/

/*
//This function interprets the left four bits in a char into a color.
void maze::changeColor(char* mazeCode)
{
	if ((*mazeCode) & 240)
	{
		if ((*mazeCode) & ENTRANCE)
		{
			//Sets the background color for spaces marked as the entrance. (Green)
			SetConsoleTextAttribute(consoleHandle, BACKGROUND_GREEN);
			if (!(*mazeCode & NORTH))
				(*mazeCode) += NORTH;
		}
		else if((*mazeCode) & EXIT)
		{
			//Sets the background color for the space marked as the Exit. (Red)
			SetConsoleTextAttribute(consoleHandle, BACKGROUND_RED);
			if (!(*mazeCode & SOUTH))
				(*mazeCode) += SOUTH;
		}
		else if ((*mazeCode) & DEAD_END)
		{
			SetConsoleTextAttribute(consoleHandle, BACKGROUND_BLUE);
		}
		else if((*mazeCode) & TREASURE)
		{
			//Sets the background color for spaces that contain treasure. (Yellow)
			SetConsoleTextAttribute(consoleHandle, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED);
		}

	}
	else
	{
		//Resets Color to default. (White on Black.)
		SetConsoleTextAttribute(consoleHandle, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE);
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	}
}
*/

//This function converts a value in a space into an ascii character.
string maze::codeToPiece(char charCode)
{
	//The directions here refer to which walls are currently knocked down in the location that was passed to the function.
	switch (charCode & 15)
	{
	case(NULL): 
		return NONE;
	case(WEST):
		return LEFT_CAP;
	case(SOUTH):
		return UP_CAP;
	case(NORTH):
		return DOWN_CAP;
	case(EAST):
		return RIGHT_CAP;
	case(NORTH + SOUTH + EAST + WEST):
		return CROSS;
	case(EAST + WEST):
		return HORIZONTAL;
	case(SOUTH + NORTH):
		return VERTICAL;
	case(WEST + NORTH + SOUTH):
		return T_LEFT;
	case(EAST + NORTH + SOUTH):
		return T_RIGHT;
	case(SOUTH + WEST + EAST):
		return T_DOWN;
	case(NORTH + WEST + EAST):
		return T_UP;
	case(NORTH + EAST):
		return RIGHT_UP_CORNER;
	case(WEST + NORTH):
		return LEFT_UP_CORNER;
	case(WEST + SOUTH):
		return LEFT_DOWN_CORNER;
	case(EAST + SOUTH):
		return RIGHT_DOWN_CORNER;
	default:
		return NONE;
	}
}

//This function randomly adds treasures to the maze. 
void maze::addTreasures()
{
	unsigned int temp;
	for (unsigned short count = (MAP_SIZE_X + MAP_SIZE_Y) / 7 + 1; count > 0; count--)
	{
		do
		{
			temp = rand() % (TOTAL_SIZE);
		}while((mazeySet->getValue(temp) & TREASURE));
		mazeySet->changeValue(TREASURE, temp);
	}
}
