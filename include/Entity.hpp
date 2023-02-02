#pragma once

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include "engine.hpp"
// #include "Misc.hpp"

// Superclasse di tutte le entità che si trovano su schermo, quali player, nemici e artefatti/potenziamenti
class Entity {

protected:

    // attributi necessari alla parte grafica
    int positionX, xMax; // posizione X nella window e dimensione massima X
    int positionY, yMax; // posizione Y nella window e dimensione massima Y
    engine *dungeon; // dungeon in cui si trova l'entità
    WINDOW* window; // window in cui si trova l'entità
    char character; // carattere che rappresenta l'entità
    char nearby[3][3]; // matrice 3x3 che contiene i caratteri nelle caselle adiacenti a quella in cui si trova l'entità

    // attributi del gioco
    int HP; // punti vita
    int damage; // danno che infligge

public:
    // costruttore
    Entity(int positionX, int positionY, int room, int HP, int damage, engine* dungeon, char character);

    // getters
    int getPositionX();
    int getPositionY();
    int getMaxX();
    int getMaxY();
    int getHP();
    int getDamage();
    WINDOW* getWindow();
    char getCharacter();
    char getNearby(int x, int y);

    // setters
    void setPositionX(int x);
    void setPositionY(int y);
    void setHP(int lostHPs);
    void setDamage();

    // metodi di movimento
    void display();
    void update();
    void updateNearby();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // metodo invocato per controllare se l'entità ha raggiunto 0 hp
    void isDead();

    // metodo che controlla se ci sono nemici nelle vicinanze
    void isTouched(char *nearbyEntities);
};
