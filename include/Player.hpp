#pragma once

#include "Entity.hpp"


// Classe usata per il player
class Player: public Entity{

private: 
    int score; // punteggio del player
    int range; // distanza massima di attacco
    int collectedArtifacts; // numero di artefatti raccolti
    int bulletsRemaining; // numero di proiettili rimanenti
    // level room; // stanza in cui si trova il player
    int maxId;

public:
    Player();
    Player(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletsList);

    // getters
    int getRange();
    int getScore();
    int getCollectedArtifacts();

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

    // metodo invocato quando si colleziona un artefatto
    void artifactCollected();

    // metodo invocato quando viene affrontato un nemico
    void defeatedEnemy(bool isBoss);

    // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    char update(int move);

    void setCurrent(int id);
    void newList(int nMeelee, int nRanged, engine* dungeon);


    //aggiornamento della lista dei proiettili
    int updateBullet();
    void shoot(int direction);
};