#include "floor.h"
#include <QRandomGenerator>

Floor::Floor(int number) : floorNum_(number) {
    generate();
}

void Floor::generate() {
    // Limpio
    for (int r=0;r<N;++r) for (int c=0;c<N;++c) grid_[r][c] = Cell{TileType::Empty,false};

    // Entrada / Salida
    grid_[entry().r][entry().c].type = TileType::Empty; // Player lo pondrá Game
    grid_[exit().r][exit().c].type   = TileType::Exit;

    // Cantidades base
    int enemies = 10;
    int chests  = 15;
    int taverns = 1;

    auto rndpos = [](){
        return Pos{ int(QRandomGenerator::global()->bounded(N)),
                   int(QRandomGenerator::global()->bounded(N)) };
    };

    // Enemigos
    int placed=0;
    while (placed<enemies) {
        Pos p = rndpos();
        if ((p==entry()) || (p==exit())) continue;
        if (grid_[p.r][p.c].type==TileType::Empty) {
            grid_[p.r][p.c].type = TileType::Enemy;
            ++placed;
        }
    }
    // Cofres
    placed=0;
    while (placed<chests) {
        Pos p = rndpos();
        if ((p==entry()) || (p==exit())) continue;
        if (grid_[p.r][p.c].type==TileType::Empty) {
            grid_[p.r][p.c].type = TileType::Chest;
            ++placed;
        }
    }
    // Tabernas
    placed=0;
    while (placed<taverns) {
        Pos p = rndpos();
        if ((p==entry()) || (p==exit())) continue;
        if (grid_[p.r][p.c].type==TileType::Empty) {
            grid_[p.r][p.c].type = TileType::Tavern;
            ++placed;
        }
    }
}
