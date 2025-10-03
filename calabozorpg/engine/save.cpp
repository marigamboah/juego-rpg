#include "save.h"
#include "game.h"
#include "types.h"
#include <QJsonArray>

QJsonObject Save::toJson(const Game& g) {
    QJsonObject o;
    o["floor"] = g.getFloor();
    o["rollsLeft"] = g.getRemainingRolls();

    // Posición del jugador
    Pos p = g.getPlayerPos();
    QJsonObject jp; jp["r"]=p.r; jp["c"]=p.c;
    o["pos"] = jp;

    // Vida/ATK
    o["hp"] = g.getPlayerHP();
    o["maxHp"] = g.getPlayerMaxHP();
    o["atk"] = g.getPlayerATK();

    return o;
}

void Save::fromJson(Game& g, const QJsonObject& o) {
    g.setFloor(o["floor"].toInt(1));
    g.setRemainingRolls(o["rollsLeft"].toInt(10));

    QJsonObject jp = o["pos"].toObject();
    g.setPlayerPos({ jp["r"].toInt(0), jp["c"].toInt(0) });

    g.setPlayerStats(o["hp"].toInt(3),
                     o["maxHp"].toInt(3),
                     o["atk"].toInt(1));
}
