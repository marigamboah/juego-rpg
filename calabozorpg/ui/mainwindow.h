#pragma once
#include <QMainWindow>
#include <QString>
#include "engine/game.h"   // aquí viene TurnResult, TileType, etc.

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRollDice();
    void onMove();
    void onSave();
    void onLoad();
    void onCheatEntered();

private:
    void setupBoard();
    void paintCell(int row, int col);
    void paintBoard();
    void updateHUD();
    void log(const QString &msg);
    void revealAllTiles();

    // ⬇️ ESTA ERA LA QUE FALTABA
    void handleTurnResult(const TurnResult &res);

    Ui::MainWindow *ui;
    Game game;
};
