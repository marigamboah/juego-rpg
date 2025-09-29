#include "mainwindow.h"
#include <QDebug>
#include <QRandomGenerator>
#include "enemigo.h"
#include "jugador.h"
#include "ui_mainwindow.h" // ¡LA CLAVE para que funcione Ui::MainWindow!

// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // El ui está definido en ui_mainwindow.h
{
    // Configura la interfaz de usuario desde el archivo .ui
    ui->setupUi(this);

    // Crea instancias del jugador y enemigo
    elJugador = new Jugador("Errësirë", 3, 3);
    elEnemigo = nullptr;
    enCombate = false;

    // Configura y actualiza la barra de vida
    ui->barraVida->setMaximum(elJugador->getVida());
    ui->barraVida->setValue(elJugador->getVida());

    // Configura la visibilidad de los botones al inicio
    ui->btnAtacar->hide();
    ui->btnLanzarDados->show();
}

// Destructor para liberar la memoria de los objetos
MainWindow::~MainWindow()
{
    delete ui;
    delete elJugador;
    if (elEnemigo) {
        delete elEnemigo;
    }
}

// Lógica para el botón "Lanzar Dados"
void MainWindow::on_btnLanzarDados_clicked()
{
    qDebug() << "Lanzando dados...";

    // Simula movimiento y probabilidad de enemigo
    int movimiento = QRandomGenerator::global()->bounded(1, 7);
    qDebug() << "El jugador se mueve " << movimiento << " casillas.";

    bool hayEnemigo = QRandomGenerator::global()->bounded(2) == 0;

    if (hayEnemigo) {
        qDebug() << "¡Ha aparecido un enemigo!";
        enCombate = true;
        elEnemigo = new Enemigo("Monstruo", 1);

        ui->btnLanzarDados->hide();
        ui->btnAtacar->show();
    }
}

// Lógica para el botón "Atacar"
void MainWindow::on_btnAtacar_clicked()
{
    if (enCombate && elEnemigo) {
        // Jugador ataca
        elJugador->atacar(elEnemigo);

        if (elEnemigo->getVida() > 0) {
            // Enemigo contraataca
            elJugador->recibirDanio(elEnemigo->getAtaque());
            ui->barraVida->setValue(elJugador->getVida());
        } else {
            // Enemigo derrotado
            qDebug() << "¡El enemigo ha sido derrotado!";
            delete elEnemigo;
            elEnemigo = nullptr;
            enCombate = false;

            ui->btnAtacar->hide();
            ui->btnLanzarDados->show();
        }
    }
}
