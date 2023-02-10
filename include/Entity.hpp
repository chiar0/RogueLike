#pragma once

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include "engine.hpp"
#include "BulletList.hpp"

// Superclasse di tutte le entità che si trovano su schermo, quali player, nemici e artefatti/potenziamenti
class Entity {

protected:

    // attributi necessari alla parte grafica
    int positionX, xMax;        // posizione X nella window e dimensione massima X
    int positionY, yMax;        // posizione Y nella window e dimensione massima Y
    engine *dungeon;            // dungeon in cui si trova l'entità
    char character;             // carattere che rappresenta l'entità
    char nearby[3][3];          // matrice 3x3 che contiene i caratteri nelle caselle adiacenti a quella in cui si trova l'entità

    // attributi del gioco
    int HP;                     // punti vita
    int damage;                 // danno che infligge
    BulletList* bulletsList;    // lista di proiettili

public:
    // costruttore
    Entity();
    Entity(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletslist);

    // getters
    int getPositionX();
    int getPositionY();
    int getMaxX();
    int getMaxY();
    int getHP();
    int getDamage();
    char getCharacter();
    char getNearby(int x, int y);
    WINDOW* getDungeonWindow();

    // setters
    void setPositionX(int x);
    void setPositionY(int y);
    void setHP(int lostHPs);
    void setDamage();
    void setBulletList(BulletList* b);
    
    // metodi che aggiornano lo stato grafico dell'entità
    void display();
    void hide();
    void update();
    void updateNearby();


    // metodi di movimento
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // metodi per il combattimento
    bool isDead();
    // void isHit(int bulletX, int bulletY, int dmg);
    void addBullets(int direction, bool isEnemy, int entityX, int entityY);
    void updateDungeon();                   //setter della nuova BulletList per quando si cambia stanza
};
