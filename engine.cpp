#include "engine.hpp"

extern bool debug = true; //se true, attiva la modalità debug

engine::engine() { //costruttore della classe engine (inizializza il gioco)

    init();                             //inizializza ncurses
    terminal_check(24, 80);       //controlla se la finestra è abbastanza grande
    set_dimensions(LINES, COLS);  //imposta le dimensioni della finestra

    ///////////////////////// inizializza i parametri della finestra di gioco
    int h= retrive_height();
    int w= retrive_width();
    s_height = h - h%2;                 //l'altezza della schermata del punteggio è pari alla metà dell'altezza del terminale
    s_width = (w - w%2)/4;              //la larghezza della schermata del punteggio è pari alla quarta parte della larghezza del terminale
    d_height = s_height;                //l'altezza del dungeon è pari all'altezza della schermata del punteggio
    d_width = s_width*3;                //la larghezza del dungeon è pari a 3 volte la larghezza della schermata del punteggio
    v_exit_lenght = d_height/8;         //la lunghezza della porta di uscita verticale è pari alla ottava parte dell'altezza del dungeon
    h_exit_lenght = v_exit_lenght*2;    //la lunghezza della porta di uscita è pari alla metà della lunghezza della porta di uscita verticale
	last_row = d_height - 1;        //l'ultima riga del dungeon è pari all'altezza del dungeon meno 1
	last_col = d_width - 1;         //l'ultima colonna del dungeon è pari alla larghezza del dungeon meno 1

    ////////////////////////// creo il primo livello
    life = 10;                          //vite iniziali del giocatore
    score = 0;                          //punteggio iniziale del giocatore
    current = new level;
    current->number = score;
    current->prev = nullptr;
    current->next = nullptr;
    create_dungeon();                   //creo il dungeon
    create_scoreboard();                //creo la finestra del punteggio
}

engine::~engine() {
    gameover();
}

void engine::gameover() { //termina il gioco
    clear();
    printw("Game Over");
    printw("\nyour score is %d", score);
    printw("\nPRESS ANY KEY TO CLOSE THE PROGRAM");
    getch();
    end();  //termina ncurses
}

void engine::life_update(double x) {  //aggiorna la vita (se x<0 decrementa, se x>0 incrementa) se diventa negativa termina il gioco
    life = life + x;
    if (life <= 0) {
        life = 0;
        gameover();
    }
    refresh_scoreboard();
}

void engine::write_char(point p, const char ch) { //scrive un carattere nel punto
    mvwaddch(current->dungeon, p.y, p.x, ch);
}

char engine::read_char(point p) { //cancella il carattere nel punto
    return mvwinch(current->dungeon, p.y, p.x);
}

void engine::clear_point(point point) { //pulisce il punto
    write_char(point, ' ');

}

engine::point engine::random_clear_point() { //ritorna un punto casuale libero
    point p;
    do { //cerca un punto libero fino a quando non ne trova uno
        p = create_point(random(1, last_row), random(1, last_col));
    } while (!is_point_clear(current->dungeon, p));
    return p;
}
void engine::create_dungeon() { //crea finestra dungeon
    current->dungeon = newwin(d_height, d_width, 0, 0); //creo la finestra del dungeon in posizione 0,0 sullo schermo
    box(current->dungeon, 0, 0);                        //creo i muri perimetrali del dungeon
    refresh();
    create_entry();                                     //creo l'entrata
    create_exit();                                      //creo l'uscita
    create_rooms();                                     //creo le stanze
    refresh_dungeon();
}

void engine::create_scoreboard() {  //crea finestra scoreboard
    scoreboard = newwin (s_height, s_width, 0, d_width);    //creo la finestra del punteggio a destra del dungeon
    box(scoreboard, 0, 0);                                  //creo il bordo della finestra
    refresh();
    refresh_scoreboard();
}

