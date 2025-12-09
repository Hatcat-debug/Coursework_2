//
// Created by Administrator on 2025/12/8.
//

#include "Clowns.h"

Clowns::Clowns(const std::string* k, const std::string* d) : EnemyObject(k, d, 30) {}
int Clowns::damage(){
    return 10;
}
