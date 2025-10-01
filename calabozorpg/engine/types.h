#pragma once
#include <QString>
#include <QVector>
#include <vector>
#include <utility>

enum class Tile { Empty, Enemy, Chest, Save, Tavern, Exit };
enum class Dir  { Up, Down, Left, Right };

inline std::pair<int,int> delta(Dir d) {
    switch (d) {
        case Dir::Up:    return {-1, 0};
        case Dir::Down:  return { 1, 0};
        case Dir::Left:  return { 0,-1};
        case Dir::Right: return { 0, 1};
    }
    return {0,0};
}

struct Pos { int row{0}; int col{0}; };

inline bool inside(int r, int c, int N=10) {
    return r>=0 && r<N && c>=0 && c<N;
}
