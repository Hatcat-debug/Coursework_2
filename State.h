

#ifndef COURSEWORK_2_STATE_H
#define COURSEWORK_2_STATE_H


#include "Room.h"

class State {
    Room *currentRoom;
    int strength;
    list<GameObject*> inventory;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;
    int getStrength() const;
    void setStrength(int s);
    void addStrength(int s);

    list<GameObject*>& getInventory();
    void addToInventory(GameObject *obj);
    void removeFromInventory(GameObject *obj);
};


#endif //COURSEWORK_2_STATE_H
