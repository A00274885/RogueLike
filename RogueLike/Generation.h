#pragma once


const char vWallChar = 186;
const char hWallChar = 205;
const char trWallChar = 187;
const char brWallChar = 188;
const char tlWallChar = 201;
const char blWallChar = 200;
const char walkChar = 249;
const char pathChar = 176;
char borderChar = 219;



void gotoScreenPosition(short C, short R);
bool checkColl(int x, int y);
void renderMap();
void generateRooms(int x, int y, int width, int height);
void generatePaths();
void encounterMonster(int x, int y);
void renderPlayer();
void renderGUI();
