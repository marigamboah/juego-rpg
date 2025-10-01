#pragma once
#include "types.h"

struct Cell { Tile t{Tile::Empty}; int id{-1}; };

class Floor {
public:
    static constexpr int N = 10;
    QVector<QVector<Cell>> grid;
    int floorNum{1};
    Floor(int f=1);
    static Pos entry();
    static Pos exit();
};
