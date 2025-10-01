#include "game.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <cstdlib>

Game::Game()
    : currentFloor(1), playerHP(3), playerMaxHP(3), playerATK(1),
    rollsLeft(10), playerRow(0), playerCol(0)
{
    grid.resize(N, QVector<Cell>(N, {TileType::Empty, -1}));
    grid[playerRow][playerCol].type = TileType::Player;
}

// === NUEVO: mover el marcador del jugador de forma segura ===
void Game::setPlayerPos(Pos p) {
    // limpiar posición anterior
    if (playerRow >= 0 && playerRow < N && playerCol >= 0 && playerCol < N) {
        if (grid[playerRow][playerCol].type == TileType::Player)
            grid[playerRow][playerCol].type = TileType::Empty;
    }
    // clamp y asignar nueva
    playerRow = std::clamp(p.row, 0, N-1);
    playerCol = std::clamp(p.col, 0, N-1);
    grid[playerRow][playerCol].type = TileType::Player;
}

std::pair<int,int> Game::rollDice() {
    if (rollsLeft <= 0) return {0,0};
    --rollsLeft;
    int d1 = 1 + rand()%6;
    int d2 = 1 + rand()%6;
    return {d1,d2};
}

TurnResult Game::playerMove(const QString &dir1, const QString &dir2) {
    auto moveOne = [&](const QString &dir) {
        int dr=0, dc=0;
        if (dir == "↑") dr=-1;
        if (dir == "↓") dr=+1;
        if (dir == "←") dc=-1;
        if (dir == "→") dc=+1;

        int nr = playerRow + dr, nc = playerCol + dc;
        if (nr < 0 || nr >= N || nc < 0 || nc >= N) return TurnResult::Moved;

        grid[playerRow][playerCol].type = TileType::Empty;
        playerRow = nr; playerCol = nc;

        auto &tile = grid[playerRow][playerCol];
        TurnResult res = TurnResult::Moved;
        switch (tile.type) {
        case TileType::Enemy:
            if (playerATK >= 1) { res = TurnResult::EnemyDefeated; }
            else { playerHP = 0; res = TurnResult::PlayerDefeated; }
            break;
        case TileType::Chest:
            playerATK += 1; res = TurnResult::ChestOpened; break;
        case TileType::Tavern:
            playerHP = std::min(playerMaxHP, playerHP + 2);
            res = TurnResult::TavernRest; break;
        default:
            res = TurnResult::Moved;
        }

        tile.type = TileType::Player;
        return res;
    };

    TurnResult r1 = moveOne(dir1);
    if (playerHP <= 0) return r1;
    TurnResult r2 = moveOne(dir2);
    return r2;
}

void Game::revealAll() {
    for (int r=0; r<N; ++r)
        for (int c=0; c<N; ++c)
            if (grid[r][c].type == TileType::Empty)
                grid[r][c].type = TileType::Enemy; // placeholder de "revelado"
}

Cell Game::getTile(int row, int col) const {
    return grid[row][col];
}

// Guardado / carga directos
bool Game::save(const QString &file) {
    QJsonObject root;
    root["floor"] = currentFloor;
    root["hp"] = playerHP;
    root["maxHp"] = playerMaxHP;
    root["atk"] = playerATK;
    root["rolls"] = rollsLeft;
    root["row"] = playerRow;
    root["col"] = playerCol;

    QJsonDocument doc(root);
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly)) return false;
    f.write(doc.toJson());
    return true;
}

bool Game::load(const QString &file) {
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly)) return false;
    QByteArray data = f.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) return false;

    QJsonObject root = doc.object();
    currentFloor = root["floor"].toInt(1);
    playerHP = root["hp"].toInt(3);
    playerMaxHP = root["maxHp"].toInt(3);
    playerATK = root["atk"].toInt(1);
    rollsLeft = root["rolls"].toInt(10);
    setPlayerPos({ root["row"].toInt(0), root["col"].toInt(0) });

    return true;
}
