//
// Created by 1 on 2025/12/8.
//

#include "GameObject.h"

GameObject::GameObject(int w, const string* k, const string* d) : weight(w), keyword(k), desc(d) {}
GameObject::~GameObject() = default;

const string *GameObject::getKeyword() {
    return keyword;
}
const string *GameObject::getDesc() {
    return desc;
}
int GameObject::getWeight() {
    return weight;
}
