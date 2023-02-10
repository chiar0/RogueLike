#pragma once

#include <time.h>
#include "Entity.hpp"
#include "Ranged.hpp"
#include "Meelee.hpp"
#include "Player.hpp"
#include "Items.hpp"
#include "engine.hpp"

// lista dinamica di nemici meelee
struct meeleeList {
    Meelee meelee;
    meeleeList* next;
    meeleeList(Meelee m) : meelee(m), next(NULL) {}
};

// lista dinamica di nemici ranged
struct rangedList {
    Ranged ranged;
    rangedList* next;
    rangedList(Ranged r) : ranged(r), next(NULL) {}
};

class List {

protected:
    
    meeleeList* meeleeHead;     // testa della lista di nemici meelee 
    rangedList* rangedHead;     // testa della lista di nemici ranged
    BulletList* bulletsList;    // lista di proiettili
    Player* p;                  // puntatore al giocatore
    Items artifact;             // artefatto della stanza
    Items powerUp;              // powerUp della stanza
    engine* dungeon;            // puntatore al dungeon
    int id;                     // id della stanza (parte da 0)

    int meeleeNumber;           // numero di nemici meelee nella stanza
    int rangedNumber;           // numero di nemici ranged nella stanza
    int defeatedEnemies;        // numero di nemici sconfitti nella stanza
    bool artifactDisplayed;     // flag per la visualizzazione dell'artefatto
    bool artifactTaken;         // flag per la raccolta dell'artefatto
    bool powerUpDisplayed;      // flag per la visualizzazione del powerUp
    bool powerUpTaken;          // flag per la raccolta del powerUp

public:

    List(int nMeelee, int nRanged, engine* dungeon, int id, BulletList* bulletsList, Player* p);

    // getters
    meeleeList* getMeeleeHead();
    rangedList* getRangedHead();
    int getId();

    // setters
    void setDefeatedEnemies();

    // list functions
    Meelee randomMeelee();                  // genera nemico meelee casuale
    Ranged randomRanged();                  // genera nemico ranged casuali
    void addMeelee(Meelee meelee);          // aggiunge un nemico meelee alla lista
    void addRanged(Ranged ranged);          // aggiunge un nemico ranged alla lista
    void removeMeelee(int x, int y);        // rimuove un nemico meelee dalla lista date le coordinate
    void removeRanged(int x, int y);        // rimuove un nemico ranged dalla lista date le coordinate
    void checkDeads();                      // controlla se i nemici sono morti
    int updateAll();                        // aggiorna tutti i nemici della lista
    void hideAll();                         // nasconde tutti i nemici, artefatti e potenziamenti della lista
    void displayAll();                      // mostra tutti i nemici, artefatti e potenziamenti della lista
    void clearMeeleeAttack();               // pulisce dallo schermo l'attacco dei nemici meelee
};