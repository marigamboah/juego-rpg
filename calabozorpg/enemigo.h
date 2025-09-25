#pragma once

#include <QObject>
#include <QDebug> // Incluye QDebug para facilitar la depuración

class Enemigo : public QObject
{
    Q_OBJECT
public:
    // El constructor recibe el nombre del enemigo y el piso en el que se encuentra
    explicit Enemigo(const QString& nombre, int piso);
    ~Enemigo();

    // Métodos para obtener los atributos
    QString getNombre() const;
    int getVida() const;
    int getAtaque() const;

    // Método para que el enemigo reciba daño
    void recibirDanio(int danio);

private:
    QString m_nombre;
    int m_vida;
    int m_ataque;
};
