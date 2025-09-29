#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "enemigo.h" // ¡Añadido!
#include "jugador.h" // ¡Añadido!

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // ¡Añadido! Funciones para los botones
    void on_btnLanzarDados_clicked();
    void on_btnAtacar_clicked();

private:
    Ui::MainWindow *ui;
    // ¡Añadido! Variables para la lógica del juego
    Jugador *elJugador;
    Enemigo *elEnemigo;
    bool enCombate;
};
#endif // MAINWINDOW_H
