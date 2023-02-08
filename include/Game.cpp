#include "Game.hpp"

/*
endwin();
printf();
exit();
*/


Game::Game(){
    //generazione dungeon e nemici
    this->dungeon = new engine();
    this->bulletsList =  new BulletList(this->dungeon);
    this->bulletsList->startDungeon(dungeon);
    this->enemies = new List(4, 4, dungeon, 4, this->bulletsList);
    this->p = new Player(dungeon->random_clear_point().x, dungeon->random_clear_point().y, 50, 50, dungeon, this->bulletsList);

    //generazione lista di liste
    this->head = new listOfLists(List(0, 0, dungeon, 0, bulletsList));
    this->head->next = new listOfLists(List(0, 0, dungeon, 1, bulletsList));
    this->head->next->prev = head;
    this->current = head;
    this->maxId = 1;
    
    //generazione finestra di debug
    /*
    this->debug = newwin(7, 120, 1, 10);
    box(debug, 0, 0);
    refresh();
    wrefresh(debug);
    */
    
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
    List new_list(nMeelee, nRanged, dungeon, maxId, bulletsList);
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
    int tps1 = time(0), cps, tps2;
    updateCounter = 2;
    int copia;
    int updateProjectile = 1;


    while(end){
        ch = getch();
        halfdelay(1);

        tps2 = time(0);
        cps = abs(tps2 - tps1)*1000/(tick+50);

        if(ch == 'x')
            end = false;
        if(ch != ERR){
            copia = ch; //la uso per vedere cosa ottiene in input
            p->update(ch);
            checkPlayer();
            bulletsList->display();
            p->display();
            //enemys->updateAll(p->getPositionX(), p->getPositionY());
        }
        
        if(cps > updateCounter){
            enemies->updateAll(p->getPositionX(), p->getPositionY());
            tps1 = time(0);

        }
        if(cps > updateProjectile){
            checkBullets();
            //checkBullets(true);
            bulletsList->update();
            bulletsList->display();
            enemies->displayAll();
            p->display();
        }

        this->dungeon->refresh_dungeon();
        
        
        //gestione finestra di debug
        /*
        bullets* tmp = bulletsList->getBulletHead();
        if(false){
            int ver = 0;
            if(tmp == NULL) ver = 1;
            werase(debug);
            mvwprintw(debug, 1, 1, "xp = %d, yp = %d", tmp->bullet.getx(), tmp->bullet.gety());
            mvwprintw(debug, 2, 1, "upc = %d\t, clock = %d\t, tps2 = %d",  updateCounter, tps, ver);
            mvwprintw(debug, 3, 1, "click = %c, length = %d\n, hit = %d",  (char)copia, bulletsList->listLength(), hacolpito);
        }
        int ver = 0;
        
        wrefresh(debug);
        */
        
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
    auxMeelee = enemies->getMeeleeHead();
    bool hit = false;
    while(auxMeelee != NULL){
        hit = bulletsList->isHit(auxMeelee->meelee.getPositionX(), auxMeelee->meelee.getPositionY(), auxMeelee->meelee.getCharacter());
        auxMeelee = auxMeelee->next;
    }
}

void Game::checkRanged(){
    rangedList* auxRanged;
    auxRanged = enemies->getRangedHead();
    bool hit = false;
    while(auxRanged != NULL){
        hit = bulletsList->isHit(auxRanged->ranged.getPositionX(), auxRanged->ranged.getPositionY(), auxRanged->ranged.getCharacter());
        auxRanged = auxRanged->next;
   }
   
}

void Game::checkPlayer(){
   bulletsList->isHit(p->getPositionX(), p->getPositionY(), '@');
}




