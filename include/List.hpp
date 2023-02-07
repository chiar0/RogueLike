#pragma once

#include "Entity.hpp"
#include "Ranged.hpp"
#include "Meelee.hpp"
#include "engine.hpp"
#include "BulletList.hpp"

struct meeleeList {
        Meelee meelee;
        meeleeList* next;
        meeleeList(Meelee m) : meelee(m), next(NULL) {}
    };

    struct rangedList {
        Ranged ranged;
        rangedList* next;
        rangedList(Ranged r) : ranged(r), next(NULL) {}
    };

class List {

protected:
    meeleeList* meeleeHead;
    rangedList* rangedHead;
    engine* dungeon;
    BulletList* bulletsList;

public:

    List(int nMeelee, int nRanged, engine* dungeon, BulletList* bullets);

    // getters
    meeleeList* getMeeleeHead();
    rangedList* getRangedHead();

    // list functions

    Meelee randomMeelee(int id);        // genera nemico meelee casuale
    Ranged randomRanged(int id);        // genera nemico ranged casuali
    void addMeelee(Meelee meelee);      // aggiunge un nemico meelee alla lista
    void addRanged(Ranged ranged);      // aggiunge un nemico ranged alla lista
    void removeMeelee(int x, int y);    // rimuove un nemico meelee dalla lista date le coordinate
    void removeRanged(int x, int y);    // rimuove un nemico ranged dalla lista date le coordinate
    void updateAll(int playerX, int playerY);                   // aggiorna tutti i nemici della lista
    //non implementata bene
    void isHit(int bulletX, int bulletY, int damage);           //aggiorno la vita di tutti i nemici
};