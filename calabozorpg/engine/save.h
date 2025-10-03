#ifndef SAVE_H
#define SAVE_H

#include <QJsonObject>

class Game;

namespace Save {
QJsonObject toJson(const Game& g);
void fromJson(Game& g, const QJsonObject& o);
}

#endif // SAVE_H
