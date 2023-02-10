#include "Game.hpp"

/*
endwin();
printf("test");
exit(1);
*/

Game::Game(){
    //generazione dungeon e nemici
    this->dungeon = new engine();
    BulletList* tmpBullet1 = new BulletList(this->dungeon);
    BulletList* tmpBullet2 = new BulletList(this->dungeon);
    display::point playerSpawn = dungeon->random_clear_point();
    this->p = new Player(playerSpawn.x, playerSpawn.y, 100, 3, dungeon, tmpBullet1);
    

    //generazione lista di liste
    List* tmpList1 = new List(3, 3, dungeon, 0, tmpBullet1, p);
    List* tmpList2 = new List(3, 3, dungeon, 0, tmpBullet1, p);
    this->head = new listOfLists(tmpBullet1, tmpList1);
    this->head->next = new listOfLists(tmpBullet2, tmpList2);
    this->head->next->prev = head;
    this->current = head;
    this->maxId = 1;
    
    //varie funzioni di libreria di ncurses
    nodelay(dungeon->retrive_dungeon(), true);
    nodelay(stdscr, true);
    noecho();
    keypad(stdscr, true);
    keypad(dungeon->retrive_dungeon(), true);
};


void Game::nextList(int nMeelee, int nRanged, engine *dungeon) {
        if (current->next != NULL) {
            current = current->next;
        } else {
            //se non è presente un next allora viene generato
            newList(nMeelee, nRanged, dungeon);     
            current = current->next;
        }
    }


void Game::prevList() {
    if (current->prev != NULL) {
        current = current->prev;
    }
}

void Game::newList(int nMeelee, int nRanged, engine* dungeon) {
    listOfLists *tmp = head;
    maxId += 1;
    BulletList* newBulletList= new BulletList(this->dungeon);
    List* new_list = new List(nMeelee, nRanged, dungeon, maxId, newBulletList, this->p);
    while(head->next != NULL) {
        head = head->next;
    }
    head->next = new listOfLists(newBulletList, new_list);
    head->next->prev = head;
    head = tmp;
}


void Game::gameLoop(){
    
    int changedRoom = 0;
    int meeleeDamage = 0;
    bool end = true;
    int ch;
    float enemyFrameRate = 3.0f;
    float bulletFrameRate = enemyFrameRate * 4;


    while(end){
        changedRoom = 0;
        ch = getch();
        enemyTimer->tick();

        if(ch == 'x')
            end = false;
        if(ch != ERR){
            updatePlayer(ch);
        }
        if(enemyTimer->getDeltaTime() >= 1/enemyFrameRate){

            checkPlayer(current->list->updateAll());
            enemyTimer->reset();
            bulletFrameRate = enemyFrameRate * 4;
        }
            
        if(enemyTimer->getDeltaTime() >= 1/bulletFrameRate){
            
            current->bulletsList->update();
            checkBullets();
            current->bulletsList->display();
            current->list->displayAll(); 
            p->display();
            bulletFrameRate -= enemyFrameRate;
        }

        this->dungeon->refresh_dungeon();
    }
};

void Game::checkBullets(){
    checkPlayer();
    checkRanged();
    checkMeelee();
}


void Game::checkMeelee(){
    meeleeList* auxMeelee;
    auxMeelee = current->list->getMeeleeHead();
    int damageTaken = 0;
    while(auxMeelee != NULL){
        damageTaken = current->bulletsList->isHit(auxMeelee->meelee.getPositionX(), auxMeelee->meelee.getPositionY(), auxMeelee->meelee.getCharacter());
        if(damageTaken > 0) {
            auxMeelee->meelee.setHP(damageTaken);
            auxMeelee->meelee.setIsTaunted(true);
        }
        auxMeelee = auxMeelee->next;
    }
}


void Game::checkRanged(){
    rangedList* auxRanged;
    auxRanged = current->list->getRangedHead();
    int damageTaken = 0;
    while(auxRanged != NULL){
        damageTaken = current->bulletsList->isHit(auxRanged->ranged.getPositionX(), auxRanged->ranged.getPositionY(), auxRanged->ranged.getCharacter());
        if(damageTaken > 0)
            auxRanged->ranged.setHP(damageTaken);
        auxRanged = auxRanged->next;
   }
   
}

void Game::checkPlayer(int damage){
    int damageTaken = current->bulletsList->isHit(p->getPositionX(), p->getPositionY(), '@') + damage;
    if (damageTaken > 0) {
        p->setHP(damageTaken);
        p->isDead();
        dungeon->life_update(-damageTaken);
    }
}


void Game::updatePlayer(int move){
    int changedRoom = p->update(move);
    if (changedRoom != 0) {
        //bulletsList->resetList();
        //bulletsList->getBulletHead();
        p->hide();
        current->bulletsList->hideAll();
        current->list->hideAll();
        switch (changedRoom) {
            case 1:
                {dungeon->next_level();
                int nMeelee = 3 + (maxId/2); if (nMeelee > 12) { nMeelee = 12; }
                int nRanged = 3 + (maxId/2); if (nRanged > 12) { nRanged = 12; }
                nextList(nMeelee, nRanged, this->dungeon);
                display::point_list *entryPoints = dungeon->retrive_entry();
                while(entryPoints->p.x != p->getPositionX() && entryPoints->p.y != p->getPositionY()) {
                    entryPoints = entryPoints->next;
                }
                p->setBulletList(current->bulletsList);
                p->setPositionX(entryPoints->p.x);
                p->setPositionY(entryPoints->p.y);
                break;}
            case 2:
                {dungeon->prev_level();
                prevList();
                display::point_list *exitPoints = dungeon->retrive_exit();
                while(exitPoints->p.x != p->getPositionX() && exitPoints->p.y != p->getPositionY()) {
                    exitPoints = exitPoints->next;
                }
                p->setBulletList(current->bulletsList);
                p->setPositionX(exitPoints->p.x);
                p->setPositionY(exitPoints->p.y);
                break;}
            default:
                break;
        }
    }
    else{
        checkPlayer();
        current->bulletsList->display();
        p->display();
        current->list->displayAll();
    }
}




