#include "ncurses.h"
#include "ctime"
#include "cstdlib"

class display{
protected:
    int height;           //altezza e larghezza della finestra
    int width;
public:
    struct point {        //struttura per le coordinate
        int y;
        int x;
    };

    struct point_list {   //struttura per la lista di coordinate
        point p;
        point_list *next;
    };

    display();                                                            //costruttore
    ~display();
    void init();                                                          //inizializza ncurses
    void end();                                                           //termina ncurses
    void set_dimensions(int h, int w);                                    //imposta le dimensioni della finestra
    void terminal_check(int h, int w);                                    //controlla se la finestra è abbastanza grande
    int retrive_height();                                                 //ritorna l'altezza della finestra
    int retrive_width();                                                  //ritorna la larghezza della finestra
    point create_point(int y, int x);                                     //crea un nuovo punto
    void add_point_to_list(point_list **head, point p);                   //aggiunge un punto alla lista
    point_list *get_point_list_node(point_list **head, int i);            //ritorna il puntatore al nodo i-esimo della lista
    bool is_y_in_list(point_list **head, int y);                          //controlla se y è presente nella lista
    bool is_x_in_list(point_list **head, int x);                          //controlla se x è presente nella lista
    bool is_point_in_list(point_list **head, point p);                    //controlla se il punto è presente nella lista
    int random(int min, int max);                                         //ritorna un numero intero casuale tra min e max
    int get_relative_y (int y, int NSWE);                                 //ritorna la coordinata y relativa alla direzione NSWE
    int get_relative_x (int x, int NSWE);                                 //ritorna la coordinata x relativa alla direzione NSWE
    point get_relative_point (point p, int NSWE);                         //ritorna il punto relativo alla direzione NSWE
    bool is_point_in_window(point p);                                     //controlla se il punto è nella finestra
    bool is_point_clear(WINDOW *win, point p);                            //controlla se il punto è libero
};