bool engine::ok_prev_level() { //controlla se esiste un livello precedente al livello corrente, se esiste ritorna true, altrimenti ritorna false
    if (current->prev != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool engine::ok_next_level() {//controlla se esiste un livello successivo al livello corrente, se esiste ritorna true, altrimenti ritorna false
	if (current->next != nullptr) {
		return true;
	} else {
		return false;
	}
}

void engine::create_entry() {   //creo un entrata speculare all'uscita del livello precedente
    current->entry = new dungeon_door;      //creo la struttura per l'entrata
    current->entry->pointList = nullptr;    //setto la lista di punti a nullptr
    if (ok_prev_level()) {  //se esiste un livello precedente
        switch (current->prev->exit->NSWE) {    //controllo la direzione dell'uscita del livello precedente
            case 0: //uscita verso il nord del livello precedente (entrata verso il sud del livello corrente)
                current->entry->NSWE = 1;
                for (int i = 0; i < h_exit_lenght; i++) {
                    add_point_to_list(&current->entry->pointList, create_point(last_row, (get_point_list_node(&current->prev->exit->pointList, i))->p.x));
                }
                break;
            case 1: //uscita verso il sud del livello precedente (entrata verso il nord del livello corrente)
                current->entry->NSWE = 0;
                for (int i = 0; i < h_exit_lenght; i++) {
                    add_point_to_list(&current->entry->pointList, create_point(0, (get_point_list_node(&current->prev->exit->pointList, i))->p.x));
                }
                break;
            case 2: //uscita verso l'est del livello precedente (entrata verso l'ovest del livello corrente)
                current->entry->NSWE = 3;
                for (int i = 0; i < v_exit_lenght; i++) {
                    add_point_to_list(&current->entry->pointList, create_point((get_point_list_node(&current->prev->exit->pointList, i))->p.y, last_col));
                }
                break;
            case 3: //uscita verso l'ovest del livello precedente (entrata verso l'est del livello corrente)
                current->entry->NSWE = 2;
                for (int i = 0; i < v_exit_lenght; i++) {
                    add_point_to_list(&current->entry->pointList, create_point((get_point_list_node(&current->prev->exit->pointList, i))->p.y, 0));
                }
                break;
        }
        point_list *temp = current->entry->pointList;
        while (temp != nullptr) {  //scrivo l'entrata sul dungeon corrente
            write_char(temp->p, ' ');
            temp = temp->next;
        }
    }
}

void engine::create_exit() { //creo un uscita casuale nel livello corrente
    (current->exit) = new dungeon_door;                         //creo la porta di uscita
    (current->exit)->NSWE = random(0,3);              //genero un numero casuale tra 0 e 3 per scegliere la direzione dell'uscita (0 = nord, 1 = sud, 2 = ovest, 3 = est)
    if (score != 0) {                                           //la porta di uscita non deve essere nella stessa direzione dell'entrata
        while (current->exit->NSWE == current->entry->NSWE) {   //se il numero casuale e` uguale alla direzione dell'entrata del livello corrente allora vado in un'altra direzione
            current->exit->NSWE = random(0, 3);
        }
    }
    switch (current->exit->NSWE) {                              //genero le coordinate casuali
        case 0: //nord
            for (int i = 0; i < h_exit_lenght; i++) { 		 //creo la lista di punti della porta di uscita
                if (i == 0) { 								 //se e` il primo punto della lista
                    add_point_to_list(&current->exit->pointList, create_point(0, random(1, last_col - h_exit_lenght - 1))); //creo il primo punto della lista con coordinate casuali
                } else {
                    add_point_to_list(&current->exit->pointList, create_point(0, get_point_list_node(&current->exit->pointList, i - 1)->p.x + 1));
                }
            }
            break;
        case 1: //sud
            for (int i = 0; i < h_exit_lenght; i++) {
                if (i == 0) {
                    add_point_to_list(&current->exit->pointList, create_point(last_row, random(1, last_col - h_exit_lenght - 1)));
                } else {
                    add_point_to_list(&current->exit->pointList, create_point(last_row, get_point_list_node(&current->exit->pointList, i - 1)->p.x + 1));
                }
            }
            break;
        case 2: //ovest
            for (int i = 0; i < v_exit_lenght; i++) {
                if (i == 0) {
                    add_point_to_list(&current->exit->pointList, create_point(random(1, last_row - v_exit_lenght - 1), 0));
                } else {
                    add_point_to_list(&current->exit->pointList, create_point(get_point_list_node(&current->exit->pointList, i - 1)->p.y + 1, 0));
                }
            }
            break;
        case 3: //east
            for (int i = 0; i < v_exit_lenght; i++) {
                if (i == 0) {
					add_point_to_list(&current->exit->pointList, create_point(random(1, last_row - v_exit_lenght - 1), last_col));
				} else {
					add_point_to_list(&current->exit->pointList, create_point(get_point_list_node(&current->exit->pointList, i - 1)->p.y + 1, last_col));
				}
            }
            break;
    }
    point_list *temp = current->exit->pointList;
    while (temp != nullptr) {
        write_char(temp->p, 'x');
        temp = temp->next;
    }
}

void engine::create_rooms() { //creo le stanze nel livello corrente
    int rand_y = random((d_height/2)-v_exit_lenght-1, (d_height/2)+v_exit_lenght+1);                                       //genero le coordinate casuali cercando di rimanere nei dintorni del centro del dungeon per evitare stanze troppo piccole
    int rand_x = random((d_width/2)-h_exit_lenght-1, (d_width/2)+h_exit_lenght+1);;                                        //
    while (is_y_in_list(&current->entry->pointList, rand_y) || is_y_in_list(&current->exit->pointList, rand_y)) {   //se la coordinata y è uguale a una delle coordinate y dell'entrata o dell'uscita genera un nuovo numero
        if (rand_y > (d_height/2)+v_exit_lenght-1) rand_y = (d_height/2)-v_exit_lenght-1;
        else rand_y++;
    }
    while (is_x_in_list(&current->entry->pointList, rand_x) || is_x_in_list(&current->exit->pointList, rand_x) ) {  //se la coordinata x è uguale a una delle coordinate x dell'entrata o dell'uscita genera un nuovo numero
        if (rand_x > (d_width/2)+h_exit_lenght-1) rand_x = (d_width/2)-h_exit_lenght-1;
        else rand_x++;
    }
    mvwvline (current->dungeon, 0, rand_x, ACS_VLINE, d_height); //disegno una linea verticale lunga 24 caratteri
    mvwhline (current->dungeon, rand_y, 0, ACS_HLINE, d_width); //disegno una linea orizzontale lunga 64 caratteri
    mvwaddch (current->dungeon, rand_y, rand_x, ACS_PLUS); //disegno un punto in cui le due linee si incontranono
    int p = 0;
    int a = random (2, 4);
    bool b = random (0, 1);
    int c = 4 - a;
    int rand_NSWE = random(0,3); //incremento il numero casuale di 1 e lo faccio tornare tra 0 e 3
    for (int i=0; i<4; i++) {
        rand_NSWE = (rand_NSWE + 1) % 4;
        switch (rand_NSWE) {
            case 0: //N
                mvwaddch (current->dungeon, 0, rand_x, ACS_HLINE); //disegno un punto in cui le due linee si incontrano
                if (a > 0) {
                    if (b == true){
                        p = random(1, rand_y-v_exit_lenght-1);
                        for (int j=0; j<v_exit_lenght; j++) write_char(create_point(get_relative_y(p+j, 1), rand_x), ' ');
                    }
                    mvwaddch (current->dungeon, 0, rand_x, ACS_TTEE); //disegno un punto in cui le due linee si incontrano
                    a--;
                    b = true;
                    break;
                }
                if (c > 0) {
                    p = rand_y - 1;
                    while (p > 0) {
                        mvwaddch (current->dungeon, p, rand_x, ' ');
                        p--;
                    }
                    c--;
                    break;
                }
                break;
            case 1: //S
                mvwaddch (current->dungeon, d_height-1, rand_x, ACS_HLINE); //disegno un punto in cui le due linee si incontrano
                if (a > 0) {
                    if (b == true){
                        p = random(rand_y+v_exit_lenght+1, d_height-2);
                        for (int j=0; j<v_exit_lenght; j++) write_char(create_point(get_relative_y(p-j, 1), rand_x), ' ');;
                    }
                    mvwaddch (current->dungeon, d_height-1, rand_x, ACS_BTEE); //disegno un punto in cui le due linee si incontrano
                    a--;
                    b = true;
                    break;
                }
                if (c > 0) {
                    p = rand_y + 1;
                    while (p < d_height - 1) {
                        mvwaddch (current->dungeon, p, rand_x, ' ');
                        p++;
                    }
                    c--;
                    break;
                }
                break;
            case 2: //W
                mvwaddch (current->dungeon, rand_y, 0, ACS_VLINE); //disegno un punto in cui le due linee si incontrano
                if (a > 0) {
                    if (b == true){
                        p = random(1, rand_x-h_exit_lenght-1);
                        for (int j=0; j<h_exit_lenght; j++) write_char(create_point(rand_y, get_relative_x(p+j, 1)), ' ');
                    }
                    mvwaddch (current->dungeon, rand_y, 0, ACS_LTEE); //disegno un punto in cui le due linee si incontrano
                    a--;
                    b = true;
                    break;
                }
                if (c > 0) {
                    p = rand_x - 1;
                    while (p > 0) {
                        mvwaddch (current->dungeon, rand_y, p, ' ');
                        p--;
                    }
                    c--;
                    break;
                }
                break;
            case 3: //E
                mvwaddch (current->dungeon, rand_y, d_width-1, ACS_VLINE); //disegno un punto in cui le due linee si incontrano
                if (a > 0) {
                    if (b == true){
                        p = random(rand_x+h_exit_lenght+1, d_width-2);
                        for (int j=0; j<h_exit_lenght; j++) write_char(create_point(rand_y, get_relative_x(p-j, 1)), ' ');
                    }
                    mvwaddch (current->dungeon, rand_y, d_width-1, ACS_RTEE); //disegno un punto in cui le due linee si incontrano
                    a--;
                    b = true;
                    break;
                }
                if (c > 0) {
                    p = rand_x + 1;
                    while (p < d_width - 1) {
                        mvwaddch (current->dungeon, rand_y, p, ' ');
                        p++;
                    }
                    c--;
                    break;
                }
                break;
        }
    }
}

void engine::add_level() { //aggiunge un livello dopo il livello corrente, lo setta come livello corrente e crea un nuovo dungeon
    score++; //aumento il punteggio di 1
    current->next = new level; //creo il nuovo livello
    current->next->prev = current; //setto il puntatore al livello precedente del nuovo livello al livello corrente
    current = current->next; //setto il nuovo livello come livello corrente
    current->number = current->prev->number + 1; //setto il numero del livello corrente al numero del livello precedente + 1
    current->next = nullptr; //setto il puntatore al livello successivo a nullptr
    create_dungeon(); //creo il nuovo dungeon
    refresh_scoreboard(); //aggiorno la finestra del punteggio
}

void engine::prev_level() { //setta il livello precedente come livello corrente e aggiorna il puntatore al dungeon corrente
    if (ok_prev_level()) {
        current = current->prev; //setto il livello precedente come livello corrente
        refresh_scoreboard(); //aggiorno la finestra del punteggio
        refresh_dungeon(); //aggiorno la finestra del dungeon
    }
}

void engine::next_level() { //setta il livello successivo come livello corrente e aggiorna il puntatore al dungeon corrente
    if (ok_next_level()) {
        current = current->next; //setto il livello successivo come livello corrente
    }
    else { //se non esiste un livello successivo aggiunge un livello e lo setta come livello corrente e aggiorna il puntatore al dungeon corrente
        add_level();
    }
    refresh_dungeon(); //aggiorno la finestra del dungeon
    refresh_scoreboard(); //aggiorno la finestra del punteggio
}

WINDOW *engine::retrive_scoreboard() { //restituisce il puntatore alla finestra del punteggio
    return scoreboard;
}

WINDOW *engine::retrive_dungeon() { //restituisce il puntatore alla finestra del dungeon
    return current->dungeon;
}

void engine::refresh_scoreboard() { //stampa il livello corrente
    wclear(scoreboard);
    box(scoreboard, 0, 0);
	int lines=s_height-1;
    int i = 1;
    mvwprintw(scoreboard, i, 1, "score: %d", score); i++; //stampa il punteggio
    mvwprintw(scoreboard, i, 1, "level: %d", current->number); i++; //stampa il numero del livello corrente
    mvwprintw(scoreboard, i, 1, "life: %f", life); i++; //stampa il numero del livello corrente
    if (debug){
        if (i<lines) { mvwprintw(scoreboard, i, 1, "prev:"); i++; } //stampa il puntatore al livello precedente
        if (i<lines) { if (ok_prev_level()) mvwprintw(scoreboard, i, 1, "%p", current->prev->dungeon); else mvwprintw(scoreboard, i, 1, "NULL"); i++; }
        if (i<lines) { mvwprintw(scoreboard, i, 1, "current:"); i++; } //stampa il puntatore al livello corrente
        if (i<lines) { mvwprintw(scoreboard, i, 1, "%p", current->dungeon); i++; } //stampa l'indirizzo del dungeon del livello corrente
        if (i<lines) { mvwprintw(scoreboard, i, 1, "next:"); i++; } //stampa il puntatore al livello successivo
        if (i<lines) { if (ok_next_level()) mvwprintw(scoreboard, i, 1, "%p", current->next->dungeon); else mvwprintw(scoreboard, i, 1, "NULL"); i++; }
        if (i<lines && score != 0) { mvwprintw(scoreboard, i, 1, "entry NSWE: %d", current->entry->NSWE); i++; } //stampa il valore NSWE dell'entrata
        point_list *tmp = current->entry->pointList; //creo un puntatore temporaneo al primo elemento della lista delle uscite
        while (tmp != nullptr) { //finchè il puntatore temporaneo non punta a nullptr
            if (i<lines) { mvwprintw(scoreboard, i, 1, "entry %d %d", tmp->p.y, tmp->p.x); i++; } //stampa il valore NSWE dell'uscita
            tmp = tmp->next; //passa all'elemento successivo
        }
        if (i<lines) { mvwprintw(scoreboard, i, 1, "exit NSWE: %d", current->exit->NSWE); i++; } //stampa il valore NSWE dell'uscita
        tmp = current->exit->pointList; //creo un puntatore temporaneo al primo elemento della lista delle uscite
        while (tmp != nullptr) { //finchè il puntatore temporaneo non punta a nullptr
            if (i<lines) { mvwprintw(scoreboard, i, 1, "exit %d %d", tmp->p.y, tmp->p.x); i++; } //stampa il valore NSWE dell'uscita
            tmp = tmp->next; //passa all'elemento successivo
        }
    }
    touchwin(scoreboard); //aggiorno la finestra del punteggio
    wrefresh(scoreboard); //aggiorno la finestra del punteggio
}

void engine::refresh_dungeon() { //stampa il dungeon corrente
    touchwin(current->dungeon); //aggiorno il dungeon
    wrefresh(current->dungeon); //aggiorno la finestra del dungeon
}

/*
┌────────────────────────────      ────────────────────────┐┌──────────────────┐
│                                                          ││score: 364        │
│                                                          ││level: 363        │
│                                                          ││life: 10.000000   │
│                                                          ││prev:             │
│                                                          ││0x564e0b020810    │
│                                                          ││current:          │
│                                                          ││0x564e0b0223b0    │
│                                                          ││next:             │
├──────────      ──────────────────┼──────────────      ───┤│0x564e0b023f50    │
│                                  │                       ││entry NSWE: 0     │
│                                  │                       ││entry 0 29        │
│                                  │                       ││entry 0 30        │
│                                  │                       ││entry 0 31        │
│                                  │                       ││entry 0 32        │
│                                  │                       ││entry 0 33        │
│                                  │                       ││entry 0 34        │
│                                  │                       ││exit NSWE: 3      │
│                                  │                       ││exit 19 60        │
│                                  │                       ││exit 20 60        │
│                                  │                       ││exit 21 60        │
│                                  │                       ││                  │
│                                  │                       ││                  │
└──────────────────────────────────┴───────────────────────┘└──────────────────
 
 */