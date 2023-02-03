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

public:
    Player(int positionX, int positionY, int room, int HP, int damage, engine* dungeon, char character);

    // getters
    int getRange();
    int getScore();
    int getCollectedArtifacts();
    // level getRoom();

    // setters
    void setScore(int increase);
    void setCollectedArtifacts();
    void setRange(int range);
    // void setRoom(level room);

    // metodi per il movimento
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

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

    // metodo invocato quando si cerca di entrare in una porta
    void checkRoom(char move);

    // update si occupa di modificare lo stato (come posizione e altro) dell'entità
    int update();
};