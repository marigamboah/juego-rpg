#ifndef GAME_H
#define GAME_H

#include <array>
#include <QString>
#include "types.h"
#include "character.h"
#include "floor.h"

class Game {
public:
    Game();

    // Lectura
    int getFloor() const { return floorIndex_+1; }
    int getPlayerHP() const { return player_.hp(); }
    int getPlayerMaxHP() const { return player_.maxHp(); }
    int getPlayerATK() const { return player_.atk(); }
    int getRemainingRolls() const { return rollsLeft_; }
    Pos getPlayerPos() const { return pos_; }
    TileType getTile(int r, int c) const;

    // Escritura (para Save)
    void setFloor(int f);               // 1..5
    void setRemainingRolls(int v) { rollsLeft_=v; }
    void setPlayerPos(Pos p);
    void setPlayerStats(int hp, int maxhp, int atk);

    // Acciones
    std::pair<int,int> rollDice();               // devuelve (d1,d2)
    TurnResult playerMove(const QString& dir1, const QString& dir2);
    void revealAll();

    // Persistencia
    bool save(const QString& file);
    bool load(const QString& file);

private:
    void clampPos();
    void setPlayerOnGrid();
    void clearPlayerOnGrid();
    void nextFloor();

private:
    static constexpr int kFloors = 5;
    std::array<Floor,kFloors> floors_;
    int floorIndex_{0};  // 0..4
    Character player_{3,1};
    Pos pos_{ Floor::entry() };
    int rollsLeft_{10};
    int lastD1_{0}, lastD2_{0};
};

#endif // GAME_H
