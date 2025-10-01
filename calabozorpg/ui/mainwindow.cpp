#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupBoard();
    updateHUD();

    // Conexiones de botones
    connect(ui->btnRoll, &QPushButton::clicked, this, &MainWindow::onRollDice);
    connect(ui->btnMove, &QPushButton::clicked, this, &MainWindow::onMove);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(ui->cheatLine, &QLineEdit::returnPressed, this, &MainWindow::onCheatEntered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
// === Inicialización del tablero ===
//
void MainWindow::setupBoard()
{
    ui->table->setRowCount(10);
    ui->table->setColumnCount(10);
    ui->table->horizontalHeader()->setVisible(false);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);

    for (int r = 0; r < 10; ++r) {
        ui->table->setRowHeight(r, 50);
        for (int c = 0; c < 10; ++c) {
            ui->table->setColumnWidth(c, 50);
            auto *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            ui->table->setItem(r, c, item);
        }
    }

    paintBoard();
}

//
// === Pintar una celda individual ===
//
void MainWindow::paintCell(int row, int col)
{
    auto tile = game.getTile(row, col);
    QTableWidgetItem *item = ui->table->item(row, col);

    switch (tile.type) {
    case TileType::Empty:
        item->setText("");
        break;
    case TileType::Player:
        item->setText("😃");
        break;
    case TileType::Enemy:
        item->setText("👹");
        break;
    case TileType::Chest:
        item->setText("💰");
        break;
    case TileType::Tavern:
        item->setText("🍻");
        break;
    default:
        item->setText("?");
        break;
    }
}

//
// === Pintar todo el tablero ===
//
void MainWindow::paintBoard()
{
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            paintCell(r, c);
        }
    }
}

//
// === Actualizar HUD (estadísticas) ===
//
void MainWindow::updateHUD()
{
    ui->lblFloor->setText(QString::number(game.getFloor()));
    ui->lblHP->setText(QString("%1/%2").arg(game.getPlayerHP()).arg(game.getPlayerMaxHP()));
    ui->lblATK->setText(QString::number(game.getPlayerATK()));
    ui->lblRolls->setText(QString::number(game.getRemainingRolls()));
}

//
// === Escribir en el registro ===
//
void MainWindow::log(const QString &msg)
{
    ui->logText->append(msg);
}

//
// === Acciones del jugador ===
//
void MainWindow::onRollDice()
{
    auto res = game.rollDice();
    ui->lblD1->setText(QString::number(res.first));
    ui->lblD2->setText(QString::number(res.second));
    updateHUD();
    log("Has tirado los dados.");
}

void MainWindow::onMove()
{
    QString dir1 = ui->dir1->currentText();
    QString dir2 = ui->dir2->currentText();

    auto result = game.playerMove(dir1, dir2);

    handleTurnResult(result);
    updateHUD();
    paintBoard();
}

void MainWindow::handleTurnResult(const TurnResult &res)
{
    switch (res) {
    case TurnResult::EnemyDefeated:
        log("¡Derrotaste a un enemigo!");
        break;
    case TurnResult::PlayerDefeated:
        log("Has muerto… Game Over.");
        QMessageBox::information(this, "Game Over", "El jugador ha muerto.");
        break;
    case TurnResult::ChestOpened:
        log("Encontraste un cofre.");
        break;
    case TurnResult::TavernRest:
        log("Descansaste en la taberna.");
        break;
    case TurnResult::Moved:
        log("Te moviste.");
        break;
    }
}

void MainWindow::revealAllTiles()
{
    game.revealAll();
    paintBoard();
    log("Cheat: tablero revelado.");
}

void MainWindow::onCheatEntered()
{
    QString cmd = ui->cheatLine->text();
    ui->cheatLine->clear();

    if (cmd == "reveal") {
        revealAllTiles();
    } else {
        log("Comando desconocido: " + cmd);
    }
}

void MainWindow::onSave()
{
    if (game.save("savegame.dat")) {
        log("Juego guardado.");
    } else {
        log("Error al guardar.");
    }
}

void MainWindow::onLoad()
{
    if (game.load("savegame.dat")) {
        paintBoard();
        updateHUD();
        log("Juego cargado.");
    } else {
        log("Error al cargar partida.");
    }
}
