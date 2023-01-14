#include "ncurses.h"
#include "ctime"
#include "cstdlib"

class display{
protected:
    int height;
    int width;
public:
    struct point { //struttura per le coordinate
        int y;
        int x;
    };

    struct point_list {  //struttura per la lista di coordinate
        point p;
        point_list *next;
    };

    void init();
    void end();
    void set_dimensions(int h, int w);
    void terminal_check(int h, int w);
    int retrive_height();
    int retrive_width();
    point create_point(int y, int x); //crea un nuovo punto
    void add_point_to_list(point_list **head, point p); //aggiunge un punto alla lista
    point_list *get_point_list_node(point_list **head, int i); //ritorna il puntatore al nodo i-esimo della lista
    bool is_y_in_list(point_list **head, int y); //controlla se y è presente nella lista
    bool is_x_in_list(point_list **head, int x); //controlla se x è presente nella lista
    bool is_point_in_list(point_list **head, point p); //controlla se p è presente nella lista
    int random(int min, int max); //ritorna un numero casuale tra min e max
    int get_relative_y (int y, int NSWE); //ritorna la coordinata y relativa alla direzione NSWE
    int get_relative_x (int x, int NSWE); //ritorna la coordinata x relativa alla direzione NSWE
    point get_relative_point (point *p, int NSWE); //ritorna il punto relativo alla direzione NSWE
    bool is_point_in_window(point p); //controlla se il punto è nella finestra
    bool is_point_clear(WINDOW *win, point p); //controlla se il punto è libero
};