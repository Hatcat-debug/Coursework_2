//
// Created by 1 on 2025/12/8.
//

#include "EnemyObject.h"

EnemyObject::EnemyObject(const string* k, const string* d, int h) : keyword(k), desc(d), health(h) {}
EnemyObject::~EnemyObject() = default;

const string *EnemyObject::getKeyword(){ return keyword; }
const string *EnemyObject::getDescription() { return desc; }
int EnemyObject::getHealth() { return health; }
void EnemyObject::setHealth(int health) {
    this->health = health;
}
void EnemyObject::takeDamage(int amount) {
    health -= amount;
}
