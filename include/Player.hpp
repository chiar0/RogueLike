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
        listOfLists* prev;
        listOfLists(List l) : list(l), next(NULL), prev(NULL) {}
    };
    listOfLists* head;
    listOfLists* current;

public:

    Player();
    Player(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletsList);

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
    void shoot(int direction);

    // metodi per il cambio lista di nemici
    void nextList();
    void prevList();
    void newList(int nMeelee, int nRanged, engine* dungeon);

    // metodo cambio stanza
    void changeRoom(int direction);

    // metodo invocato quando viene affrontato un nemico
    void defeatedEnemy(bool isBoss);

    // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    char update(int move);

    //aggiornamento della lista dei proiettili
    int updateBullet();
};