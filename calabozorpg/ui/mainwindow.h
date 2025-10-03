#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>          // usado por log(const QString&)
#include "engine/types.h"   // para TurnResult, TileType (evita dependencias implícitas)
#include "engine/game.h"    // Game

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

private slots:
    void onRollDice();
    void onMove();
    void onSave();
    void onLoad();
    void onCheatEntered();

private:
    void setupBoard();
    void paintCell(int r,int c);
    void paintBoard();
    void updateHUD();
    void log(const QString& msg);
    void handleTurnResult(TurnResult res);
    void revealAllTiles();

private:
    Ui::MainWindow *ui{nullptr};
    Game game;
};

#endif // MAINWINDOW_H
