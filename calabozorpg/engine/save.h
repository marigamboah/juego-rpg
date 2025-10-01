#pragma once
#include <QJsonObject>

class Game;

namespace Save {
QJsonObject toJson(const Game &g);
void fromJson(Game &g, const QJsonObject &o);
}
