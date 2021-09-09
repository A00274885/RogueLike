#pragma once

void gotoScreenPosition(short C, short R);

bool checkColl(int x, int y);
void renderMap();
void handleInput();
void generateRooms(int x, int y, int width, int height);
void generatePaths();
void encounterMonster(int x, int y);
void renderPlayer();
void renderGUI();
