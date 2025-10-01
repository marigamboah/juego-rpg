#pragma once
#include <QString>

enum class ItemType { Weapon, MaxHpUp, Heal10Pct };

struct Item {
    ItemType type;
    int value{0};
    QString name;
    QString desc;
    static Item weapon(int dmg);
    static Item maxHpUp();
    static Item heal10();
};
