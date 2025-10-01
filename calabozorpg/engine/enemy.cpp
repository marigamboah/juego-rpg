#include "enemy.h"

Enemy::Enemy(int floor) {
    name = QString("Enemigo Piso %1").arg(floor);
    s.maxHp = floor + 1;
    s.hp    = s.maxHp;
    s.atk   = floor;
    s.weapon= 0;
}
