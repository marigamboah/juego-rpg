#ifndef ITEMS_H
#define ITEMS_H
#include <QtGlobal>

enum class ChestReward : quint8 {
    Weapon,     // arma: +X ATK
    MaxHpUp,    // +1 PS máx (y cura 1)
    Heal10Pct   // cura 10% (mín 1)
};

#endif // ITEMS_H
