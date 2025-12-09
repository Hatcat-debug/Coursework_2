
#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <fstream>

#include "Boss.h"
#include "Clowns.h"
#include "Food.h"
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "Weapon.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

std::vector<GameObject*> globalObjects;
std::vector<EnemyObject*> globalEnemies;
std::vector<Room*> globalRooms;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r1 = new Room(&r1name, &r1desc);
    globalRooms.push_back(r1);
    auto * r2 = new Room(&r2name, &r2desc);
    globalRooms.push_back(r2);
    auto * r3 = new Room(&r3name, &r3desc);
    globalRooms.push_back(r3);
    auto * r4 = new Room(&r4name, &r4desc);
    globalRooms.push_back(r4);
    auto * r5 = new Room(&r5name, &r5desc);
    globalRooms.push_back(r5);

    for (auto r : globalRooms) {
        Room::addRoom(r);
    }

    r1->setNorth(r2);
    r2->setSouth(r1);
    r1->setSouth(r3);
    r3->setNorth(r1);
    r1->setEast(r4);
    r4->setWest(r1);
    r1->setWest(r5);
    r5->setEast(r1);

    auto * starterSword = new Weapon(5, &w1name, &w1desc, 10);
    auto * starterFood = new Food(1, &f1name, &f1desc, 3);
    globalObjects.push_back(starterSword);
    globalObjects.push_back(starterFood);
    r1->addObject(starterSword);
    r1->addObject(starterFood);

    auto * highTierFood = new Food(2, &f2name, &f2desc, 10);
    globalObjects.push_back(highTierFood);
    r2->addObject(highTierFood);

    auto * legendarySword = new Weapon(6, &w2name, &w2desc, 30);
    globalObjects.push_back(legendarySword);
    r3->addObject(legendarySword);

    auto * minion = new Clowns(&c1name, &c1desc);
    globalEnemies.push_back(minion);
    r3->addEnemy(minion);

    auto * boss = new Boss(&b1name, &b1desc);
    globalEnemies.push_back(boss);
    r4->addEnemy(boss);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}

int getRoomIndex(Room* r) {
    for (size_t i = 0; i < globalRooms.size(); ++i) {
        if (globalRooms[i] == r) return static_cast<int>(i);
    }
    return -1;
}

int getObjectLocationID(GameObject* obj) {
    for (auto* item : currentState->getInventory()) {
        if (item == obj) return -1;
    }
    for (size_t i = 0; i < globalRooms.size(); ++i) {
        for (auto* item : globalRooms[i]->getObjects()) {
            if (item == obj) return static_cast<int>(i);
        }
    }
    return -2;
}

int getEnemyLocationID(EnemyObject* enemy) {
    for (size_t i = 0; i < globalRooms.size(); ++i) {
        for (auto* e : globalRooms[i]->getEnemies()) {
            if (e == enemy) return static_cast<int>(i);
        }
    }
    return -2;
}

void saveGame(const string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        string msg = "Error: Could not open file for save.";
        wrapOut(&msg); wrapEndPara();
        return;
    }

    outFile << "PLAYER" << std::endl;
    outFile << currentState->getStrength() << " "
            << getRoomIndex(currentState->getCurrentRoom()) << std::endl;

    outFile << "OBJECTS" << std::endl;
    outFile << globalObjects.size() << std::endl;
    for (auto* obj : globalObjects) {
        outFile << getObjectLocationID(obj) << " ";
    }
    outFile << std::endl;

    outFile << "ENEMIES" << std::endl;
    outFile << globalEnemies.size() << std::endl;
    for (auto* enemy : globalEnemies) {
        int loc = getEnemyLocationID(enemy);
        int hp = (loc != -2) ? enemy->getHealth() : 0;
        outFile << loc << " " << hp << std::endl;
    }

    outFile.close();
    string msg = "Game saved.";
    wrapOut(&msg); wrapEndPara();
}

