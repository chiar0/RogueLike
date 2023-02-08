#include "List.hpp"

    List::List(int nMeelee, int nRanged, engine* dungeon, int id, BulletList* bulletsList, Player*p) {
        meeleeHead = NULL;
        rangedHead = NULL;
        this->id = id;
        this->meeleeNumber = nMeelee;
        this->rangedNumber = nRanged;
        this->defeatedEnemies = 0;
        this->dungeon = dungeon;
        this->bulletsList = bulletsList;
        for (int i = 0; i < nMeelee; i++) { addMeelee(randomMeelee()); }
        for (int i = 0; i < nRanged; i++) { addRanged(randomRanged()); }
        display::point artifactPoint = dungeon->random_clear_point();
        this->artifact = Items(artifactPoint.x, artifactPoint.y, this->dungeon, 'a');
        this->artifactDisplayed = false;
        this->artifactTaken = false;
    }

    // getters
    meeleeList* List::getMeeleeHead() { return meeleeHead; }
    rangedList* List::getRangedHead() { return rangedHead; }
    int List::getId() { return id; }

    // setters
    void List::setDefeatedEnemies() { defeatedEnemies++; }

    // list functions

    // generazione di nemici meelee casuali
    Meelee List::randomMeelee() {
        display::point p = dungeon->random_clear_point();
        Meelee generated = Meelee(p.x, p.y, 15, 3, false, 3, dungeon, bulletsList);
        return generated;
    }

    Ranged List::randomRanged() {
        display::point p = dungeon->random_clear_point();
        Ranged generated = Ranged(p.x, p.y, 10, 5, 7, false, dungeon, bulletsList);
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
        
        defeatedEnemies++;
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

        defeatedEnemies++;
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

    // controllo se un nemico è morto

    void List::checkDeads() {

        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        while(tempMeelee != NULL) {
            if (tempMeelee->meelee.isDead()) {
                removeMeelee(tempMeelee->meelee.getPositionX(), tempMeelee->meelee.getPositionY());
            }
            tempMeelee = tempMeelee->next;
        }

        while(tempRanged != NULL) {
            if (tempRanged->ranged.isDead()) {
                removeRanged(tempRanged->ranged.getPositionX(), tempRanged->ranged.getPositionY());
            }
            tempRanged = tempRanged->next;
        }

    }

    // aggiornamento di tutti i nemici
    void List::updateAll(int playerX, int playerY) {

        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        checkDeads();

        while(tempMeelee != NULL) {
            tempMeelee->meelee.update(playerX, playerY);
            tempMeelee = tempMeelee->next;
        }

        while(tempRanged != NULL) {
            tempRanged->ranged.update(playerX, playerY);
            tempRanged = tempRanged->next;
        }
        
        if (defeatedEnemies == meeleeNumber + rangedNumber && !artifactDisplayed) {
            artifact.display();
            artifactDisplayed = true;
        }
        
        if (playerX == artifact.getPositionX() && playerY == artifact.getPositionY() && artifactDisplayed) {
            artifactTaken = true;
            wmove(dungeon->retrive_dungeon(), artifact.getPositionY(), artifact.getPositionX());
            waddch(dungeon->retrive_dungeon(), ' ');
        }
        

    }

    void List::hideAll() {

        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        while(tempMeelee != NULL) {
            tempMeelee->meelee.hide();
            tempMeelee = tempMeelee->next;
        }

        while(tempRanged != NULL) {
            tempRanged->ranged.hide();
            tempRanged = tempRanged->next;
        }

        if (artifactDisplayed) {
            artifact.hide();
            artifactDisplayed = false;
        }

    }

    void List::displayAll(){
        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        while(tempMeelee != NULL) {
            tempMeelee->meelee.display();
            tempMeelee = tempMeelee->next;
        }

        while(tempRanged != NULL) {
            tempRanged->ranged.display();
            tempRanged = tempRanged->next;
        }

        if (artifactDisplayed) {
            artifact.display();
        }


    }