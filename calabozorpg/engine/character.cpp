#include "character.h"
#include <algorithm>

Character::Character(int hp, int atk) : hp_(hp), maxHp_(hp), atk_(atk) {}

void Character::setHp(int v) { hp_ = std::max(0, std::min(v, maxHp_)); }
void Character::addMaxHp(int v) { maxHp_ += v; if (maxHp_ < 1) maxHp_ = 1; if (hp_ > maxHp_) hp_ = maxHp_; }
void Character::heal(int v) { setHp(hp_ + v); }
void Character::addAtk(int v) { atk_ += v; if (atk_ < 0) atk_ = 0; }