void loadGame(const string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        string msg = "Error: Could not open file for load.";
        wrapOut(&msg); wrapEndPara();
        return;
    }

    currentState->getInventory().clear();
    for (auto* r : globalRooms) {
        r->getObjects().clear();
        r->getEnemies().clear();
    }

    string header;
    inFile >> header;
    int strength, roomID;
    inFile >> strength >> roomID;
    currentState->setStrength(strength);
    if (roomID >= 0 && roomID < globalRooms.size()) {
        currentState->goTo(globalRooms[roomID]);
    }

    inFile >> header;
    int objCount;
    inFile >> objCount;
    for (int i = 0; i < objCount; ++i) {
        int locID;
        inFile >> locID;

        if (i < globalObjects.size()) {
            GameObject* obj = globalObjects[i];
            if (locID == -1) {
                currentState->addToInventory(obj);
            } else if (locID >= 0 && locID < globalRooms.size()) {
                globalRooms[locID]->addObject(obj);
            }
        }
    }

    inFile >> header;
    int enemyCount;
    inFile >> enemyCount;
    for (int i = 0; i < enemyCount; ++i) {
        int locID, hp;
        inFile >> locID >> hp;

        if (i < globalEnemies.size()) {
            EnemyObject* enemy = globalEnemies[i];
            if (locID >= 0 && locID < globalRooms.size()) {
                globalRooms[locID]->addEnemy(enemy);
                enemy->setHealth(hp);
            }
        }
    }

    inFile.close();
    string msg = "Game loaded.";
    wrapOut(&msg); wrapEndPara();

    currentState->announceLoc();
}

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        auto firstSpace = commandBuffer.find(' ');

        string action;
        if (firstSpace == string::npos) {
            action = commandBuffer;
        } else {
            action = commandBuffer.substr(0, firstSpace);
        }

        string target;
        if (firstSpace != string::npos) {
            target = commandBuffer.substr(firstSpace + 1);
        }

        /* Command to go north. */
        if (action == "north" || action == "n") {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
            }
        }

        /* Command to go south. */
        if (action == "south" || action == "s") {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a south exit */
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
            }
        }

        /* Command to go east. */
        if (action == "east" || action == "e") {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a east exit */
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
            }
        }

        /* Command to go west. */
        if (action == "west" || action == "w") {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a west exit */
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
            }
        }

        /* Quit command */
        if (action == "quit") {
            commandOk = true;
            gameOver = true;
        }

        /* Save command */
        if (action == "save")
        {
            commandOk = true;
            if (target.empty()) {
                string msg = "Please enter a filename (e.g., save mygame.txt)";
                wrapOut(&msg);
                wrapEndPara();
            } else {
                saveGame(target);
            }
        }

        /* Load command */
        if (action == "load") {
            commandOk = true;
            if (target.empty()) {
                string msg = "Please specify a filename.";
                wrapOut(&msg); wrapEndPara();
            } else {
                loadGame(target);
            }
        }

        /* Command to get an object. */
        if (action == "get") {
            commandOk = true;
            bool found = false;

            auto& roomObjects = currentState->getCurrentRoom()->getObjects();


            for (auto i : roomObjects) {
                if (*i->getKeyword() == target) {
                    GameObject* obj = i;
                    currentState->addToInventory(obj);
                    currentState->getCurrentRoom()->removeObject(obj);

                    string msg = "You picked up '" + *obj->getKeyword() + "'.";
                    wrapOut(&msg);
                    wrapEndPara();
                    found = true;
                    break;
                }
            }
            if (!found) {
                string msg = "There is no " + target + " here.";
                wrapOut(&msg);
                wrapEndPara();
            }
        }

        /* Command to drop an object. */
        if (action == "drop") {
            commandOk = true;
            bool found = false;

            for (auto i : currentState->getInventory()) {
                if (*i->getKeyword() == target) {
                    GameObject* obj = i;
                    currentState->getCurrentRoom()->addObject(obj);
                    currentState->removeFromInventory(obj);

                    string msg = "You dropped '" + *obj->getKeyword() + "'.";
                    wrapOut(&msg);
                    wrapEndPara();
                    found = true;
                    break;
                }
            }
            if (!found) {
                string msg = "You don't have '" + target + "'.";
                wrapOut(&msg);
                wrapEndPara();
            }
        }

        /* Command to check inventory. */
        if (action == "inventory") {
            commandOk = true;
            if (currentState->getInventory().empty()) {
                wrapOut(&emptyInv);
                wrapEndPara();
            } else {
                wrapOut(&inv);
                wrapEndPara();
                string msg;
                for (auto i : currentState->getInventory()) {
                    Food* food = dynamic_cast<Food*>(i);
                    if (food) msg += "'[Food] ";
                    else msg += "'[Weapon] ";
                    msg += *i->getKeyword() + "' ";
                }
                wrapOut(&msg);
                wrapEndPara();
            }
        }

        /* Command for eat food */
        if (action == "eat") {
            commandOk = true;
            bool found = false;

            for (auto i : currentState->getInventory()) {
                if (*i->getKeyword() == target) {
                    GameObject* obj = i;
                    Food* food = dynamic_cast<Food*>(i);

                    if (food) {
                        currentState->addStrength(food->getEnergy());
                        if (currentState->getStrength() > 100) currentState->setStrength(100);
                        currentState->removeFromInventory(obj);
                        string msg = "You ate '" + *obj->getKeyword() + "'.";


                        msg += " Your strength is now " + std::to_string(currentState->getStrength()) + ".";
                        wrapOut(&msg);
                        wrapEndPara();
                    }
                    else {
                        string msg = "You can't eat '" + *obj->getKeyword() + "'.";
                        wrapOut(&msg);
                        wrapEndPara();
                    }
                    found = true;
                    break;
                }
            }
            if (!found) {
                string msg = "You don't have '" + target + "'.";
                wrapOut(&msg);
                wrapEndPara();
            }
        }

        /* Command for fight */
        if (action == "fight") {
            commandOk = true;
            bool found = false;

            for (auto i : currentState->getCurrentRoom()->getEnemies()) {
                if (*i->getKeyword() == target) {
                    EnemyObject* enemy = i;
                    found = true;

                    int playerDamage = 0;
                    for (auto obj : currentState->getInventory()) {
                        auto* weapon = dynamic_cast<Weapon*>(obj);
                        if (weapon) {
                            playerDamage += weapon->getHarm();
                        }
                    }

                    enemy->takeDamage(playerDamage);
                    string msg = "You hit '" + target + "' for " + std::to_string(playerDamage) + " damage.";
                    wrapOut(&msg);
                    wrapEndPara();

                    if (enemy->getHealth() <= 0) {
                        msg = "'" + target + "' has been defeated!";
                        wrapOut(&msg);
                        wrapEndPara();

                        currentState->getCurrentRoom()->removeEnemy(enemy);
                        break;
                    }

                    msg = "'" + target + "' is still alive with " + std::to_string(enemy->getHealth()) + " health.";
                    wrapOut(&msg);
                    wrapEndPara();

                    int enemyDamage = enemy->damage();
                    currentState->addStrength(-enemyDamage);

                    msg = "'" + target + "' attacks you for " + std::to_string(enemyDamage) + " damage.";
                    wrapOut(&msg);
                    wrapEndPara();

                    msg = "Your strength is now " + std::to_string(currentState->getStrength()) + ".";
                    wrapOut(&msg);
                    wrapEndPara();

                    break;
                }
            }
            if (!found) {
                string msg = "There is no " + target + " here.";
                wrapOut(&msg);
                wrapEndPara();
            }
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }

        if (currentState->getStrength() <= 0) {
            std::string msg = "You have died.";
            wrapOut(&msg);
            wrapEndPara();
            gameOver = true;
        }
    }
}

int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}