#pragma once
#include "game.h"
#include <QJsonObject>

namespace Save {
    QJsonObject toJson(const Game& g);
    void fromJson(Game& g, const QJsonObject& o);
    bool saveToFile(const Game& g, const QString& path);
    bool loadFromFile(Game& g, const QString& path);
}
