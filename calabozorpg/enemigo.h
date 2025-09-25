#pragma once

#include <QObject>
#include <QDebug>

class Enemigo : public QObject
{
    Q_OBJECT
public:
    // Constructor que calcula vida y ataque basándose en el piso
    explicit Enemigo(const QString& nombre, int piso);
    ~Enemigo();

    // Getters
    QString getNombre() const;
    int getVida() const;
    int getAtaque() const;

    // Método para recibir daño
    void recibirDanio(int danio);

private:
    QString m_nombre;
    int m_vida;
    int m_ataque;
};
