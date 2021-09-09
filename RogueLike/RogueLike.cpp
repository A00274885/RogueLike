#include <windows.h>
#include <iostream>
#include <string>

#include "Generation.h"

const int LEVELWIDTH = 50;
const int LEVELHEIGHT = 25;

unsigned int playerPositionX = 7;
unsigned int playerPositionY = 5;
unsigned int newPlayerPositionX = playerPositionX;
unsigned int newPlayerPositionY = playerPositionY;

unsigned int health = 0;

char playerChar = 'P';

char borderChar = 219;

const char vWallChar = 186;
const char hWallChar = 205;
const char trWallChar = 187;
const char brWallChar = 188;
const char tlWallChar = 201;
const char blWallChar = 200;


char map[LEVELHEIGHT][LEVELWIDTH + 1] =
{
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  ",
"                                                  "
};

void gotoScreenPosition(short C, short R)
{
	COORD xy;
	xy.X = C;
	xy.Y = R;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

bool checkColl(int x, int y)
{
	switch (map[y][x])
	{
	case vWallChar:
		return false;
		break;
	case hWallChar:
		return false;
		break;
	case trWallChar:
		return false;
		break;
	case tlWallChar:
		return false;
		break;
	case brWallChar:
		return false;
		break;
	case blWallChar:
		return false;
	default:
		return true;
		break;
	}
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
			if (i == 0 || i == LEVELHEIGHT -1)
				map[i][n] = borderChar;

			if (n == 0 || n == LEVELWIDTH)
				map[i][n] = borderChar;
			std::cout << map[i][n];
		}
		std::cout << std::endl;
	}
}


void handleInput()
{
	newPlayerPositionX = playerPositionX;
	newPlayerPositionY = playerPositionY;

	if (GetKeyState(VK_UP) & 0x8000 && checkColl(playerPositionX, playerPositionY-1))
	{
		newPlayerPositionY = playerPositionY - 1;
	}

	if (GetKeyState(VK_DOWN) & 0x8000 && checkColl(playerPositionX, playerPositionY+1))
	{
		newPlayerPositionY = playerPositionY + 1;
	}

	if (GetKeyState(VK_RIGHT) & 0x8000 && checkColl(playerPositionX+1, playerPositionY))
	{
		newPlayerPositionX = playerPositionX + 1;
	}

	if (GetKeyState(VK_LEFT) & 0x8000 && checkColl(playerPositionX-1,playerPositionY))
	{
		newPlayerPositionX = playerPositionX - 1;
	}
}

void generateRooms(int x,int y,int width,int height)
{
	
	int pWidth = x + width;
	int pHeight = y + height;

	for (int lY = y; lY < pHeight+1; lY++)
	{
		for (int lX = x; lX < pWidth+1; lX++)
		{
			if (lX == x && lY == y)
			{
				map[lY][lX] = tlWallChar;
			}
			else if (lY == y && lX != pWidth)
			{
				map[lY][lX] = hWallChar;
			}
			else if (lY == y)
			{
				map[lY][lX] = trWallChar;
			}
			else if (lY != pHeight && (lX == x || lX == pWidth))
			{
				map[lY][lX] = vWallChar;
			}
			else if (lY == pHeight && lX == x)
			{
				map[lY][lX] = blWallChar;
			}
			else if (lY == pHeight && lX == pWidth)
			{
				map[lY][lX] = brWallChar;
			}
			else if (lY == pHeight)
			{
				map[lY][lX] = hWallChar;
			}

		}
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

void main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 800, 800, TRUE);

	
	generateRooms( 5,2, 7, 5);
	generateRooms(20, 5, 15, 8);
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