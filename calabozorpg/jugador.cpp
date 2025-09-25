#include "jugador.h"
#include <QDebug>

Jugador::Jugador(const QString& nombre, int vida, int ataque)
    : m_nombre(nombre), m_vida(vida), m_ataque(ataque)
{
    qDebug() << "El jugador" << m_nombre << "ha sido creado.";
}

Jugador::~Jugador()
{
    qDebug() << "El jugador" << m_nombre << "ha sido eliminado.";
}

int Jugador::getVida() const
{
    return m_vida;
}

int Jugador::getAtaque() const
{
    return m_ataque;
}

QString Jugador::getNombre() const
{
    return m_nombre;
}

void Jugador::atacar(Enemigo* enemigo)
{
    if (enemigo) {
        qDebug() << m_nombre << " ataca a " << enemigo->getNombre() << " con " << m_ataque << " puntos de daño.";
        enemigo->recibirDanio(m_ataque);
    }
}

void Jugador::recibirDanio(int danio)
{
    m_vida -= danio;
    qDebug() << m_nombre << " recibe " << danio << " puntos de daño. Vida restante: " << m_vida;

    if (m_vida <= 0) {
        qDebug() << m_nombre << " ha sido derrotado. Fin del juego.";
        // Aquí iría la lógica de Game Over en la interfaz
    }
}
