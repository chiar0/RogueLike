#ifndef GAME_CPP_ENGINE_HPP
#define GAME_CPP_ENGINE_HPP

#include "display.hpp"
#include "math.h"


class engine: public display{
protected:
    int d_height, d_width;              //altezza e larghezza del dungeon
    int v_exit_lenght, h_exit_lenght;   //lunghezza dell'uscita verticale e orizzontale del dungeon
    int s_height, s_width;              //altezza e larghezza della schermata del punteggio
	int last_row, last_col;         //coordinate dell'ultima cella del dungeon

    struct dungeon_door {   //struttura per le porte del dungeon
        point_list *pointList;  //puntatore alla lista di coordinate
        int NSWE;               //direzione del muro in cui si inserisce la porta (0=Nord, 1=Sud, 2=Ovest, 3=Est)
    };

    struct level {  //struttura per il livello
        int number;             //numero del livello
        WINDOW *dungeon;        //puntatore alla finestra del dungeon
        dungeon_door *entry;    //puntatori alla struttura contenente le coordinate dell' entrata e dell'uscita
        dungeon_door *exit;
        level *prev;            //puntatori al livello precedente e successivo
        level *next;
    };

    level *current;     //puntatore al livello corrente
    int score;          //punteggio
    double life;        //vita
    int count;          //contatore
    WINDOW *scoreboard; //puntatore alla finestra del punteggio

    void create_dungeon();      //crea il dungeon
    void create_scoreboard();   //crea la finestra del punteggio
    void create_entry();        //crea l'entrata
    void create_exit();         //crea l'uscita
    void create_rooms();        //crea le stanze
    void add_level();           //aggiunge un livello dopo il livello corrente, lo setta come livello corrente e crea un nuovo dungeon
public: //===================// =======
    engine();                               //costruttore della classe engine (inizializza il gioco)
    ~engine();
    void gameover();                        //termina il gioco
    void life_update(double x);             //aggiorna la vita (se x<0 decrementa, se x>0 incrementa) se diventa negativa termina il gioco
    void count_update(int x);               //aggiorna il punteggio (se x<0 decrementa, se x>0 incrementa)
    void write_char(point point, char ch);  //scrive un carattere nel punto
    char read_char(point point);            //ritorna il carattere nel punto
    void clear_point(point point);          //cancella il carattere nel punto
    point random_clear_point();             //ritorna un punto casuale libero
    bool ok_prev_level();                   //controlla se esiste un livello precedente al livello corrente, se esiste ritorna true, altrimenti ritorna false
    bool ok_next_level();                   //controlla se esiste un livello successivo al livello corrente, se esiste ritorna true, altrimenti ritorna false
    void prev_level();                      //setta il livello precedente, se esiste, come livello corrente
    void next_level();                      //setta il livello successivo, se non esiste lo crea, come livello corrente
    void clear_exit();                      //cancella i muri d'uscita
    WINDOW *retrive_scoreboard();           //ritorna il puntatore alla finestra del punteggio
    WINDOW *retrive_dungeon();              //ritorna il puntatore alla finestra del dungeon
    point_list *retrive_entry();            //ritorna il puntatore alla lista di coordinate dell'entrata
    point_list *retrive_exit();             //ritorna il puntatore alla lista di coordinate dell'uscita
    int retrive_entry_NSWE();               //ritorna la direzione del muro in cui si trova l'entrata
    int retrive_exit_NSWE();                //ritorna la direzione del muro in cui si trova l'uscita
    int retrive_level_number();             //ritorna il punteggio
    int retrive_columns();                  //restituisce il numero di colonne del dungeon
    int retrive_rows();                     //restituisce il numero di righe del dungeon
    void refresh_scoreboard();              //aggiorna la finestra del punteggio
    void refresh_dungeon();                 //aggiorna la finestra del dungeon
};

#endif //GAME_CPP_ENGINE_HPP
