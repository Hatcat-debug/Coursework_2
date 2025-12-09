//
// Created by 1 on 2025/12/8.
//

#include "Food.h"

#include <stdexcept>

Food::Food(int w, const string* k, const string* d, int e) : GameObject(w, k, d), energy(e) {
    if (w < 1) {
        throw std::invalid_argument("Weight must be at least 1");
    }
    if (w > 5) {
        throw std::invalid_argument("Weight must be at most 5");
    }
    if (e < 1) {
        throw std::invalid_argument("Energy must be at least 1");
    }
    if (e > 10) {
        throw std::invalid_argument("Energy must be at most 10");
    }
}
int Food::getEnergy() const {
    return energy;
}
