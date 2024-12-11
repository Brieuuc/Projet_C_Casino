cmake_minimum_required(VERSION 3.30)
project(Projet_C_Casino C)

set(CMAKE_C_STANDARD 11)

include_directories("C:/raylib/raylib/src")
link_directories("C:/raylib/raylib/src")

set(SOURCES
        main.c
        accueil.c
        menu.c
        chicken.c
)

add_executable(Projet_C_Casino ${SOURCES})

target_link_libraries(Projet_C_Casino raylib)

if (MINGW)
    target_link_libraries(Projet_C_Casino gdi32 winmm)
endif()
