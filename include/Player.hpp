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
    int moveUp();
    int moveDown();
    int moveLeft();
    int moveRight();
    void shoot(int direction);

    // metodo cambio stanza
    int changeRoom(int direction);

    // metodo invocato quando viene affrontato un nemico
    void defeatedEnemy(bool isBoss);

    // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    int update(int move);

    //aggiornamento della lista dei proiettili
    int updateBullet();
};