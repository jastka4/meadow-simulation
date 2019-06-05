cmake_minimum_required(VERSION 3.13)
project(meadow_sim)

set(CMAKE_CXX_STANDARD 17)

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
        Grass.cpp
        Grass.h
        Resources/Rabbit_Hole.cpp
        Resources/Rabbit_Hole.h
        Meadow.cpp
        Meadow.h
        Pond.cpp
        Pond.h
        Sun.cpp
        Sun.h Synchronization.cpp Synchronization.h)
        Utils.cpp
        Utils.h)