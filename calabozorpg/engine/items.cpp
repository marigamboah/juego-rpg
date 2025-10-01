#include "items.h"

Item Item::weapon(int dmg) {
    return Item{ItemType::Weapon, dmg, QString("Arma %1 PA").arg(dmg),
                QString("Un arma con %1 puntos de ataque").arg(dmg)};
}
Item Item::maxHpUp() {
    return Item{ItemType::MaxHpUp, 1, "Aumento de PS", "+1 PS máximo (y curas 1)"};
}
Item Item::heal10() {
    return Item{ItemType::Heal10Pct, 10, "Poción 10%", "Cura 10% (mín. 1) a todo el grupo"};
}
