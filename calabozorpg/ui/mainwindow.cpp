#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QHeaderView>     // por horizontalHeader()/verticalHeader()
#include "engine/types.h"  // TileType, TurnResult (si no los incluye tu mainwindow.h)


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupBoard();
    updateHUD();

    connect(ui->btnRoll, &QPushButton::clicked, this, &MainWindow::onRollDice);
    connect(ui->btnMove, &QPushButton::clicked, this, &MainWindow::onMove);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(ui->cheatLine, &QLineEdit::returnPressed, this, &MainWindow::onCheatEntered);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setupBoard() {
    ui->table->setRowCount(10);
    ui->table->setColumnCount(10);
    ui->table->horizontalHeader()->setVisible(false);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);

    for (int r=0;r<10;++r) {
        ui->table->setRowHeight(r, 36);
        for (int c=0;c<10;++c) {
            ui->table->setColumnWidth(c, 36);
            auto *it = new QTableWidgetItem();
            it->setTextAlignment(Qt::AlignCenter);
            ui->table->setItem(r,c,it);
        }
    }
    paintBoard();
}

void MainWindow::paintCell(int r,int c) {
    TileType t = game.getTile(r,c);
    auto *it = ui->table->item(r,c);
    switch (t) {
    case TileType::Empty:  it->setText(""); break;
    case TileType::Player: it->setText("🧝"); break;
    case TileType::Enemy:  it->setText("👹"); break;
    case TileType::Chest:  it->setText("💰"); break;
    case TileType::Tavern: it->setText("🍻"); break;
    case TileType::Exit:   it->setText("⛩"); break;
    }
}
void MainWindow::paintBoard() {
    for (int r=0;r<10;++r)
        for (int c=0;c<10;++c)
            paintCell(r,c);
}
void MainWindow::updateHUD() {
    ui->lblFloor->setText(QString::number(game.getFloor()));
    ui->lblHP->setText(QString("%1/%2").arg(game.getPlayerHP()).arg(game.getPlayerMaxHP()));
    ui->lblATK->setText(QString::number(game.getPlayerATK()));
    ui->lblRolls->setText(QString::number(game.getRemainingRolls()));
}
void MainWindow::log(const QString& m) { ui->logText->append(m); }

void MainWindow::handleTurnResult(TurnResult res) {
    switch (res) {
    case TurnResult::Moved: log("Te moviste."); break;
    case TurnResult::EnemyDefeated: log("¡Enemigo derrotado!"); break;
    case TurnResult::PlayerDefeated:
        log("Has muerto… Game Over."); QMessageBox::information(this,"Game Over","El jugador ha muerto."); break;
    case TurnResult::ChestOpened: log("Abriste un cofre."); break;
    case TurnResult::TavernRest: log("Descansaste en la taberna."); break;
    }
}

void MainWindow::onRollDice() {
    auto d = game.rollDice();
    ui->lblD1->setText(QString::number(d.first));
    ui->lblD2->setText(QString::number(d.second));
    updateHUD();
    log("Has tirado los dados.");
}
void MainWindow::onMove() {
    handleTurnResult(game.playerMove(ui->dir1->currentText(), ui->dir2->currentText()));
    updateHUD();
    paintBoard();
}
void MainWindow::revealAllTiles() { game.revealAll(); paintBoard(); log("Cheat: tablero revelado."); }
void MainWindow::onCheatEntered() {
    const QString cmd = ui->cheatLine->text().trimmed(); ui->cheatLine->clear();
    if (cmd=="reveal") revealAllTiles(); else log("Comando desconocido: "+cmd);
}
void MainWindow::onSave() { if (game.save("savegame.json")) log("Partida guardada."); else log("Error al guardar."); }
void MainWindow::onLoad() { if (game.load("savegame.json")) { paintBoard(); updateHUD(); log("Partida cargada."); } else log("Error al cargar."); }
