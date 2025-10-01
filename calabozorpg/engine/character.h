#pragma once
#include "types.h"
#include "items.h"
#include <vector>

struct Stats { int hp{3}; int maxHp{3}; int atk{1}; int weapon{3}; };

class Character {
public:
    QString name{"Anon"};
    Stats s;
    bool isAlive() const;
    int totalAttack() const;
};

class Player : public Character {
public:
    std::vector<Character> party;
    std::vector<Item> inventory;
    Player();
    void giveItem(const Item& it);
    void tryEquipWeapon(int dmg);
};
