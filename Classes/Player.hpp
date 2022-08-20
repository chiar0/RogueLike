#include "Entity.hpp"

// Classe usata per il player
class Player: public Entity{

private:
    int damage;
    int score;
    int collectedArtifacts;
    const int DAMAGE_SCALING = 25;

    // setters
    void setScore(int increase) { score += increase; }
    void setCollectedArtifacts() { collectedArtifacts += 1; }
    void setDamage() { damage += DAMAGE_SCALING; }

public:
    Player(int positionX, int positionY, int room, int HP, int damage);

    // getters
    int getDamage();
    int getScore();
    int getCollectedArtifacts();

    // metodo invocato quando si colleziona un artefatto
    void artifactCollected();
    }

    // metodo invocato quando viene affrontato un nemico
    void defeatedEnemy(bool isBoss);

    // update si occupa di modificare lo stato (come posizione e altro) dell'entità ogni input del player
    void update();
    // display serve a far comparire il personaggio su schermo
    void display();
};