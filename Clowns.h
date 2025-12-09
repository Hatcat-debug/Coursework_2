//
// Created by Administrator on 2025/12/8.
//

#ifndef COURSEWORK_2_CLOWNS_H
#define COURSEWORK_2_CLOWNS_H
#include "EnemyObject.h"


class Clowns : public EnemyObject {
    public:
    Clowns(const std::string* k, const std::string* d);
    int damage() override;
};


#endif //COURSEWORK_2_CLOWNS_H