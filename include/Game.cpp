#include "Game.hpp"

/*
endwin();
printf("test");
exit(1);
*/

Game::Game(){
    //generazione dungeon e nemici
    this->dungeon = new engine();
    this->bulletsList =  new BulletList(this->dungeon);
    this->bulletsList->startDungeon(dungeon);
    display::point playerSpawn = dungeon->random_clear_point();
    this->p = new Player(playerSpawn.x, playerSpawn.y, 10000, 100, dungeon, this->bulletsList);
    

    //generazione lista di liste
    this->head = new listOfLists(List(0, 2, dungeon, 0, bulletsList, p));
    this->head->next = new listOfLists(List(4, 4, dungeon, 1, bulletsList, p));
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

void Game::nextList() {
        if (current->next != NULL) {
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
    List new_list(nMeelee, nRanged, dungeon, maxId, bulletsList, this->p);
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new listOfLists(new_list);
    tmp->next->prev = tmp;
}

//gestisce il gioco e il tempo
void Game::gameLoop(){
    //molte sono usare per debuggare
    bool end = true;
    int ch;
    float enemyFrameRate = 4.0f;
    float bulletFrameRate = enemyFrameRate * 3;


    while(end){
        int changedRoom = 0;
        ch = getch();
        enemyTimer->tick();

        if(ch == 'x')
            end = false;
        if (ch == 'n') {
            dungeon->clear_exit();
        }
        if(ch != ERR){
            updatePlayer(ch);
            checkPlayer();
            bulletsList->display();
            p->display();
            current->list.displayAll();
        }
        if(enemyTimer->getDeltaTime() >= 1/enemyFrameRate){
            current->list.updateAll(p->getPositionX(), p->getPositionY());
            enemyTimer->reset();
            bulletFrameRate = enemyFrameRate * 3;
        }

        if(enemyTimer->getDeltaTime() >= 1/bulletFrameRate){
            bulletsList->update();
            checkBullets();
            bulletsList->display();
            current->list.displayAll();
            p->display();
            bulletFrameRate -= enemyFrameRate;
        }

        this->dungeon->refresh_dungeon();
    }
};

void Game::genEnemys(int nMeelee, int nRanged){

}

void Game::checkBullets(){
    checkPlayer();
    checkRanged();
    checkMeelee();

}

void Game::checkMeelee(){
    meeleeList* auxMeelee;
    auxMeelee = current->list.getMeeleeHead();
    int damageTaken = 0;
    while(auxMeelee != NULL){
        damageTaken = bulletsList->isHit(auxMeelee->meelee.getPositionX(), auxMeelee->meelee.getPositionY(), auxMeelee->meelee.getCharacter());
        if(damageTaken > 0) {
            auxMeelee->meelee.setHP(damageTaken);
            auxMeelee->meelee.setIsTaunted(true);
        }
        auxMeelee = auxMeelee->next;
    }
}

void Game::checkRanged(){
    rangedList* auxRanged;
    auxRanged = current->list.getRangedHead();
    int damageTaken = 0;
    while(auxRanged != NULL){
        damageTaken = bulletsList->isHit(auxRanged->ranged.getPositionX(), auxRanged->ranged.getPositionY(), auxRanged->ranged.getCharacter());
        if(damageTaken > 0)
            auxRanged->ranged.setHP(damageTaken);
        auxRanged = auxRanged->next;
   }
   
}

void Game::checkPlayer(){
    p->setHP(bulletsList->isHit(p->getPositionX(), p->getPositionY(), '@'));
    if(p->isDead()){ dungeon->gameover(); }
}

void Game::updatePlayer(int move){
    int changedRoom = p->update(move);
    if (changedRoom != 0) {
        switch (changedRoom) {
            case 1:
                {bulletsList->resetList();
                bulletsList->getBulletHead();
                p->hide();
                current->list.hideAll();
                dungeon->refresh_dungeon();
                dungeon->next_level();
                int nMeelee = 4 + (maxId/2); if (nMeelee > 12) { nMeelee = 12; }
                int nRanged = 4 + (maxId/2); if (nRanged > 12) { nRanged = 12; }
                if (dungeon->retrive_level_number() > maxId) { newList(nMeelee, nRanged, this->dungeon); }
                nextList();
                display::point_list *entryPoints = dungeon->retrive_entry();
                while(entryPoints->p.x != p->getPositionX() && entryPoints->p.y != p->getPositionY()) {
                    entryPoints = entryPoints->next;
                }
                p->setPositionX(entryPoints->p.x);
                p->setPositionY(entryPoints->p.y);
                break;}
            case 2:
                {bulletsList->resetList();
                bulletsList->getBulletHead();
                p->hide();
                current->list.hideAll();
                dungeon->refresh_dungeon();
                dungeon->prev_level();
                prevList();
                display::point_list *exitPoints = dungeon->retrive_exit();
                while(exitPoints->p.x != p->getPositionX() && exitPoints->p.y != p->getPositionY()) {
                    exitPoints = exitPoints->next;
                }
                p->setPositionX(exitPoints->p.x);
                p->setPositionY(exitPoints->p.y);
                break;}
            default:
                break;
        }
    }
}
