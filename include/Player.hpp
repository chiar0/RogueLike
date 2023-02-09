#pragma once

#include "Entity.hpp"

// Classe usata per il player
class Player: public Entity{

private: 
    int score;                  // punteggio del player
    int range;                  // distanza massima di attacco
    int collectedArtifacts;     // numero di artefatti raccolti
    int collectedPowerUps;      // numero di powerUp raccolti
    int bulletsRemaining;       // numero di proiettili rimanenti
    
public:

    // costruttore
    Player();
    Player(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletsList);

    // getters
    int getRange();
    int getScore();
    int getCollectedArtifacts();
    int getCollectedPowerUps();

    // setters
    void setScore(int increase);
    void setCollectedArtifacts();
    void setCollectedPowerUps();
    void setRange(int range);
    void powerUpDamage(int increase);
    void powerUpHP(int increase);

    // metodi per il movimento
    int moveUp();
    int moveDown();
    int moveLeft();
    int moveRight();
    void shoot(int direction);

    int changeRoom(int direction);      // metodo cambio stanza
    void defeatedEnemy(bool isBoss);    // metodo invocato quando viene affrontato un nemico
    int update(int move);               // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    int updateBullet();                 //aggiornamento della lista dei proiettili
};