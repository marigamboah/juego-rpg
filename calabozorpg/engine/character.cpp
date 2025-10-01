#include "character.h"
#include <algorithm>

bool Character::isAlive() const { return s.hp > 0; }
int Character::totalAttack() const { return s.atk + s.weapon; }

Player::Player() { name = "Errësirë"; s = {3,3,1,3}; }
void Player::giveItem(const Item& it) { inventory.push_back(it); }
void Player::tryEquipWeapon(int dmg) { if (dmg > s.weapon) s.weapon = dmg; }
