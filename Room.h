


#ifndef COURSEWORK_2_ROOM_H
#define COURSEWORK_2_ROOM_H

#include <string>
#include <forward_list>
#include <list>

#include "EnemyObject.h"
#include "GameObject.h"

using std::string;
using std::list;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointer to room that is north of this one.
     */
    Room* north;
    Room * south;
    Room * east;
    Room * west;

    std::list<GameObject*> objects;
    std::list<EnemyObject*> enemies;

public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static std::list<Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);


    Room* getNorth() const;
    void setNorth(Room* _north);
    Room* getSouth() const;
    void setSouth(Room* _south);
    Room* getEast() const;
    void setEast(Room* _east);
    Room* getWest() const;
    void setWest(Room* _west);

    void addObject(GameObject* _object);
    void removeObject(GameObject* _object);
    list<GameObject *> &getObjects();

    void addEnemy(EnemyObject* _enemy);
    void removeEnemy(EnemyObject* _enemy);
    list<EnemyObject *> &getEnemies();
};

#endif //COURSEWORK_2_ROOM_H
