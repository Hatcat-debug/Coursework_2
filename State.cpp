

#include "State.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom), strength(100) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

int State::getStrength() const {
    return this->strength;
}

void State::setStrength(int s) {
    this->strength = s;
}

void State::addStrength(int s) {
    this->strength += s;
}



list<GameObject*>& State::getInventory() {
    return this->inventory;
}
void State::addToInventory(GameObject *obj) {
    this->inventory.push_back(obj);
}
void State::removeFromInventory(GameObject *obj) {
    this->inventory.remove(obj);
}