#include "Ranged.hpp"

    Ranged::Ranged(int positionX, int positionY, int HP, int damage, int range, bool isBoss, engine* dungeon, BulletList* bullets)
    :Entity(positionX, positionY, HP, damage, dungeon, bulletsList) {
        this->range = range;
        this->isBoss = isBoss;
        this->character = 'R';
    }

    // getters
    int Ranged::getRange() { return range; }
    bool Ranged::getIsBoss() { return isBoss; }

    // setters
    void Ranged::setRange(int range) { range = range; }

    void Ranged::update(int playerX, int playerY) {
        int dx = playerX - positionX;
        int dy = playerY - positionY;
        int distance = sqrt(dx * dx + dy * dy);
        if (distance <= range + 5) {
            if (positionX == playerX) {
                // shoot up or down
                if(positionY > playerY)
                    shoot(1);
                else
                    shoot(3);
            } else if (positionY == playerY) {
                // shoot left or right
                if(positionX < playerX)
                    shoot(4);
                else
                    shoot(2);
            } else {
                bool direction = abs(dx) < abs(dy);
                if (direction) {
                    if (dx > 0) { moveRight(); }
                    else { moveLeft(); }
                } else {
                    if (dy > 0) { moveDown(); }
                    else { moveUp(); }
                }
            }
        } else {
            int movementChance, direction;
            movementChance = rand()% 3;
            if (movementChance != 0) {
                direction = rand()% 4+1;
                switch (direction) {
                    case 1:
                        moveRight(); break;
                    case 2:
                        moveLeft(); break;
                    case 3:
                        moveUp(); break;
                    case 4:
                        moveDown(); break;
                    default:
                        break;
                }
            }
        }
    }
        /*
    int Ranged::updateBullet(int playerX, int playerY){
        Bul aux = first, prev = first;
        bool alive = false;
        int hit = 0;

        prev = first;
        
        if(first != NULL){
            while(aux != NULL){
                //cancello il proiettile dalla finestra e aggiorno la posizione
                display::point p{aux->bullet.gety(), aux->bullet.getx()};
                dungeon->write_char(p, ' ');
                alive = aux->bullet.move();

                if(alive == true){
                    //se non colpisco niente lo lascio nella lista
                    display::point p{aux->bullet.gety(), aux->bullet.getx()};
                    dungeon->write_char(p, aux->bullet.getChar());
                    //mvwprintw(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx(), "%c", aux->bullet.getChar());
                    //aux->bullet.display();
                    prev = aux;
                    aux = aux->next;
                }

                else{
                    //se colpisco il personaggio salvo i danni
                    char mapChar = mvwinch(dungeon->retrive_dungeon(), aux->bullet.gety(), aux->bullet.getx());
                    if(mapChar == '@'){
                        hit = hit + Ranged::getDamage();
                    }

                    //cancellazione del proiettile dalla lista
                    if(aux == first && first->next == NULL){
                        delete aux;
                        first = NULL;
                        aux = NULL; 
                    }
                    else if(aux == first && first->next != NULL){
                        first = first->next;
                        delete aux;
                        aux = NULL;
                        aux = first;
                    }
                    else{
                        prev->next = aux->next;
                        delete aux;
                        aux = NULL;
                        aux = prev->next;
                    }
                    
                }
            }
        }
        display();

        return hit;
    }; 
    */

    void Ranged::shoot(int direction){
        Entity::addBullets(direction, false);
    }
