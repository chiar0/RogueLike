#include "List.hpp"

    List::List(int nMeelee, int nRanged, engine* dungeon) {
        meeleeHead = NULL;
        rangedHead = NULL;
        this->dungeon = dungeon;
        for (int i = 0; i < nMeelee; i++) { addMeelee(randomMeelee(i)); }
        for (int i = 0; i < nRanged; i++) { addRanged(randomRanged(i)); }
    }

    // getters
    List::meeleeList* List::getMeeleeHead() { return meeleeHead; }
    List::rangedList* List::getRangedHead() { return rangedHead; }

    // list functions

    // generazione di nemici meelee casuali
    Meelee List::randomMeelee(int id) {
        display::point p = dungeon->random_clear_point();
        Meelee generated = Meelee(p.x, p.y, 15, 3, false, 3, dungeon, 'M', id);
        return generated;
    }

    Ranged List::randomRanged(int id) {
        display::point p = dungeon->random_clear_point();
        Ranged generated = Ranged(p.x, p.y, 10, 5, 7, false, dungeon, 'R', id);
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
                    wmove(dungeon->retrive_dungeon(), current->meelee.getPositionY(), current->meelee.getPositionX());
                    waddch(dungeon->retrive_dungeon(), ' ');
                    meeleeHead = current->next;
                } else {
                    wmove(dungeon->retrive_dungeon(), current->meelee.getPositionY(), current->meelee.getPositionX());
                    waddch(dungeon->retrive_dungeon(), ' ');
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
                    wmove(dungeon->retrive_dungeon(), current->ranged.getPositionY(), current->ranged.getPositionX());
                    waddch(dungeon->retrive_dungeon(), ' ');
                    rangedHead = current->next;
                } else {
                    wmove(dungeon->retrive_dungeon(), current->ranged.getPositionY(), current->ranged.getPositionX());
                    waddch(dungeon->retrive_dungeon(), ' ');
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

        while(tempMeelee != NULL) {
            tempMeelee->meelee.update(playerX, playerY);
            tempMeelee = tempMeelee->next;
        }

        while(tempRanged != NULL) {
            tempRanged->ranged.update(playerX, playerY);
            tempRanged = tempRanged->next;
        }
        
    }