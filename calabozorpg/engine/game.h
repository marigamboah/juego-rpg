#pragma once
#include "floor.h"
#include "character.h"
#include "enemy.h"
#include "items.h"
#include <QRandomGenerator>
#include <QStringList>

struct CombatLog { QStringList lines; bool heroDied{false}; bool enemyDied{false}; };
enum class EventKind { None, Enemy, Chest, Save, Tavern, ExitReached, GameOver };

struct TurnResult {
    bool moved{false};
    Pos finalPos{};
    EventKind event{EventKind::None};
    CombatLog combat;
    QStringList messages;
};

class Game {
public:
    Player hero;
    int currentFloor{1};
    int rollsLeft{10};
    Pos pos{Floor::entry()};
    Floor floor{currentFloor};

    void newFloor();
    TurnResult applyTurn(int d1, Dir dir1, int d2, Dir dir2);

    static int d6();
    static bool canMove(const Pos& from, Dir dir, int steps, Pos& out);
    void setSeed(quint32 seed);

private:
    void generateFloorContents();
    void place(Tile t, int count);
    void resolveFinalTile(TurnResult& tr);
    CombatLog startCombat(Enemy enemy);
    void lootChest(TurnResult& tr);
    void visitTavern(TurnResult& tr);
    void hitSave(TurnResult& tr);
    int randInt(int a, int b);
};
