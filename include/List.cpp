#include "List.hpp"

    List::List(int nMeelee, int nRanged, engine* dungeon, BulletList* bulletsList) {
        meeleeHead = NULL;
        rangedHead = NULL;
        this->dungeon = dungeon;
        this->bulletsList = bulletsList;
        for (int i = 0; i < nMeelee; i++) { addMeelee(randomMeelee(i)); }
        for (int i = 0; i < nRanged; i++) { addRanged(randomRanged(i)); }
    }

    // getters
    meeleeList* List::getMeeleeHead() { return meeleeHead; }
    rangedList* List::getRangedHead() { return rangedHead; }

    // list functions

    // generazione di nemici meelee casuali
    Meelee List::randomMeelee(int id) {
        display::point p = dungeon->random_clear_point();
        Meelee generated = Meelee(p.x, p.y, 15, 3, false, 3, dungeon, 'M', id, this->bulletsList);
        return generated;
    }

    Ranged List::randomRanged(int id) {
        display::point p = dungeon->random_clear_point();
        Ranged generated = Ranged(p.x, p.y, 10, 5, 7, false, dungeon, 'R', id, this->bulletsList);
        return generated;
    }

    // aggiunta di nemici meelee
    void List::addMeelee(Meelee meelee) {
        meeleeList* newMeelee = new meeleeList(meelee);
        newMeelee->next = meeleeHead;
        meeleeHead = newMeelee;
        newMeelee->meelee.display();
    }

    // aggiunta di nemici ranged
    void List::addRanged(Ranged ranged) {
        rangedList* newRanged = new rangedList(ranged);
        newRanged->next = rangedHead;
        rangedHead = newRanged;
        newRanged->ranged.display();
    }

    // rimozione di nemici meelee
    void List::removeMeelee(int x, int y) {
        meeleeList* current = meeleeHead;
        meeleeList* previous = NULL;
        while (current != NULL) {
            if (current->meelee.getPositionX() == x
                && current->meelee.getPositionY() == y) {
                if (previous == NULL) {
                    display::point p{current->meelee.getPositionY(), current->meelee.getPositionY()};
                    dungeon->write_char(p, ' ');
                    //wmove(dungeon->retrive_dungeon(), current->meelee.getPositionY(), current->meelee.getPositionX());
                    //waddch(dungeon->retrive_dungeon(), ' ');
                    meeleeHead = current->next;
                } else {
                    display::point p{current->meelee.getPositionY(), current->meelee.getPositionY()};
                    dungeon->write_char(p, ' ');
                    //wmove(dungeon->retrive_dungeon(), current->meelee.getPositionY(), current->meelee.getPositionX());
                    //waddch(dungeon->retrive_dungeon(), ' ');
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }

    // rimozione di nemici ranged
    void List::removeRanged(int x, int y) {
        rangedList* current = rangedHead;
        rangedList* previous = NULL;
        while (current != NULL) {
            if (current->ranged.getPositionX() == x
                && current->ranged.getPositionY() == y) {
                if (previous == NULL) {
                    display::point p{current->ranged.getPositionY(), current->ranged.getPositionY()};
                    dungeon->write_char(p, ' ');
                    //wmove(dungeon->retrive_dungeon(), current->ranged.getPositionY(), current->ranged.getPositionX());
                    //waddch(dungeon->retrive_dungeon(), ' ');
                    rangedHead = current->next;
                } else {
                    display::point p{current->ranged.getPositionY(), current->ranged.getPositionY()};
                    dungeon->write_char(p, ' ');
                    //wmove(dungeon->retrive_dungeon(), current->ranged.getPositionY(), current->ranged.getPositionX());
                    //waddch(dungeon->retrive_dungeon(), ' ');
                    previous->next = current->next;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->next;
        }
    }
    
    void List::updateAll(int playerX, int playerY) {
        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;
        int killedX, killedY;
        while(tempMeelee != NULL) {
            if(tempMeelee->meelee.getHP() > 0){
                tempMeelee->meelee.update(playerX, playerY);
                tempMeelee = tempMeelee->next;
            }
            else{
                killedX = tempMeelee->meelee.getPositionX();
                killedY = tempMeelee->meelee.getPositionY();
                tempMeelee = tempMeelee->next;
                removeMeelee(killedY, killedX);
            }
        }
        while(tempRanged != NULL) {
            if(tempRanged->ranged.getHP() > 0){
                tempRanged->ranged.update(playerX, playerY);
                tempRanged = tempRanged->next;
            }
            else{
                killedX = tempRanged->ranged.getPositionX();
                killedY = tempRanged->ranged.getPositionY();
                tempRanged= tempRanged->next;
                removeRanged(killedY, killedX);
            }
        }
    }

    void List::isHit(int bulletX, int bulletY, int damage) {
        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;
        while(tempMeelee != NULL) {
            tempMeelee->meelee.isHit(bulletX, bulletY, damage);
            tempMeelee = tempMeelee->next;
        }
        while(tempRanged != NULL) {
            tempRanged->ranged.isHit(bulletX, bulletY, damage);
            tempRanged = tempRanged->next;
        }
    }

