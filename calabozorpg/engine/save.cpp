#include "save.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>

QJsonObject Save::toJson(const Game& g) {
    QJsonObject o;
    o["floor"] = g.currentFloor;
    o["rollsLeft"] = g.rollsLeft;
    QJsonObject p; p["r"]=g.pos.row; p["c"]=g.pos.col; o["pos"]=p;
    return o;
}
void Save::fromJson(Game& g, const QJsonObject& o) {
    g.currentFloor = o["floor"].toInt(1);
    g.rollsLeft = o["rollsLeft"].toInt(10);
    auto p = o["pos"].toObject();
    g.pos = { p["r"].toInt(0), p["c"].toInt(0) };
}
bool Save::saveToFile(const Game& g, const QString& path) {
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly)) return false;
    f.write(QJsonDocument(toJson(g)).toJson());
    return true;
}
bool Save::loadFromFile(Game& g, const QString& path) {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) return false;
    auto doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isObject()) return false;
    fromJson(g, doc.object());
    return true;
}
