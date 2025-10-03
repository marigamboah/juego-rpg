#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
    Character(int hp=3, int atk=1);
    virtual ~Character() = default;

    int hp() const { return hp_; }
    int maxHp() const { return maxHp_; }
    int atk() const { return atk_; }

    void setHp(int v);
    void addMaxHp(int v);
    void heal(int v);
    void addAtk(int v);

    bool isDead() const { return hp_ <= 0; }

protected:
    int hp_;
    int maxHp_;
    int atk_;
};

#endif // CHARACTER_H
