#pragma once
#include <QString>
#include <QVector>
#include <utility>
#include <algorithm>

enum class TileType { Empty, Player, Enemy, Chest, Tavern };

struct Cell {
    TileType type = TileType::Empty;
    int id = -1;
};

enum class TurnResult { EnemyDefeated, PlayerDefeated, ChestOpened, TavernRest, Moved };

// === NUEVO: tipo para posición ===
struct Pos { int row{0}; int col{0}; };

class Game {
public:
    Game();

    // Getters
    int getFloor() const          { return currentFloor; }
    int getPlayerHP() const       { return playerHP; }
    int getPlayerMaxHP() const    { return playerMaxHP; }
    int getPlayerATK() const      { return playerATK; }
    int getRemainingRolls() const { return rollsLeft; }
    Pos getPlayerPos() const      { return {playerRow, playerCol}; } // NUEVO

    // Setters (para Save::fromJson)
    void setFloor(int v)                { currentFloor = std::max(1, v); }   // NUEVO
    void setRemainingRolls(int v)       { rollsLeft = std::max(0, v); }      // NUEVO
    void setPlayerPos(Pos p);                                               // NUEVO
    void setPlayerHP(int v)             { playerHP = std::clamp(v, 0, playerMaxHP); } // opcional
    void setPlayerMaxHP(int v)          { playerMaxHP = std::max(1, v); playerHP = std::min(playerHP, playerMaxHP); } // opcional
    void setPlayerATK(int v)            { playerATK = std::max(0, v); }      // opcional

    // Lógica
    std::pair<int,int> rollDice();
    TurnResult playerMove(const QString &dir1, const QString &dir2);
    void revealAll();

    Cell getTile(int row, int col) const;

    // Guardado / carga directos
    bool save(const QString &file);
    bool load(const QString &file);

private:
    static const int N = 10;
    QVector<QVector<Cell>> grid;
    int currentFloor;
    int playerHP, playerMaxHP, playerATK;
    int rollsLeft;
    int playerRow, playerCol;
};
