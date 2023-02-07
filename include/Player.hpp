#pragma once

#include "Entity.hpp"
#include "List.hpp"

// Classe usata per il player
class Player: public Entity{

private: 
    int score; // punteggio del player
    int range; // distanza massima di attacco
    int collectedArtifacts; // numero di artefatti raccolti
    int bulletsRemaining; // numero di proiettili rimanenti
    int maxId;

    struct listOfLists {
        List list;
        listOfLists* next;
        listOfLists(List l) : list(l), next(NULL) {}
    };
    listOfLists* head;
    List* current;

public:
    Player(int positionX, int positionY, int HP, int damage, engine* dungeon);

    // getters
    int getRange();
    int getScore();
    int getCollectedArtifacts();
    int getMaxId();

    // setters
    void setScore(int increase);
    void setCollectedArtifacts();
    void setRange(int range);

    // metodi per il movimento
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // metodo cambio stanza
    void changeRoom(int direction);

    // metodi per il combattimento
    void attack(int y, int x);
    void attackUp();
    void attackDown();
    void attackLeft();
    void attackRight();

    // list of List functions
    void setCurrent(int id);                    // imposta la lista corrente
    void newList(int nMeelee, int nRanged, engine* dungeon);                   // aggiunge una lista alla lista di liste

    // metodo invocato quando viene affrontato un nemico
    void defeatedEnemy(bool isBoss);

    // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    char update();
};