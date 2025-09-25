#include "enemigo.h"
#include <QDebug>

// El enemigo tiene (piso + 1) de vida y (piso) de ataque
Enemigo::Enemigo(const QString& nombre, int piso)
    : m_nombre(nombre), m_vida(piso + 1), m_ataque(piso)
{
    qDebug() << "El enemigo " << m_nombre << " ha aparecido. Vida: " << m_vida << ", Ataque: " << m_ataque;
}

Enemigo::~Enemigo()
{
    qDebug() << "El enemigo " << m_nombre << " ha sido derrotado.";
}

QString Enemigo::getNombre() const
{
    return m_nombre;
}

int Enemigo::getVida() const
{
    return m_vida;
}

int Enemigo::getAtaque() const
{
    return m_ataque;
}

void Enemigo::recibirDanio(int danio)
{
    m_vida -= danio;
    qDebug() << m_nombre << " ha recibido " << danio << " puntos de daño. Vida restante: " << m_vida;
}
