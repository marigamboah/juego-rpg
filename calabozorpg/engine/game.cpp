// engine/game.cpp
#include "game.h"
#include <algorithm>

// ---------- Utilidades ----------
int Game::d6() {
    return QRandomGenerator::global()->bounded(1, 7);
}

bool Game::canMove(const Pos& from, Dir dir, int steps, Pos& out) {
    auto [dr, dc] = delta(dir);
    int r = from.row + dr * steps;
    int c = from.col + dc * steps;
    if (!inside(r, c, Floor::N)) return false;
    out = { rint Game::getFloor() const { return floor; }
int Game::getPlayerHP() const { return player.hp; }
int Game::getPlayerMaxHP() const { return player.maxHP; }
int Game::getPlayerATK() const { return player.atk; }
int Game::getRemainingRolls() const { return rolls; }

std::pair<int,int> Game::rollDice() {
    return { rand()%6 + 1, rand()%6 + 1 };
}

TurnResult Game::playerMove(const QString &, const QString &) {
    return TurnResult::Moved; // Placeholder
}

Tile Game::getTile(int row, int col) const {
    return floorData[row][col]; // según cómo hayas guardado tu mapa
}

bool Game::save(const std::string &) { return true; } // Placeholder
bool Game::load(const std::string &) { return true; } // Placeholder

void Game::revealAll() {
    // Marcar todas las casillas como visibles
}
, c };
    return true;
}

void Game::setSeed(quint32 seed) {
    QRandomGenerator::global()->seed(seed);
}

int Game::randInt(int a, int b) {
    // incluye b
    return QRandomGenerator::global()->bounded(a, b + 1);
}

// ---------- Ciclo de piso ----------
void Game::newFloor() {
    floor = Floor(currentFloor);
    rollsLeft = 10;
    pos = Floor::entry();
    generateFloorContents();
}

void Game::place(Tile t, int count) {
    int placed = 0;
    while (placed < count) {
        int r = randInt(0, Floor::N - 1);
        int c = randInt(0, Floor::N - 1);
        if ((r == Floor::entry().row && c == Floor::entry().col) ||
            (r == Floor::exit().row && c == Floor::exit().col)) continue;
        if (floor.grid[r][c].t == Tile::Empty) {
            floor.grid[r][c].t = t;
            floor.grid[r][c].id = placed;
            placed++;
        }
    }
}

void Game::generateFloorContents() {
    for (auto& row : floor.grid)
        for (auto& cell : row)
            cell = Cell{};

    // marcar salida
    auto ex = Floor::exit();
    floor.grid[ex.row][ex.col].t = Tile::Exit;

    // contenido mínimo por piso
    place(Tile::Enemy, 10);
    place(Tile::Chest, 15);
    place(Tile::Tavern, 2);
    place(Tile::Save,   2);
}

// ---------- Turno: movimiento + evento ----------
TurnResult Game::applyTurn(int d1, Dir dir1, int d2, Dir dir2) {
    TurnResult tr; tr.finalPos = pos;

    Pos mid, end;
    if (!canMove(pos, dir1, d1, mid)) {
        tr.messages << "Primer tramo inválido.";
        return tr;
    }
    if (!canMove(mid, dir2, d2, end)) {
        tr.messages << "Segundo tramo inválido.";
        return tr;
    }

    // aplicar movimiento y consumir 1 tirada
    pos = end;
    tr.finalPos = pos;
    tr.moved = true;
    rollsLeft = std::max(0, rollsLeft - 1);

    // evento al final
    resolveFinalTile(tr);

    // aviso si se quedó sin tiradas y no está en la salida
    if (rollsLeft == 0 && tr.event != EventKind::ExitReached) {
        tr.messages << "Te quedaste sin tiradas en este piso.";
    }
    return tr;
}

void Game::resolveFinalTile(TurnResult& tr) {
    auto& cell = floor.grid[pos.row][pos.col];
    switch (cell.t) {
    case Tile::Enemy: {
        tr.event = EventKind::Enemy;
        Enemy e(currentFloor);
        tr.combat = startCombat(e);
        if (tr.combat.enemyDied) {
            cell.t = Tile::Empty; cell.id = -1;
            tr.messages << "Venciste al enemigo.";
        }
        if (tr.combat.heroDied) {
            tr.event = EventKind::GameOver;
            tr.messages << "El protagonista ha caído. Game Over.";
        }
    } break;

    case Tile::Chest: {
        tr.event = EventKind::Chest;
        lootChest(tr);
        // cofre se consume
        cell.t = Tile::Empty; cell.id = -1;
    } break;

    case Tile::Save: {
        tr.event = EventKind::Save;
        hitSave(tr); // la UI decide guardar
    } break;

    case Tile::Tavern: {
        tr.event = EventKind::Tavern;
        visitTavern(tr);
        // una vez reclutada, la taberna se “vacía”
        cell.t = Tile::Empty; cell.id = -1;
    } break;

    case Tile::Exit: {
        tr.event = EventKind::ExitReached;
        tr.messages << "Has alcanzado la salida.";
    } break;

    case Tile::Empty:
    default:
        tr.event = EventKind::None;
    }
}

