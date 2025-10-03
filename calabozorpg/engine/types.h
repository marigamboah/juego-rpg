#ifndef TYPES_H
#define TYPES_H

#include <QtGlobal>

enum class TileType {
    Empty,
    Player,
    Enemy,
    Chest,
    Tavern,
    Exit
};

enum class TurnResult {
    Moved,
    EnemyDefeated,
    PlayerDefeated,
    ChestOpened,
    TavernRest
};

struct Pos {
    int r{0};
    int c{0};
    bool operator==(const Pos& o) const { return r==o.r && c==o.c; }
};

#endif // TYPES_H
