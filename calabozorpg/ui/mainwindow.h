#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QVector>
#include <QColor>
#include <QPushButton>
#include "engine/game.h"   // Debe proveer Pos, TurnResult, TileType, Floor::N

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // --- Botones principales ---
    void onRollDice();
    void onMove();
    void onSave();
    void onLoad();

    // Compatibilidad (si alguien presiona Enter en el QLineEdit oculto)
    void onCheatEntered();

    // Botones extra visibles
    void onCheatButton();       // Cheat con pregunta y 3 intentos
    void onTutorialButton();    // Abrir tutorial en cualquier momento

private:
    // --- Inicialización / estilo ---
    void styleUI();
    void styleButtons();
    void setupHUDWidgets();
    void styleHUD();
    void applyCardEffect(QWidget *w);

    // --- Juego y tablero ---
    void setupBoard();
    void paintCell(int r, int c);
    void paintBoard();
    QColor colorForTile(TileType t) const;

    // --- HUD / log ---
    void updateHUD();
    void log(const QString &m);
    void handleTurnResult(TurnResult res);

    // --- Tutorial y diálogos ---
    void showTutorialDialog();
    void showVictoryDialog();
    void showDefeatDialog();

    // --- Utilidades ---
    void setGameControlsEnabled(bool enabled);
    void revealAllTiles();      // helper opcional

    // --- Animación del jugador (tile a tile) ---
    void ensureActorLabel();
    QRect cellRectPx(int r, int c) const;
    QVector<Pos> buildPathFromUI() const;
    void startAnimatedMove(const QVector<Pos> &path);
    void advanceAnimationStep();    // conectado al QTimer::timeout

private:
    Ui::MainWindow *ui;
    Game game;

    // HUD dinámico
    QProgressBar *hpBar = nullptr;

    // Animación
    QLabel *actorLabel = nullptr;
    QTimer *animTimer = nullptr;
    QVector<Pos> animPath;
    int animIndex = 0;
    bool animating = false;

    // Botones extra (barra / layout)
    QPushButton *btnCheat = nullptr;
    QPushButton *btnTutorial = nullptr;

    // Cheat (máximo 3 intentos)
    int cheatTries = 0;
    static constexpr int kCheatMaxTries = 3;

    // Tipografías seleccionadas
    QString headingFamily;
    QString bodyFamily;
    QString emojiFamily;
};

#endif // MAINWINDOW_H
