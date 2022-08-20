#include <ncurses.h>

// Superclasse di tutte le entità che si trovano su schermo, quali player, nemici e artefatti/potenziamenti
class Entity {

private:

    // attributi necessari alla parte grafica
    int positionX, xMax;
    int positionY, yMax;
    WINDOW* window;
    char character;

    // attributi del gioco
    int room;
    int HP;

public:
    // costruttore
    Entity(int positionX, int positionY, int room, int HP, WINDOW* window, char character);

    // getters, ritornano i campi protetti della classe
    int getPositionX();
    int getPositionY();
    int getRoom();
    int getHP();
    WINDOW* getWindow();

    // setters
    void setHP (int lostHPs);
    void setPositionX (int x);
    void setPositionY (int y);

    // metodi di movimento
    void display();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // metodo invocato per controllare se l'entità ha raggiunto 0 hp
    bool isDead();
};
