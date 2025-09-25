#pragma once

#include <QObject>
#include "enemigo.h"

class Jugador : public QObject
{
    Q_OBJECT
public:
    // Constructor con los atributos iniciales
    explicit Jugador(const QString& nombre, int vida, int ataque);
    ~Jugador();

    // Getters
    int getVida() const;
    int getAtaque() const;
    QString getNombre() const;

    // Métodos de lógica del juego
    void atacar(Enemigo* enemigo);
    void recibirDanio(int danio);

private:
    QString m_nombre;
    int m_vida;
    int m_ataque;
};
