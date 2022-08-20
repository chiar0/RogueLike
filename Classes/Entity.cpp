#include "Entity.hpp"

    void Entity::setPositionX(int newX) { positionX = newX; }
    void Entity::setPositionY(int newY) { positionY = newY; }
    void Entity::setHP (int lostHPs) { HP = HP - lostHPs; }

    Entity::Entity(int positionX, int positionY, int room, int HP, WINDOW* window, char character){
        this->positionX = positionX;
        this->positionY = positionY;
        this->room = room;
        this->HP = HP;
        this->window = window;
        this->character = character;
        this-> xMax = getmaxx(this->window);
        this-> yMax = getmaxy(this->window);
    }

    int Entity::getPositionX() { return positionX; }
    int Entity::getPositionY() { return positionY; }
    int Entity::getRoom() { return room; }
    int Entity::getHP() { return HP; }
    WINDOW* Entity::getWindow() { return window; }

    void Entity::setHP (int lostHPs) { HP = HP - lostHPs; }
    void Entity::setPositionX (int x) { positionX = x};
    void Entity::setPositionY (int y) { positionY = y};

    void Entity::display(){
        wmove(window, getPositionY(), getPositionX());
        waddch(window, character);
        mvwprintw(window, 0, 0, "%d %d", getPositionY(), getPositionX());
    };

    void Entity::moveUp(){
        wmove(window, positionY, positionX);
        waddch(window, ' ');
        if(positionY < 1) { positionY = 1; }
        else { positionY = positionY - 1; }
    }
    void Entity::moveDown(){
        wmove(window, positionY, positionX);
        waddch(window, ' ');
        if(positionY > yMax-2) { positionY = yMax - 2; }
        else { positionY = positionY - 1; }
    }
    void Entity::moveLeft(){
        wmove(window, positionY, positionX);
        waddch(window, ' ');
        int tempX = positionX;
        mvwprintw(window, 0, 10, "%d %d", positionX, tempX);
        while(positionX >= tempX) {
            positionX--;
        }
        if(positionX != tempX)
            positionX--;
        if(positionX < 1)
            positionX = 1;
    }
    void Entity::moveRight(){
        wmove(window, positionY, positionX);
        waddch(window, ' ');
        if(positionX > xMax-2) { positionY = xMax - 2; }
        else { positionX = positionX += 1; }
    }

    bool Entity::isDead() {
        if (HP <= 0)
            return true;
        else
            return false;
    }