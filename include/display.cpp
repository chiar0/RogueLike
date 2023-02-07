#include "display.hpp"

void display::init(){ //inizializza ncurses
    initscr();                                  //inizializza ncurses
    cbreak();                                   //disabilita il buffering della tastiera
    noecho();                                   //disabilita l'echo dei caratteri
    keypad(stdscr, TRUE);                       //abilita la lettura dei tasti freccia
    curs_set(0);                                //nasconde il cursore
    srand(time(nullptr));            //inizializza il generatore di numeri casuali
    //start_color();
    //init_pair(1, COLOR_WHITE, COLOR_BLACK);
    //init_pair(2, COLOR_RED, COLOR_BLACK);
}

void display::end(){ //termina ncurses
    clear();
    endwin();
    exit(0);
}

void display::set_dimensions(int h, int w){ //imposta le dimensioni della finestra
    if (h > LINES) height = LINES;
    else if (h < 0) height = 0;
    else height = h;
    if (w > COLS) width = COLS;
    else if (w < 0) width = 0;
    else width = w;
}

void display::terminal_check(int h, int w) { //controlla se la finestra è abbastanza grande e se ha le caratteristiche richieste
    if (LINES < h || COLS < w) { //se la finestra non è abbastanza grande
        printw("terminal size (HEIGHT x WIDTH) must be >= %dx%d", h, w);
        printw("\nyou actually have %dx%d", LINES, COLS);           //LINES E COLS sono due variabili che inizializza initscr() che contegono le rispettive proprieta` del terminale
        printw("\nPRESS ANY KEY TO CLOSE THE PROGRAM");             //prima del resize e` meglio chiudere il programma o si baca il terminale xD
        getch();
        end();
        exit (0);
    }
    if (has_colors() == FALSE) { //se il terminale non supporta i colori
        printf("Your terminal does not support color");
        printw("\nPRESS ANY KEY TO CLOSE THE PROGRAM");
        end();
        exit(0);
    }
}

int display::retrive_height() { //ritorna l'altezza del terminale
    return height;
}

int display::retrive_width() { //ritorna la larghezza del terminale
    return width;
}

display::point display::create_point(int y, int x) { //crea un nuovo punto
    point new_point{y,x};
    return new_point;
}

void display::add_point_to_list(point_list **head, point p) { //aggiunge un punto alla lista
    if (*head == nullptr) { //se la lista è vuota crea il primo nodo
        *head = new point_list;
        (*head)->p = p;
        (*head)->next = nullptr;
    } else {                //altrimenti aggiunge un nodo alla fine
        point_list *temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new point_list;
        temp->next->p = p;
        temp->next->next = nullptr;
    }
}

display::point_list *display::get_point_list_node(point_list **head, int i) { //ritorna il nodo i-esimo della lista
    if (*head == nullptr) { //se la lista è vuota ritorna nullptr
        return nullptr;
    } else {                //altrimenti ritorna il nodo i-esimo
        point_list *temp = *head;
        for (int j = 0; j < i && temp->next != nullptr; j++) {
            temp = temp->next;
        }
        return temp;
    }
}

bool display::is_y_in_list(point_list **head, int y) { //controlla se y è presente nella lista
    if (*head == nullptr) {
        return false;
    }
    point_list *tmp = *head;
    while (tmp != nullptr) {
        if (tmp->p.y == y) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool display::is_x_in_list(point_list **head, int x) { //controlla se x è presente nella lista
    if (*head == nullptr) {
        return false;
    }
    point_list *tmp = *head;
    while (tmp != nullptr) {
        if (tmp->p.x == x) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool display::is_point_in_list(point_list **head, point p) { //controlla se il punto è presente nella lista
    return is_x_in_list(head, p.x) && is_y_in_list(head, p.y);
}


int display::random(int min, int max) { //ritorna un numero casuale tra min e max
    return rand() % (max - min + 1) + min;
}

int display::get_relative_y (int y, int NSWE) { //ritorna la coordinata y relativa alla direzione NSWE
    switch (NSWE) {
        case 0: //N
            return y - 1;
        case 1: //S
            return y + 1;
        case 2: //W
            return y;
        case 3: //E
            return y;
    }
}

int display::get_relative_x (int x, int NSWE) { //ritorna la coordinata x relativa alla direzione NSWE
    switch (NSWE) {
        case 0: //N
            return x;
        case 1: //S
            return x;
        case 2: //W
            return x - 1;
        case 3: //E
            return x + 1;
    }
}

display::point display::get_relative_point (point p, int NSWE) { //ritorna il punto relativo alla direzione NSWE
    return create_point(get_relative_x(p.x, NSWE), get_relative_y(p.y, NSWE));
}

bool display::is_point_in_window(point p) { //controlla se il punto è nella finestra
    return p.y >= 0 && p.y < height && p.x >= 0 && p.x < width;
}

bool display::is_point_clear(WINDOW *win, point p) { //controlla se il punto è vuoto
    return mvwinch(win, p.y, p.x) == ' ';
}


