#ifndef FLOOR_H
#define FLOOR_H

#include <QVector>
#include "types.h"

class Floor {
public:
    static constexpr int N = 10;

    struct Cell {
        TileType type{TileType::Empty};
        bool revealed{false};
    };

    explicit Floor(int number=1);

    int number() const { return floorNum_; }
    const Cell& at(int r, int c) const { return grid_[r][c]; }
    Cell& at(int r, int c) { return grid_[r][c]; }

    static Pos entry() { return {0,0}; }
    static Pos exit()  { return {N-1,N-1}; }

private:
    void generate();

    int floorNum_{1};
    QVector<QVector<Cell>> grid_{N, QVector<Cell>(N)};
};

#endif // FLOOR_H
