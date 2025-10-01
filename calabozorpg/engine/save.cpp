#include "save.h"
#include "game.h"
#include <QJsonObject>

namespace Save {

QJsonObject toJson(const Game &g) {
    QJsonObject o;
    o["floor"]    = g.getFloor();
    o["hp"]       = g.getPlayerHP();
    o["maxHp"]    = g.getPlayerMaxHP();
    o["atk"]      = g.getPlayerATK();
    o["rollsLeft"]= g.getRemainingRolls();

    Pos p = g.getPlayerPos();  // ahora Pos existe en game.h
    QJsonObject posJson;
    posJson["r"] = p.row;
    posJson["c"] = p.col;
    o["pos"] = posJson;

    return o;
}

void fromJson(Game &g, const QJsonObject &o) {
    g.setFloor(o["floor"].toInt(1));
    g.setPlayerHP(o["hp"].toInt(3));
    g.setPlayerMaxHP(o["maxHp"].toInt(3));
    g.setPlayerATK(o["atk"].toInt(1));
    g.setRemainingRolls(o["rollsLeft"].toInt(10));

    QJsonObject p = o["pos"].toObject();
    g.setPlayerPos({ p["r"].toInt(0), p["c"].toInt(0) });
}

} // namespace Save
