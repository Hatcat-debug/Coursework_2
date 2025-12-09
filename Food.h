//
// Created by 1 on 2025/12/8.
//

#ifndef COURSEWORK_2_FOOD_H
#define COURSEWORK_2_FOOD_H
#include "GameObject.h"


class Food : public GameObject {
    protected:
    int energy;

    public:
    Food(int w, const string* k, const string* d, int e);
    int getEnergy() const;
};


#endif //COURSEWORK_2_FOOD_H