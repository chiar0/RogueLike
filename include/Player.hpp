#pragma once

#include "Entity.hpp"

// Classe usata per il player
class Player: public Entity{

private: 
    int score;                  // punteggio del player
    int collectedArtifacts;     // numero di artefatti raccolti
    int collectedPowerUps;      // numero di powerUp raccolti
    int bulletsRemaining;       // numero di proiettili rimanenti
    
public:

    // costruttore
    Player();
    Player(int positionX, int positionY, int HP, int damage, engine* dungeon, BulletList* bulletsList);

    // getters
    int getCollectedArtifacts();
    int getCollectedPowerUps();

    // setters
    void setCollectedArtifacts();       
    void setCollectedPowerUps();        
    void powerUpDamage(int increase);   // aumenta il danno del player quando prende il powerUp
    void powerUpHP(int increase);       // aumenta la vita del player quando prende il powerUp

    // metodi per il movimento
    int moveUp();
    int moveDown();
    int moveLeft();
    int moveRight();

    void shoot(int direction);          // metodo per sparare
    int changeRoom(int direction);      // metodo cambio stanza
    int update(int move);               // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    int updateBullet();                 // aggiornamento della lista dei proiettili
};