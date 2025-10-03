#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
public:
    Enemy(int hp=2, int atk=1);
};

#endif // ENEMY_H
