#include "jugador.h"
#include <QDebug> // Para imprimir mensajes en la consola de Qt Creator

Jugador::Jugador(const QString& nombre, int vida, int ataque)
    : m_nombre(nombre), m_vida(vida), m_ataque(ataque)
{
    qDebug() << "El jugador" << m_nombre << "ha sido creado.";
}

Jugador::~Jugador() {
    qDebug() << "El jugador" << m_nombre << "ha sido eliminado.";
}

int Jugador::getVida() const {
    return m_vida;
}

int Jugador::getAtaque() const {
    return m_ataque;
}

void Jugador::atacar(Enemigo* enemigo) {
    // En esta función se ejecutará la lógica de ataque del jugador
    qDebug() << m_nombre << "ataca al enemigo. Daño infligido:" << m_ataque;
    enemigo->recibirDanio(m_ataque);
}

void Jugador::recibirDanio(int danio) {
    // Lógica para que el jugador reciba daño
    m_vida -= danio;
    qDebug() << m_nombre << "ha recibido" << danio << "puntos de daño. Vida restante:" << m_vida;
    if (m_vida <= 0) {
        qDebug() << m_nombre << "ha sido derrotado. Fin del juego.";
        // Aquí puedes emitir una señal para notificar a la interfaz.
    }
}
