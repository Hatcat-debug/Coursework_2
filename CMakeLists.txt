cmake_minimum_required(VERSION 4.0)
project(Coursework_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Coursework_2
        main.cpp
        Room.cpp
        Room.h
        State.cpp
        State.h
        strings.h
        wordwrap.cpp
        wordwrap.h
        GameObject.cpp
        GameObject.h
        Weapon.cpp
        Weapon.h
        Food.cpp
        Food.h
        EnemyObject.cpp
        EnemyObject.h
        Boss.cpp
        Boss.h
        Clowns.cpp
        Clowns.h)
