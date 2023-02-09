#include "List.hpp"

    List::List(int nMeelee, int nRanged, engine* dungeon, int id, BulletList* bulletsList, Player*p) {
        this->dungeon = dungeon;
        meeleeHead = NULL;
        rangedHead = NULL;
        this->bulletsList = bulletsList;
        this->p = p;
        display::point artifactPoint = dungeon->random_clear_point();
        this->artifact = Items(artifactPoint.x, artifactPoint.y, this->dungeon, 'a');
        display::point powerUpPoint = dungeon->random_clear_point();
        while(powerUpPoint.x == artifactPoint.x && powerUpPoint.y == artifactPoint.y) powerUpPoint = dungeon->random_clear_point();
        this->powerUp = Items(powerUpPoint.x, powerUpPoint.y, this->dungeon, 'p');
        this->id = id;

        this->meeleeNumber = nMeelee;
        this->rangedNumber = nRanged;
        this->defeatedEnemies = 0;
        for (int i = 0; i < nMeelee; i++) { addMeelee(randomMeelee()); }
        for (int i = 0; i < nRanged; i++) { addRanged(randomRanged()); }
        this->artifactDisplayed = false;
        this->artifactTaken = false;
        this->powerUpDisplayed = false;
        this->powerUpTaken = false;
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
        while(p.x == dungeon->retrive_columns() || p.y == dungeon->retrive_rows() || p.x == 0 || p.y == 0) p = dungeon->random_clear_point();
        Meelee generated = Meelee(p.x, p.y, 15+(id*3/2), 3+id, true, dungeon, bulletsList);
        if (id == dungeon->retrive_level_number()) { generated.display(); }
        return generated;
    }

    Ranged List::randomRanged() {
        display::point p = dungeon->random_clear_point();
        while(p.x == dungeon->retrive_columns() || p.y == dungeon->retrive_rows() || p.x == 0 || p.y == 0) p = dungeon->random_clear_point();
        Ranged generated = Ranged(p.x, p.y, 10+(id*3/2), 5+id, 7, true, dungeon, bulletsList);
        if (id == dungeon->retrive_level_number()) { generated.display(); }
        return generated;
    }

    // aggiunta di nemici meelee
    void List::addMeelee(Meelee meelee) {
        meeleeList* newMeelee = new meeleeList(meelee);
        newMeelee->next = meeleeHead;
        meeleeHead = newMeelee;
    }

    // aggiunta di nemici ranged
    void List::addRanged(Ranged ranged) {
        rangedList* newRanged = new rangedList(ranged);
        newRanged->next = rangedHead;
        rangedHead = newRanged;
    }

    // rimozione di nemici meelee
    void List::removeMeelee(int x, int y) {
        
        defeatedEnemies++;
        meeleeList* current = meeleeHead;
        meeleeList* previous = NULL;
        bool deleted = false;

        while (current != NULL && !deleted) {

            if (current->meelee.getPositionX() == x && current->meelee.getPositionY() == y) {
                if (previous == NULL) { meeleeHead = current->next; }
                else { previous->next = current->next; }
                delete current;
                deleted = true;
            } else {
                previous = current;
                current = current->next;
            }

        }
    }

    // rimozione di nemici ranged
    void List::removeRanged(int x, int y) {

        defeatedEnemies++;
        rangedList* current = rangedHead;
        rangedList* previous = NULL;
        bool deleted = false;

        while (current != NULL && !deleted) {

            if (current->ranged.getPositionX() == x && current->ranged.getPositionY() == y) {
                if (previous == NULL) { rangedHead = current->next; }
                else { previous->next = current->next; }
                delete current;
                deleted = true;
            } else {
                previous = current;
                current = current->next;
            }

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
    void List::updateAll() {

        checkDeads();

        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        while(tempMeelee != NULL) {
            tempMeelee->meelee.update(p->getPositionX(), p->getPositionY());
            tempMeelee = tempMeelee->next;
        }

        while(tempRanged != NULL) {
            tempRanged->ranged.update(p->getPositionX(), p->getPositionY());
            tempRanged = tempRanged->next;
        }
        
        if (defeatedEnemies >= (meeleeNumber + rangedNumber)/2 && !artifactDisplayed && !artifactTaken) {
            artifact.display();
            artifactDisplayed = true;
        }
        
        if (p->getPositionX() == artifact.getPositionX() && p->getPositionY() == artifact.getPositionY() && artifactDisplayed && !artifactTaken) {
            artifactTaken = true;
            artifact.hide();
            artifactDisplayed = false;
        }
        
        if (!powerUpDisplayed && !powerUpTaken) {
            powerUp.display();
            powerUpDisplayed = true;
        }

        if (p->getPositionX() == powerUp.getPositionX() && p->getPositionY() == powerUp.getPositionY() && powerUpDisplayed && !powerUpTaken) {
            powerUpTaken = true;
            powerUp.hide();
            powerUpDisplayed = false;
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

        if (powerUpDisplayed) {
            powerUp.hide();
            powerUpDisplayed = false;
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

        if (!powerUpDisplayed && !powerUpTaken) {
            powerUp.display();
            powerUpDisplayed = true;
        }

    }