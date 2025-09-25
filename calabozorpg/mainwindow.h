#pragma once

#include <QMainWindow>
#include "jugador.h"
#include "enemigo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnLanzarDados_clicked();
    void on_btnAtacar_clicked();

private:
    Ui::MainWindow *ui;
    Jugador* elJugador;
    Enemigo* elEnemigo;
    bool enCombate;
};
