#ifndef ITEMS_H
#define ITEMS_H

#include <QtGlobal>

enum class ItemType { Weapon, MaxHP, Heal };

struct Item {
    ItemType type{ItemType::Weapon};
};

#endif // ITEMS_H
