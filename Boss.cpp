//
// Created by Administrator on 2025/12/8.
//

#include "Boss.h"
Boss::Boss(const std::string* k, const std::string* d) : EnemyObject(k, d, 100) {}

int Boss::damage() {
    return 30;
}
