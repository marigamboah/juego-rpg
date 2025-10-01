#pragma once
#include <algorithm>

class Enemy {
public:
    Enemy(int hp = 1, int atk = 1)
        : hp_(hp), atk_(atk) {
        if (hp_ < 0) hp_ = 0;
        if (atk_ < 0) atk_ = 0;
    }

    // Getters
    int hp() const  { return hp_; }
    int atk() const { return atk_; }

    // Setters
    void setHp(int v)  { hp_  = std::max(0, v); }
    void setAtk(int v) { atk_ = std::max(0, v); }

    // Acciones
    void takeDamage(int amount) { setHp(hp_ - std::max(0, amount)); }
    bool isDead() const         { return hp_ <= 0; }

private:
    int hp_;
    int atk_;
};
