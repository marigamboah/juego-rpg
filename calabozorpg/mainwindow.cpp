#include "mainwindow.h"
#include "ui_mainwindow.h" // ¡Esta línea es la clave para solucionar el error!
#include "jugador.h"
#include "enemigo.h"
#include <QDebug>
#include <QRandomGenerator>

// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Configura la interfaz de usuario desde el archivo .ui
    ui->setupUi(this);

    // Crea una instancia del jugador con los atributos iniciales del documento
    elJugador = new Jugador("Errësirë", 3, 3);
    elEnemigo = nullptr; // Inicialmente no hay un enemigo

    // Configura y actualiza la barra de vida en la interfaz
    ui->barraVida->setMaximum(elJugador->getVida());
    ui->barraVida->setValue(elJugador->getVida());

    // Configura la visibilidad de los botones al inicio del juego
    ui->btnAtacar->hide();
    ui->btnLanzarDados->show();
    enCombate = false;
}

// Destructor para liberar la memoria de los objetos
MainWindow::~MainWindow()
{
    delete ui;
    delete elJugador;
    // Asegúrate de eliminar el enemigo si todavía existe
    if (elEnemigo) {
        delete elEnemigo;
    }
}

// Lógica para cuando se presiona el botón "Lanzar Dados"
void MainWindow::on_btnLanzarDados_clicked()
{
    qDebug() << "Lanzando dados...";

    // Simula el movimiento del jugador con un número aleatorio entre 1 y 6
    int movimiento = QRandomGenerator::global()->bounded(1, 7);
    qDebug() << "El jugador se mueve " << movimiento << " casillas.";

    // Simula una probabilidad de 50% de que aparezca un enemigo
    bool hayEnemigo = QRandomGenerator::global()->bounded(2) == 0;

    if (hayEnemigo) {
        qDebug() << "¡Ha aparecido un enemigo!";
        enCombate = true;

        // Crea un nuevo enemigo con los atributos del piso 1
        elEnemigo = new Enemigo("Monstruo", 1);

        // Oculta el botón de dados y muestra el de ataque
        ui->btnLanzarDados->hide();
        ui->btnAtacar->show();
    }
}

// Lógica para cuando se presiona el botón "Atacar"
void MainWindow::on_btnAtacar_clicked()
{
    if (enCombate && elEnemigo) {
        // El jugador ataca primero
        elJugador->atacar(elEnemigo);

        if (elEnemigo->getVida() > 0) {
            // Si el enemigo no ha sido derrotado, contraataca
            elJugador->recibirDanio(elEnemigo->getAtaque());
            // Actualiza la barra de vida del jugador en la interfaz
            ui->barraVida->setValue(elJugador->getVida());
        } else {
            // El enemigo ha sido derrotado
            qDebug() << "¡El enemigo ha sido derrotado!";

            // Libera la memoria del enemigo y actualiza el estado del juego
            delete elEnemigo;
            elEnemigo = nullptr;
            enCombate = false;

            // Vuelve a mostrar el botón de dados y oculta el de ataque
            ui->btnAtacar->hide();
            ui->btnLanzarDados->show();
        }
    }
}
