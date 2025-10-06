#include "game.h"
#include "save.h"
#include <QFile>
#include <QJsonDocument>
#include <QRandomGenerator>
#include <algorithm>

Game::Game() {
    for (int i=0;i<kFloors;++i) floors_[i] = Floor(i+1);
    pos_ = Floor::entry();
    setPlayerOnGrid();
}

TileType Game::getTile(int r, int c) const {
    if (pos_.r==r && pos_.c==c) return TileType::Player;
    return floors_[floorIndex_].at(r,c).type;
}

void Game::setFloor(int f) {
    f = std::max(1,std::min(f,kFloors));
    clearPlayerOnGrid();
    floorIndex_ = f-1;
    pos_ = Floor::entry();
    rollsLeft_ = 10;
    setPlayerOnGrid();
}

void Game::setPlayerPos(Pos p) {
    clearPlayerOnGrid();
    pos_ = p; clampPos();
    setPlayerOnGrid();
}

void Game::setPlayerStats(int hp, int maxhp, int atk) {
    player_.addMaxHp(maxhp - player_.maxHp());
    player_.addAtk(atk - player_.atk());
    player_.setHp(hp);
}

std::pair<int,int> Game::rollDice() {
    if (rollsLeft_<=0) return {0,0};
    --rollsLeft_;
    lastD1_ = int(QRandomGenerator::global()->bounded(1,7));
    lastD2_ = int(QRandomGenerator::global()->bounded(1,7));
    return {lastD1_, lastD2_};
}

TurnResult Game::playerMove(const QString& dir1, const QString& dir2) {
    auto stepOf = [](const QString& d)->Pos {
        if (d=="Up") return {-1,0};
        if (d=="Down") return {1,0};
        if (d=="Left") return {0,-1};
        if (d=="Right") return {0,1};
        return {0,0};
    };
    Pos step1 = stepOf(dir1), step2 = stepOf(dir2);

    clearPlayerOnGrid();

    // mover d1 + d2 en línea recta según cada dirección
    Pos cur = pos_;
    for (int i=0;i<lastD1_;++i) { cur.r += step1.r; cur.c += step1.c; clampPos(); }
    for (int i=0;i<lastD2_;++i) { cur.r += step2.r; cur.c += step2.c; clampPos(); }

    // Resolver celda de destino
    auto &cell = floors_[floorIndex_].at(cur.r,cur.c);
    TurnResult res = TurnResult::Moved;

    switch (cell.type) {
    case TileType::Enemy: {
        // combate muy básico: si ATK >= (piso), gana; si no, muere
        int enemyHp = floors_[floorIndex_].number()+1;
        int enemyAtk = floors_[floorIndex_].number();
        if (player_.atk() >= enemyHp) {
            res = TurnResult::EnemyDefeated;
        } else {
            player_.setHp(player_.hp() - enemyAtk);
            if (player_.isDead()) { setPlayerOnGrid(); return TurnResult::PlayerDefeated; }
        }
        cell.type = TileType::Empty;
    } break;
    case TileType::Chest: {
        // recompensa simple: 1/3 arma, 1/3 +maxHP, 1/3 curar
        int r = int(QRandomGenerator::global()->bounded(3));
        if (r==0) player_.addAtk(1);
        else if (r==1) player_.addMaxHp(1);
        else player_.heal(std::max(1, player_.maxHp()/10));
        res = TurnResult::ChestOpened;
        cell.type = TileType::Empty;
    } break;
    case TileType::Tavern: {
        player_.heal(std::max(1, player_.maxHp()/5));
        res = TurnResult::TavernRest;
    } break;
    case TileType::Exit: {
        // siguiente piso
        pos_ = cur;
        setPlayerOnGrid();
        nextFloor();
        return TurnResult::Moved;
    }
    default: break;
    }

    pos_ = cur;
    setPlayerOnGrid();
    return res;
}

void Game::revealAll() {
    auto &f = floors_[floorIndex_];
    for (int r=0;r<Floor::N;++r)
        for (int c=0;c<Floor::N;++c)
            f.at(r,c).revealed = true;
}

bool Game::save(const QString& file) {
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly)) return false;
    QJsonDocument doc(Save::toJson(*this));
    f.write(doc.toJson());
    return true;
}

bool Game::load(const QString& file) {
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly)) return false;
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isObject()) return false;
    Save::fromJson(*this, doc.object());
    return true;
}

// privados
void Game::clampPos() {
    pos_.r = std::max(0, std::min(pos_.r, Floor::N-1));
    pos_.c = std::max(0, std::min(pos_.c, Floor::N-1));
}
void Game::setPlayerOnGrid() {
    // no marcamos Player en grid para evitar estados mezclados; UI consulta getTile()
    auto &f = floors_[floorIndex_];
    f.at(pos_.r,pos_.c).revealed = true;
}
void Game::clearPlayerOnGrid() {
    // nada que limpiar explícitamente
}
void Game::nextFloor() {
    if (floorIndex_ < kFloors-1) {
        ++floorIndex_;
        pos_ = Floor::entry();
        rollsLeft_ = 10;
    }
}
