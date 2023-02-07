#pragma once

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include "engine.hpp"

class Items {

protected:

    int positionX, xMax; // posizione X nella window e dimensione massima X
    int positionY, yMax; // posizione Y nella window e dimensione massima Y
    engine *dungeon; // dungeon in cui si trova l'entità
    char character; // carattere che rappresenta l'entità

public:

    // costruttore
    Items() = default;
    Items(int positionX, int positionY, engine* dungeon, char character);

    // getters
    int getPositionX();
    int getPositionY();
    int getMaxX();
    int getMaxY();

    // metodi per la gestione su schermo
    void hide();
    void display();

};