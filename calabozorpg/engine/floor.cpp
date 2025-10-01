#include "floor.h"

Floor::Floor(int f) : grid(N, QVector<Cell>(N)), floorNum(f) {}
Pos Floor::entry() { return {0,0}; }
Pos Floor::exit() { return {9,9}; }
