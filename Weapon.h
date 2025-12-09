//
// Created by 1 on 2025/12/8.
//

#ifndef COURSEWORK_2_WEAPON_H
#define COURSEWORK_2_WEAPON_H
#include "GameObject.h"


class Weapon : public GameObject {
    protected:
        int harm;
    public:
        Weapon(int w, const string* k, const string* d, int h);
        int getHarm() const;
};


#endif //COURSEWORK_2_WEAPON_H