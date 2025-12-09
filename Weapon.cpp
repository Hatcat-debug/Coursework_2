//
// Created by 1 on 2025/12/8.
//

#include "Weapon.h"

#include <stdexcept>

Weapon::Weapon(int w, const string* k, const string* d, int h) : GameObject(w, k, d), harm(h) {
    if (w < 5) {
        throw std::invalid_argument("Weapon weight must be at least 5");
    }
    if (w > 10) {
        throw std::invalid_argument("Weapon weight must be at most 10");
    }
    if (h < 10) {
        throw std::invalid_argument("Weapon harm must be at least 10");
    }
    if (h > 30) {
        throw std::invalid_argument("Weapon harm must be at most 30");
    }
}
int Weapon::getHarm() const {
    return harm;
}