// ---------- Combate ----------
CombatLog Game::startCombat(Enemy enemy) {
    CombatLog L;

    auto aliveIndices = [&]() {
        std::vector<int> idx; idx.reserve(1 + (int)hero.party.size());
        if (hero.isAlive()) idx.push_back(-1); // -1 = héroe
        for (int i = 0; i < (int)hero.party.size(); ++i)
            if (hero.party[i].isAlive()) idx.push_back(i);
        return idx;
    };

    auto pickRandomTarget = [&]() -> int {
        auto idx = aliveIndices();
        if (idx.empty()) return -2;
        int k = randInt(0, (int)idx.size() - 1);
        return idx[k]; // -1 héroe, >=0 aliado
    };

    auto someoneAlive = [&]() {
        if (hero.isAlive()) return true;
        for (auto& a : hero.party) if (a.isAlive()) return true;
        return false;
    };

    bool enemyTurn = (randInt(0, 1) == 0); // quién inicia
    while (enemy.isAlive() && someoneAlive()) {
        if (enemyTurn) {
            int t = pickRandomTarget();
            if (t == -2) break; // nadie
            Character* target = (t == -1 ? (Character*)&hero : &hero.party[t]);
            target->s.hp -= std::max(1, enemy.totalAttack());
            L.lines << QString("Enemigo golpea a %1 por %2.")
                           .arg(target->name).arg(enemy.totalAttack());
        } else {
            if (hero.isAlive()) {
                enemy.s.hp -= std::max(1, hero.totalAttack());
                L.lines << QString("Héroe golpea por %1.").arg(hero.totalAttack());
            }
            for (auto& a : hero.party) if (a.isAlive()) {
                    enemy.s.hp -= std::max(1, a.totalAttack());
                    L.lines << QString("%1 golpea por %2.").arg(a.name).arg(a.totalAttack());
                    if (!enemy.isAlive()) break;
                }
        }
        enemyTurn = !enemyTurn;

        if (enemy.s.hp <= 0) { L.enemyDied = true; }
        if (!hero.isAlive()) { L.heroDied = true; }
    }
    return L;
}

// ---------- Cofres / Taberna / Guardado ----------
void Game::lootChest(TurnResult& tr) {
    // 0: arma nueva; 1: +1 PS máx (+1 curado); 2: curación 10% (mín 1) a todo el grupo
    int kind = randInt(0, 2);
    if (kind == 0) {
        int newW = randInt(currentFloor + 2, currentFloor + 4);
        Item it = Item::weapon(newW);
        hero.giveItem(it);          // registrar en inventario
        hero.tryEquipWeapon(newW);  // equipar si mejora
        tr.messages << QString("Cofre: %1. ¡Arma equipada si es mejor! (arma=%2)")
                           .arg(it.name).arg(hero.s.weapon);
    } else if (kind == 1) {
        Item it = Item::maxHpUp();
        hero.giveItem(it);
        hero.s.maxHp += 1; hero.s.hp += 1;
        tr.messages << "Cofre: Aumento de PS (+1 máx y +1 curado).";
    } else {
        Item it = Item::heal10();
        hero.giveItem(it);
        int heal = std::max(1, hero.s.maxHp / 10);
        auto healOne = [&](Character& ch) {
            ch.s.hp = std::min(ch.s.maxHp, ch.s.hp + heal);
        };
        healOne(hero);
        for (auto& a : hero.party) healOne(a);
        tr.messages << QString("Cofre: Poción 10%% aplicada. +%1 PS a todo el grupo.").arg(heal);
    }
}

void Game::visitTavern(TurnResult& tr) {
    if ((int)hero.party.size() >= 3) {
        tr.messages << "La party ya está completa (3).";
        return;
    }
    Character ally;
    ally.name = QString("Aliado %1").arg(hero.party.size() + 1);
    // Stats razonables por piso
    ally.s.maxHp = std::max(2, currentFloor);
    ally.s.hp    = ally.s.maxHp;
    ally.s.atk   = std::max(1, currentFloor - 1);
    ally.s.weapon= std::max(1, currentFloor);
    hero.party.push_back(ally);
    tr.messages << QString("Se unió %1 (HP %2, ATK %3, Arma %4)")
                       .arg(ally.name).arg(ally.s.maxHp).arg(ally.s.atk).arg(ally.s.weapon);
}

void Game::hitSave(TurnResult& tr) {
    // El motor sólo notifica; la UI/persistencia hace el guardado real
    tr.messages << "Punto de salvado alcanzado. (La UI debería guardar el estado ahora)";
}
