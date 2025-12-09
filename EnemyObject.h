//
// Created by 1 on 2025/12/8.
//

#ifndef COURSEWORK_2_ENEMYOBJECT_H
#define COURSEWORK_2_ENEMYOBJECT_H


#include <string>

using std::string;

class EnemyObject {
    protected:
    int health;
    const string* keyword;
    const string* desc;

    public:
    EnemyObject(const string* k, const string* d, int h);

    virtual ~EnemyObject();

    virtual int damage() = 0;

    const string *getKeyword();

    const string *getDescription();

    int getHealth();
    void setHealth(int health);
    void takeDamage(int amount);
};

#endif //COURSEWORK_2_ENEMYOBJECT_H