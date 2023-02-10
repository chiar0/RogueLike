#include "engine.hpp"

engine::engine():display() { //costruttore della classe engine (inizializza il gioco)

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
    life = 100.0;                          //vite iniziali del giocatore
    score = 0;                          //punteggio iniziale del giocatore
    count = 0;                         //numero di nemici uccisi
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
    printw("Game Over!");
    printw("\n Max level reached: %d", score);
    printw("\n Enemy killed: %d", count);
    printw("\nPRESS x TO CLOSE THE PROGRAM");
    int ch = 0;
    while (ch != 'x') { ch = getch(); }
    end();  //termina ncurses
}

void engine::life_update(double x) {  //aggiorna la vita (se x<0 decrementa, se x>0 incrementa) se diventa negativa termina il gioco
    life = life + x;
    if (life <= 0.0) {
        life = 0.0;
        gameover();
    }
    refresh_scoreboard();
}

void engine::count_update(int x) { //aggiorna il punteggio (se x<0 decrementa, se x>0 incrementa)
    count = count + x;
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
    switch (current->exit->NSWE) {                              //creo la lista di punti della porta di uscita in base alla direzione scelta
        case 0: //nord
            for (int i = 0; i < h_exit_lenght; i++) {
                if (i == 0) {
                    add_point_to_list(&current->exit->pointList, create_point(0, random(1, last_col - h_exit_lenght - 1)));
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
    while (temp != nullptr) { //scrivo l'uscita sul dungeon corrente
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
    mvwvline (current->dungeon, 0, rand_x, ACS_VLINE, d_height);                                                                     //disegno una linea verticale lunga 24 caratteri
    mvwhline (current->dungeon, rand_y, 0, ACS_HLINE, d_width);                                                                      //disegno una linea orizzontale lunga 64 caratteri
    mvwaddch (current->dungeon, rand_y, rand_x, ACS_PLUS);                                                                           //disegno un punto in cui le due linee si incontranono
    int p = 0;
    int a = random (2, 4);                                                                                                  //genero un numero casuale tra 2 e 4 per scegliere il numero di muri da disegnare
    bool b = random (0, 1);                                                                                                 //genero un numero casuale tra 0 e 1 per scegliere se lasciare un muro senza uscita
    int c = 4 - a;                                                                                                                   //calcolo il numero di muri da eliminare
    int rand_NSWE = random(0,3);
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

void engine::clear_exit() { //sostituisce le x dell'uscita con spazi
    display::point_list *p = current->exit->pointList;
    while (p != nullptr) {
        write_char(p->p, ' ');
        p = p->next;
    }
}

WINDOW *engine::retrive_scoreboard() { //restituisce il puntatore alla finestra del punteggio
    return scoreboard;
}

WINDOW *engine::retrive_dungeon() { //restituisce il puntatore alla finestra del dungeon
    return current->dungeon;
}

display::point_list *engine::retrive_entry() { //restituisce il puntatore alla lista dei punti
    return current->entry->pointList;
}

display::point_list *engine::retrive_exit() { //restituisce il puntatore alla lista dei punti
    return current->exit->pointList;
}

int engine::retrive_entry_NSWE() { //restituisce il numero che indica la direzione dell'ingresso
    return current->entry->NSWE;
}

int engine::retrive_exit_NSWE() { //restituisce il numero che indica la direzione dell'uscita
    return current->exit->NSWE;
}

int engine::retrive_level_number() { //restituisce il numero del livello corrente
    return current->number;
}

int engine::retrive_columns() { //restituisce il numero di colonne del dungeon
    return d_width-1;
}

int engine::retrive_rows() { //restituisce il numero di righe del dungeon
    return d_height-1;
}

void engine::refresh_scoreboard() { //stampa il livello corrente
    
    wclear(scoreboard);
    box(scoreboard, 0, 0);
	int lines=s_height-1;
    int i = 1;
    
    mvwprintw(scoreboard, i, 1, "life: "); i+=2; //stampa la vita
    int x = (int)ceil(life)/10;
    if (x > (s_width-8) || x == 1) { wprintw(scoreboard, "%d", (int)ceil(life)); }
    else { 
        for (int j = 0; j < x; j++) { 
            waddch(scoreboard, ACS_DIAMOND);
        } 
    }

    mvwprintw(scoreboard, i, 1, "kills: %d", count); i+=2; //stampa il punteggio
    mvwprintw(scoreboard, i, 1, "level: %d", current->number); i+=2; //stampa il numero del livello corrente
    if (score != 0){
        if (current->entry->NSWE == 0) mvwprintw(scoreboard, i, 1, "entry: NORD");
        if (current->entry->NSWE == 1) mvwprintw(scoreboard, i, 1, "entry: SUD");
        if (current->entry->NSWE == 2) mvwprintw(scoreboard, i, 1, "entry: OVEST");
        if (current->entry->NSWE == 3) mvwprintw(scoreboard, i, 1, "entry: EST");
        i++;
    }
    if (current->exit->NSWE == 0) mvwprintw(scoreboard, i, 1, "exit: NORD");
    if (current->exit->NSWE == 1) mvwprintw(scoreboard, i, 1, "exit: SUD");
    if (current->exit->NSWE == 2) mvwprintw(scoreboard, i, 1, "exit: OVEST");
    if (current->exit->NSWE == 3) mvwprintw(scoreboard, i, 1, "exit: EST");
    i++;

    touchwin(scoreboard); 
    wrefresh(scoreboard); 
}

void engine::refresh_dungeon() { //stampa il dungeon corrente
    touchwin(current->dungeon); 
    wrefresh(current->dungeon); 
}