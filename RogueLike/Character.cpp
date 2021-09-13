#include <vector>
#include <string>
#include "Item.cpp"
#include <iostream>
#include <memory>
#include <windows.h>
#include <winuser.rh>



using namespace std;


/// <summary>
/// 
/// </summary>
class Character
{
private:
	string name;
	int attack;
	int health;
	char iconChar;
	int armourClass;
	int critChance;
	COORD coords;
	COORD newCoords;
	/*int coords[1];
	int newCoords[1];*/
public:
	Character(string name, int attack, int health, char iconChar,int armourClass, int critChance)
	{
		this->name = name;
		this->attack = attack;
		this->health = health;
		this->iconChar = iconChar;
		this->armourClass = armourClass;
		this->critChance = critChance;
		this->coords.X = 7;
		this->coords.Y = 5;
		this->newCoords.X = 7;
		this->newCoords.Y = 5;
	}

	string getName() { return this->name; }
	void setName(string name) { this->name = name; }

	int getAttack(){ return this->attack; }
	void setAttack(int attack) { this->attack = attack; }

	int getHealth() { return this->health; }
	void setHealth(int health) { this->health = health; }

	char getIcon() { return this->iconChar; }
	void setIcon(char icon) { this->iconChar = icon; }

	int getArmourClass() { return this->armourClass; }
	void setArmourClass(int armourClass) { this->armourClass = armourClass; }

	int getCritChance() { return this->critChance; }
	void setCritChance(int critChance) { this->critChance = critChance; }

	COORD getCoords() const { return this->coords; }
	void setCoords(short x, short y) { this->coords.X = x; this->coords.Y = y; }

	COORD getNewCoords() const { return this->newCoords; }
	void setNewCoords(short x, short y) { this->newCoords.X = x; this->newCoords.Y = y; }

};

class Player : public Character
{
private:
	vector<Item> inventory{};
	vector<Weapon> weapons{};
	vector<Armour> armours{};
public:
	Player(string name, int attack, int health, char iconChar,int armourClass,int critChance): Character{name,attack,health,iconChar,armourClass,critChance}
	{
		Weapon shortSword(2, "Short Sword", 1, 32, 4);
		weapons.push_back(shortSword);
		Armour leatherArmour(3, "Leather Armour", 1, 54, 5);
		armours.push_back(leatherArmour);
	}

	void pickUpItem(Item item)
	{
		inventory.push_back(item);
	}

	void displayInventory()
	{
		
			for (Item item : inventory)
			{
				cout << item.getName() << endl;
			}
			for (Weapon weapon : weapons)
			{
				cout << weapon.getName() << endl;
			}
			for (Armour armour : armours)
			{
				cout << armour.getName() << endl;
			}

		while (true)
		{
			if (GetKeyState(0x1B) & 0x8000)
				break;
		}
	}
};

class Monster : public Character
{
private:
public:
	Monster(string name, int attack, int health, char iconChar,int armourClass, int critChance) : Character(name, attack, health, iconChar,armourClass,critChance)
	{

	}
};





