#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../engine/game.h"

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
    Ui::MainWindow *ui;
    Game game;

    void setupBoard();
    void paintCell(int row, int col);
    void paintBoard();
    void updateHUD();
    void log(const QString &msg);
    void revealAllTiles();
};

#endif // MAINWINDOW_H
