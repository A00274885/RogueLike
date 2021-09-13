#include <string>

using namespace std;

/// <summary>
/// 
/// </summary>
class Item
{
private:
	int id;
	string name;
	int rarity;
	char iconChar;
public:
	Item(int id, string name, int rarity, char iconChar)
	{
		this->id = id;
		this->name = name;
		this->rarity = rarity;
		this->iconChar = iconChar;
	}

	int getId() { return this->id; }
	void setId(int id) { this->id = id; }

	string getName() { return this->name; }
	void setName(string name) { this->name = name; }

	int getRarity() { return this->rarity; }
	void setRarity(int rarity) { this->rarity = rarity; }

	char getIcon() { return this->iconChar; }
	void setIcon(char icon) { this->iconChar = icon; }
};

class Weapon :public Item
{
private:
	int attackMod;
public:
	Weapon(int id, string name, int rarity, char iconChar, int attackMod) : Item{ id, name, rarity, iconChar }
	{
		this->attackMod = attackMod;
	}
};

class Armour : public Item
{
private:
	int acMod;
public:
	Armour(int id, string name, int rarity, char iconChar, int acMod) : Item{ id, name, rarity, iconChar }
	{
		this->acMod = acMod;
	}
};

class Potion : public Item
{
private:
public:
	Potion(int id, string name, int rarity, char iconChar) : Item{ id, name, rarity, iconChar }
	{

	}
};