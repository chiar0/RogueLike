#pragma once

#include "Entity.hpp"
#include "Ranged.hpp"
#include "Meelee.hpp"
#include "Items.hpp"
#include "engine.hpp"

class List {

protected:
    
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

    meeleeList* meeleeHead;
    rangedList* rangedHead;
    Items artifact;
    engine* dungeon;
    int id;

    int meeleeNumber;
    int rangedNumber;
    int defeatedEnemies;
    bool artifactDisplayed;
    bool artifactTaken;

public:

    List(int nMeelee, int nRanged, engine* dungeon, int id);

    // getters
    meeleeList* getMeeleeHead();
    rangedList* getRangedHead();
    int getId();

    // setters
    void setDefeatedEnemies();

    // list functions
    Meelee randomMeelee();                // genera nemico meelee casuale
    Ranged randomRanged();                // genera nemico ranged casuali
    void addMeelee(Meelee meelee);              // aggiunge un nemico meelee alla lista
    void addRanged(Ranged ranged);              // aggiunge un nemico ranged alla lista
    void removeMeelee(int x, int y);            // rimuove un nemico meelee dalla lista date le coordinate
    void removeRanged(int x, int y);            // rimuove un nemico ranged dalla lista date le coordinate
    void checkDeads();
    void updateAll(int playerX, int playerY);   // aggiorna tutti i nemici della lista
    void hideAll();                             // nasconde tutti i nemici, artefatti e potenziamenti della lista

};