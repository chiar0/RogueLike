#pragma once

#include "Entity.hpp"
#include <time.h>
#include <cstdlib>

// Classe usata per i nemici
class Meelee: public Entity {

protected:
    bool isBoss;            // = true se è un boss (più forte, più vita, più danno)
    bool isTaunted;         // se = true, il nemico si muove verso il player per n = chaseBlocks mosse
    int chaseBlocks; 
    int currentChaseBlocks; // numero di caselle per le quali il nemico deve ancora seguire il player prima di smettere di essere "taunted"
    int startAttackX;       // coordinate iniziali dell'attacco
    int startAttackY;       // coordinate iniziali dell'attacco

public:
    Meelee(int positionX, int positionY, int HP, int damage, bool isBoss, engine* dungeon, BulletList* bulletesList);

    // getters
    bool getIsBoss();
    bool getIsTaunted();
    int getCurrentChaseBlocks();

    // setters
    void setIsTaunted(bool isTaunted);

    // controlla se c'è un nemico in range di attacco in una certa direzione usando la matrice di adiacenza
    bool isInRange(int x, int y, int direction);

    // update con movimento non certo in direzioni casuali (dx, sx, up, down)
    int update(int playerX, int playerY);                   //funzione per l'update
    int attack(int direction,int playerX, int playerY);     //funzione per l'attacco 
    void clearAttack();                                     //funzone per pulire il dungeon dopo l'attacco
};