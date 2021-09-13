#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Generation.h"
#include "Character.cpp"

const int LEVELWIDTH = 50;
const int LEVELHEIGHT = 25;

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




bool checkColl(int x, int y)
{
	switch (map[y][x])
	{
	case vWallChar:
		return false;
	case hWallChar:
		return false;
	case trWallChar:
		return false;
	case tlWallChar:
		return false;
	case brWallChar:
		return false;
	case blWallChar:
		return false;
	case walkChar:
		return true;
	case pathChar:
		return true;
	default:
		return false;
	}
}



/// <summary>
/// Creation of the game world and everything in it
/// Classes: Generate rooms
///			 Generate paths
///			 Generate Map
/// </summary>

void generateRooms(int x, int y, int width, int height)
{
	int pWidth = x + width;
	int pHeight = y + height;

	for (int lY = y; lY < pHeight + 1; lY++)
	{
		for (int lX = x; lX < pWidth + 1; lX++)
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
			else
			{
				map[lY][lX] = walkChar;
			}
		}
	}
	
}

void renderMap()
{
	for (int i = 0; i < LEVELHEIGHT; i++)
	{
		for (int n = 0; n < LEVELWIDTH + 1; n++)
		{
			if (i == 0 || i == LEVELHEIGHT - 1)
				map[i][n] = borderChar;
			else if (n == 0 || n == LEVELWIDTH)
				map[i][n] = borderChar;
			else map[i][n] = walkChar;
			std::cout << map[i][n];
		}
		std::cout << std::endl;
	}
}

void clearScreen()
{
	gotoScreenPosition(0, 0);

	for (int x = 0; x < LEVELWIDTH + 20; x++)
	{
		for (int y = 0; y < LEVELHEIGHT + 20; y++)
		{
			cout << " ";
		}
	}

	gotoScreenPosition(0, 0);
}

/// <summary>
/// Input handling
/// </summary>
void handleInput(Player player)
{
	
	player.setNewCoords(player.getCoords().X, player.getCoords().Y);
	/*player.setNewCoords(0, player.getCoords(0));
	player.setNewCoords(1, player.getCoords(1));*/

	if (GetKeyState(VK_UP) & 0x8000 && checkColl(player.getCoords().X, player.getCoords().Y -1))
	{
		/*player.setNewCoords(1, player.getCoords(1) - 1);*/
		player.setNewCoords(player.getCoords().X, player.getCoords().Y - 1);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000 && checkColl(player.getCoords().X, player.getCoords().Y +1))
	{
		/*player.setNewCoords(1, player.getCoords(1) + 1);*/
		player.setNewCoords(player.getCoords().X, player.getCoords().Y + 1);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000 && checkColl(player.getCoords().X +1, player.getCoords().Y))
	{
		/*player.setNewCoords(0, player.getCoords(0) + 1);*/
		player.setNewCoords(player.getCoords().X + 1, player.getCoords().Y);
	}
	else if (GetKeyState(VK_LEFT) & 0x8000 && checkColl(player.getCoords().X -1, player.getCoords().Y))
	{
		/*player.setNewCoords(0, player.getCoords(0) - 1);*/
		player.setNewCoords(player.getCoords().X - 1, player.getCoords().Y);
	}
	
	if (GetKeyState(VK_F1) & 0x8000)
	{
		clearScreen();
		player.displayInventory();
		clearScreen();
		renderMap();
	}
}

/// <summary>
/// All code related to Player and non player characters on the screen and how
/// they interact with eachother and the environment
/// </summary>
void renderPlayer(Player player)
{
	// Blank old player position
	gotoScreenPosition(player.getCoords().X, player.getCoords().Y);
	if (map[player.getCoords().Y][player.getCoords().X] == pathChar)
		std::cout << pathChar;
	else
		std::cout << walkChar;

	// Draw new player position
	gotoScreenPosition(player.getNewCoords().X, player.getNewCoords().Y);
	std::cout << player.getIcon();
	

	player.setCoords(player.getCoords().X, player.getCoords().Y);
	/*player.setCoords(0, player.getNewCoords(0));
	player.setCoords(1, player.getNewCoords(1));*/

	Sleep(60);
}



/// <summary>
/// All code related to rendering the gui and other game information
/// to the player
/// Classes: RenderGUI
/// </summary>
void renderGUI()
{
	gotoScreenPosition(2, LEVELHEIGHT + 3);
	//std::cout << "Health: " << playerHealth << std:: endl <<"Attack: " << playerAttack;

	gotoScreenPosition(LEVELWIDTH + 5, LEVELHEIGHT / 2);
}

/// <summary>
/// Different tools used frequently throughout the program
/// Classes: gotoScreenPosition
/// </summary>
void gotoScreenPosition(short C, short R)
{
	COORD xy;
	xy.X = C;
	xy.Y = R;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 800, 800, TRUE);

	string name;
	std::cin >> name;
	Player player(name, 4, 20, 80, 10, 1);

	Item item(1, "Lol", 1, 1);
	player.pickUpItem(item);

	renderMap();
	Player* playerptr = &player;

	/// <summary>
	/// Game runtime
	/// </summary>
	while (true)
	{
		//Player* playerPtr = &player;
		// Handles the input and updates the players position
		handleInput(*playerptr);
		renderPlayer(*playerptr);
		
		
	}
	system("pause");
}