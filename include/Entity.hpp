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
                                // [0][1] = sopra, [1][0] = sinistra, [1][2] = destra, [2][1] = sotto, [1][1] = entità stessa

    // attributi del gioco
    int HP;                     // punti vita
    int damage;                 // danno che infligge
    BulletList* bulletsList;    // lista di proiettili

public:
    // costruttore
    Entity();
    Entity(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletslist);

    // getters, ritornano i valori degli attributi
    int getPositionX();
    int getPositionY();
    int getMaxX();
    int getMaxY();
    int getHP();
    int getDamage();
    char getCharacter();
    char getNearby(int x, int y);
    WINDOW* getDungeonWindow();

    // setters, impostano i valori degli attributi
    void setPositionX(int x);
    void setPositionY(int y);
    void setHP(int lostHPs);
    void setDamage();
    void setBulletList(BulletList* b);
    
    // metodi che aggiornano lo stato grafico dell'entità
    void display();             // stampa l'entità sulla finestra
    void hide();                // oscura l'entità dalla finestra
    void update();              // aggiorna lo stato dell'entità
    void updateNearby();        // aggiorna la matrice 3x3 che contiene i caratteri nelle caselle adiacenti a quella in cui si trova l'entità


    // metodi di movimento
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // metodi per il combattimento

    // ritorna true se l'entità è morta, se lo è la elimina dalla finestra con hide()
    bool isDead();

    // aggiunge un proiettile alla lista dei proiettili
    void addBullets(int direction, bool isEnemy, int entityX, int entityY);

};
