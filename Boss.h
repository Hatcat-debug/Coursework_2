//
// Created by Administrator on 2025/12/8.
//

#ifndef COURSEWORK_2_BOSS_H
#define COURSEWORK_2_BOSS_H
#include <string>

#include "EnemyObject.h"


class Boss : public EnemyObject {
    public:
    Boss(const std::string* k, const std::string* d);
    int damage() override;
};


#endif //COURSEWORK_2_BOSS_H