cmake_minimum_required(VERSION 3.13)
project(meadow_sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lncurses")

add_executable(meadow_sim
        main.cpp
        Animals/Animal.cpp
        Animals/Animal.h
        Animals/Cow.cpp
        Animals/Cow.h
        Animals/Rabbit.cpp
        Animals/Rabbit.h
        Animals/Wolf.cpp
        Animals/Wolf.h
        Resources/Grass.cpp
        Resources/Grass.h
        Resources/Rabbit_Hole.cpp
        Resources/Rabbit_Hole.h
        Utils/Synchronization.cpp
        Utils/Synchronization.h
        Utils/Utils.cpp
        Utils/Utils.h
        Utils/Graphics.cpp
        Utils/Graphics.h
        Meadow.cpp
        Meadow.h
        Resources/Pond.cpp
        Resources/Pond.h
        Sun.cpp
        Sun.h)