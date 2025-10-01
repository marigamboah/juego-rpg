#pragma once
#include <algorithm>

class Character {
public:
    Character(int hp = 3, int maxHp = 3, int atk = 1)
        : hp_(hp), maxHp_(maxHp), atk_(atk) {
        if (maxHp_ < 1) maxHp_ = 1;
        hp_ = std::clamp(hp_, 0, maxHp_);
        if (atk_ < 0) atk_ = 0;
    }

    // Getters
    int hp() const      { return hp_; }
    int maxHp() const   { return maxHp_; }
    int atk() const     { return atk_; }

    // Setters seguros
    void setHp(int v)       { hp_ = std::clamp(v, 0, maxHp_); }
    void setMaxHp(int v)    { maxHp_ = std::max(1, v); hp_ = std::min(hp_, maxHp_); }
    void setAtk(int v)      { atk_ = std::max(0, v); }

    // Acciones
    void heal(int amount)        { setHp(hp_ + std::max(0, amount)); }
    void takeDamage(int amount)  { setHp(hp_ - std::max(0, amount)); }
    bool isDead() const          { return hp_ <= 0; }

private:
    int hp_;
    int maxHp_;
    int atk_;
};
