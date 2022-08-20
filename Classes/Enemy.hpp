#include "Entity.hpp"
#include <time.h>
#include <cstdlib>

// Classe usata per i nemici
class Enemy: public Entity {

protected:
    int damage;
    bool isBoss;
    bool isTaunted; // true se player.isTouched == true, il nemico segue il player per chaseBlocks caselle
    int chaseBlocks;
    int currentChaseBlocks;


public:
    Enemy(int positionX, int positionY, int room, int HP, int damage, bool isBoss, int chaseBlocks);

    // getters
    int getDamage();
    bool getIsBoss();

    // update con movimento non certo in direzioni casuali (dx, sx, up, down)
    void update(int playerX, int playerY, bool isTaunted);
};