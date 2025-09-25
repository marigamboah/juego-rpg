#pragma once

#include <QObject>
#include "enemigo.h"

class Jugador : public QObject
{
    Q_OBJECT
public:
    // Constructor para inicializar al jugador
    explicit Jugador(const QString& nombre, int vida, int ataque);
    ~Jugador();

    // Métodos de acceso a los atributos
    int getVida() const;
    int getAtaque() const;
    void setVida(int nuevaVida);
    QString getNombre() const;

    // Métodos para la lógica del juego
    void atacar(Enemigo* enemigo);
    void recibirDanio(int danio);

private:
    // Atributos del jugador
    QString m_nombre;
    int m_vida;
    int m_ataque;
};
