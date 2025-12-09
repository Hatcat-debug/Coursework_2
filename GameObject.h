//
// Created by 1 on 2025/12/8.
//

#ifndef COURSEWORK_2_GAMEOBJECT_H
#define COURSEWORK_2_GAMEOBJECT_H
#include <string>

using std::string;

class GameObject {
    protected:
    int weight;
    const string* keyword;
    const string* desc;

    public:
    GameObject(int w, const string* k, const string* d);

    virtual ~GameObject();

    const string *getKeyword();
    const string *getDesc();
    int getWeight();
};


#endif //COURSEWORK_2_GAMEOBJECT_H