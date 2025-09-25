#include "enemigo.h"
#include <QDebug>

// El constructor inicializa los atributos del enemigo basándose en el número de piso
Enemigo::Enemigo(const QString& nombre, int piso)
    : m_nombre(nombre), m_vida(piso + 1), m_ataque(piso)
{
    qDebug() << "El enemigo" << m_nombre << "ha aparecido. Vida:" << m_vida << ", Ataque:" << m_ataque;
}

// El destructor se llama cuando el objeto es eliminado
Enemigo::~Enemigo()
{
    qDebug() << "El enemigo" << m_nombre << "ha sido derrotado.";
}

// Devuelve el nombre del enemigo
QString Enemigo::getNombre() const
{
    return m_nombre;
}

// Devuelve la vida actual del enemigo
int Enemigo::getVida() const
{
    return m_vida;
}

// Devuelve el ataque del enemigo
int Enemigo::getAtaque() const
{
    return m_ataque;
}

// Lógica para que el enemigo reciba daño
void Enemigo::recibirDanio(int danio)
{
    m_vida -= danio;
    qDebug() << m_nombre << "ha recibido" << danio << "puntos de daño. Vida restante:" << m_vida;
}
