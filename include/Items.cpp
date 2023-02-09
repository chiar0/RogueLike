#include "Items.hpp"

    // costruttore
    Items::Items(int positionX, int positionY, engine* dungeon, char character) {
        this->positionX = positionX;
        this->positionY = positionY;
        this->dungeon = dungeon;
        this->character = character;
    }

    // getters
    int Items::getPositionX() { return positionX; }
    int Items::getPositionY() { return positionY; }
    int Items::getMaxX() { return xMax; }
    int Items::getMaxY() { return yMax; }

    // si sposta sulla posizione dell'entità e aggiunge il carattere relativo
    void Items::display() {
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        waddch(dungeon->retrive_dungeon(), character);
    }

    // si sposta sulla posizione dell'entità e aggiunge il carattere vuoto
    void Items::hide() {
        wmove(dungeon->retrive_dungeon(), positionY, positionX);
        waddch(dungeon->retrive_dungeon(), ' ');
    }