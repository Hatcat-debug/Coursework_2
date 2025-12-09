
#include "Room.h"

#include "Food.h"
#include "Weapon.h"
#include "wordwrap.h"

/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    if (!objects.empty()) {
        std::string obj = "Objects in this room: ";
        for (auto i : objects) {
            Food* food = dynamic_cast<Food*>(i);
            if (food) obj += "'[Food] ";
            else obj += "'[Weapon] ";

            obj += *i->getKeyword();
            obj += "' ";
        }
        wrapOut(&obj);
        wrapEndPara();
    }

    if (!enemies.empty()) {
        std::string enemy = "Enemies in this room: ";
        for (auto i : enemies) {
            enemy += "'";
            enemy += *i->getKeyword();
            enemy += "' ";
        }
        wrapOut(&enemy);
        wrapEndPara();
    }
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}

Room* Room::getSouth() const {
    return this->south;
}
void Room::setSouth(Room* _south) {
    this->south = _south;
}

Room* Room::getEast() const {
    return this->east;
}
void Room::setEast(Room* _east) {
    this->east = _east;
}

Room* Room::getWest() const {
    return this->west;
}
void Room::setWest(Room* _west) {
    this->west = _west;
}

void Room::addObject(GameObject* _object) {
    this->objects.push_back(_object);
}
void Room::removeObject(GameObject* _object) {
    this->objects.remove(_object);
}

list<GameObject*>& Room::getObjects(){
    return this->objects;
}

void Room::addEnemy(EnemyObject* _enemy) {
    this->enemies.push_back(_enemy);
}
void Room::removeEnemy(EnemyObject* _enemy) {
    this->enemies.remove(_enemy);
}
list<EnemyObject*>& Room::getEnemies(){
    return this->enemies;
}
