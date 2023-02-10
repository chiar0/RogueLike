#include "List.hpp"

    List::List(int nMeelee, int nRanged, engine* dungeon, int id, BulletList* bulletsList, Player*p) {
        this->dungeon = dungeon;
        // inizializzazione teste delle liste
        meeleeHead = NULL;
        rangedHead = NULL;
        this->bulletsList = bulletsList;
        this->p = p;
        // scelgo un punto casuale libero per l'artefatto e un punto casuale libero per il powerUp, controllando che non siano gli stessi
        display::point artifactPoint = dungeon->random_clear_point();
        this->artifact = Items(artifactPoint.x, artifactPoint.y, this->dungeon, 'a');
        display::point powerUpPoint = dungeon->random_clear_point();
        while(powerUpPoint.x == artifactPoint.x && powerUpPoint.y == artifactPoint.y) powerUpPoint = dungeon->random_clear_point();
        this->powerUp = Items(powerUpPoint.x, powerUpPoint.y, this->dungeon, 'p');
        this->id = id;

        this->meeleeNumber = nMeelee;
        this->rangedNumber = nRanged;
        this->defeatedEnemies = 0;
        // aggiungo i nemici alla lista
        for (int i = 0; i < nMeelee; i++) { addMeelee(randomMeelee()); }
        for (int i = 0; i < nRanged; i++) { addRanged(randomRanged()); }
        // inizializzazione flag
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
        // scelgo un punto casuale libero e mi assicuro che non sia un bordo
        display::point p = dungeon->random_clear_point();
        while(p.x == dungeon->retrive_columns() || p.y == dungeon->retrive_rows() || p.x == 1 || p.y == 1) p = dungeon->random_clear_point();
        // scelgo se il nemico è un boss o meno casualmente, se è un boss moltiplico i valori di vita e danno per 2
        int bossMultiplier = 1;
        bool isBoss = false;
        int choice = rand() % 4;
        if (choice == 3) { bossMultiplier = 2; isBoss = true;}
        Meelee generated = Meelee(p.x, p.y, (15+(id*3/2))*bossMultiplier, (3+id)*bossMultiplier, isBoss, dungeon, bulletsList);
        return generated;
    }

    Ranged List::randomRanged() {
        // scelgo un punto casuale libero e mi assicuro che non sia un bordo
        display::point p = dungeon->random_clear_point();
        while(p.x == dungeon->retrive_columns() || p.y == dungeon->retrive_rows() || p.x == 1 || p.y == 1) p = dungeon->random_clear_point();
        // scelgo se il nemico è un boss o meno casualmente, se è un boss moltiplico i valori di vita e danno per 2
        int bossMultiplier = 1;
        bool isBoss = false;
        int choice = rand() % 4;
        if (choice == 3) { bossMultiplier = 2; isBoss = true;}
        Ranged generated = Ranged(p.x, p.y, (10+(id*3/2))*bossMultiplier, (5+id)*bossMultiplier, 7, isBoss, dungeon, bulletsList);
        return generated;
    }

    // aggiunta di nemici meelee alla lista
    void List::addMeelee(Meelee meelee) {
        meeleeList* newMeelee = new meeleeList(meelee);
        newMeelee->next = meeleeHead;
        meeleeHead = newMeelee;
    }

    // aggiunta di nemici ranged alla lista
    void List::addRanged(Ranged ranged) {
        rangedList* newRanged = new rangedList(ranged);
        newRanged->next = rangedHead;
        rangedHead = newRanged;
    }

    // rimozione di nemici meelee
    void List::removeMeelee(int x, int y) {
        
        defeatedEnemies++;          // incremento il numero di nemici sconfitti
        dungeon->count_update(1);   // aggiorno il contatore della finestra di gioco
        meeleeList* current = meeleeHead;
        meeleeList* previous = NULL;
        bool deleted = false;

        while (current != NULL && !deleted) {

            if (current->meelee.getPositionX() == x && current->meelee.getPositionY() == y) {
                current->meelee.clearAttack();
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

        defeatedEnemies++;          // incremento il numero di nemici sconfitti
        dungeon->count_update(1);   // aggiorno il contatore della finestra di gioco
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

    // controllo se ci sono nemici morti e li rimuovo
    void List::checkDeads() {

        meeleeList *tempMeelee = meeleeHead;
        meeleeList *auxMeelee;
        rangedList *tempRanged = rangedHead;
        rangedList *auxRanged;

        while(tempMeelee != NULL) {
            auxMeelee = tempMeelee->next;
            if (tempMeelee->meelee.isDead()) {
                removeMeelee(tempMeelee->meelee.getPositionX(), tempMeelee->meelee.getPositionY());
            }
            tempMeelee = auxMeelee;
        }

        while(tempRanged != NULL) {
            auxRanged = tempRanged->next;
            if (tempRanged->ranged.isDead()) {
                removeRanged(tempRanged->ranged.getPositionX(), tempRanged->ranged.getPositionY());
            }
            tempRanged = auxRanged;
        }

    }

    // aggiornamento di tutti i nemici singolarmente, non prima di aver controllato se ci sono nemici morti
    // controllo inoltre se è stato preso l'artefatto o il potenziamento
    int List::updateAll() {
        int meeleeDamage = 0;
        checkDeads();

        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        while(tempMeelee != NULL) {
            meeleeDamage += tempMeelee->meelee.update(p->getPositionX(), p->getPositionY());
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
        return meeleeDamage;
    }

    // metodo per nascondere tutti i nemici e il potenziamento se non è stato preso
    void List::hideAll() {

        meeleeList *tempMeelee = meeleeHead;
        rangedList *tempRanged = rangedHead;

        while(tempMeelee != NULL) {
            tempMeelee->meelee.hide();
            tempMeelee->meelee.clearAttack();
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

    // metodo per mostrare tutti i nemici e il potenziamento se non è stato preso
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

    // metodo per pulire il residuo di attacco dei nemici meelee
    void List::clearMeeleeAttack(){
        meeleeList *tempMeelee = meeleeHead;

        while(tempMeelee != NULL) {
            tempMeelee->meelee.clearAttack();
            tempMeelee = tempMeelee->next;
        }
    }