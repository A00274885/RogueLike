#include <windows.h>
#include <iostream>
#include <string>

const int LEVELWIDTH = 30;
const int LEVELHEIGHT = 15;

unsigned int playerPositionX = 5;
unsigned int playerPositionY = 5;
unsigned int newPlayerPositionX = playerPositionX;
unsigned int newPlayerPositionY = playerPositionY;

unsigned int health = 0;

char playerChar = 'P';

char wallChar = 'a';


char map[LEVELHEIGHT][LEVELWIDTH + 1] =
{
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              ",
"                              "
};

void gotoScreenPosition(short C, short R)
{
	COORD xy;
	xy.X = C;
	xy.Y = R;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void renderMap()
{
	//for (int i = 0; i < LEVELHEIGHT; i++)
	//{
	//	std::cout << map[i] << std::endl;
	//}
	for (int i = 0; i < LEVELHEIGHT; i++)
	{
		for (int n = 0; n < LEVELWIDTH + 1; n++)
		{
			std::cout << map[i][n];
		}
		std::cout << std::endl;
	}
}

void handleInput()
{
	newPlayerPositionX = playerPositionX;
	newPlayerPositionY = playerPositionY;

	if (GetKeyState(VK_UP) & 0x8000 && (map[playerPositionY - 1][playerPositionX] != 'a'))
	{
		newPlayerPositionY = playerPositionY - 1;
	}

	if (GetKeyState(VK_DOWN) & 0x8000 && (map[playerPositionY+1][playerPositionX] != 'a'))
	{
		newPlayerPositionY = playerPositionY + 1;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000 && (map[playerPositionY][playerPositionX +1] != 'a'))
	{
		newPlayerPositionX = playerPositionX + 1;
	}

	if (GetKeyState(VK_LEFT) & 0x8000 && (map[playerPositionY][playerPositionX-1] != 'a'))
	{
		newPlayerPositionX = playerPositionX - 1;
	}
}

void renderPlayer()
{
	// Blank old enemy position
	gotoScreenPosition(playerPositionX, playerPositionY);
	std::cout << ' ';

	// Draw new enemy position
	gotoScreenPosition(newPlayerPositionX, newPlayerPositionY);
	std::cout << playerChar;
	gotoScreenPosition(newPlayerPositionX, newPlayerPositionY);

	playerPositionX = newPlayerPositionX;
	playerPositionY = newPlayerPositionY;

	Sleep(60);
}

void renderGUI()
{
	gotoScreenPosition(2, LEVELHEIGHT + 3);
	std::cout << "Health: " << health;
}

void generateMap()
{
	//Pick a spot on the map and define width and height
	//Draw the rooms in without overlapping
	//Create doors and connecting tunnels between rooms (pathfinding?)

	
}

void main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 800, 800, TRUE);

	generateMap();
	renderMap();
	

	while (true)
	{
		// Handles the input and updates the players position
		handleInput();

		// Render the scene
		renderPlayer();

		// Render the GUI
		renderGUI();

	}

	system("pause");
}