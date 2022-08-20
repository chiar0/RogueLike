#include <ncurses.h>
int main()
{
    initscr(); /* Start curses mode */
    printw("Hello World !!!"); /* Print Hello World */
    refresh(); /* Print it on to the real screen */
    getch(); /* Wait for user input */
    endwin(); /* End curses mode */
    return 0;
}

/*
#include <iostream>
#include <string.h>

// !! C++ 23 !!
int main()
{
    class fortnite_user
    {
    protected:
        int health;
        int dmg;
        char icon[3];
    public:
        fortnite_user (int health = 5, int dmg = -1)
        {
            this->health = health;
            this->dmg = dmg;
            icon[0] = 'P';
            icon[1] = '\0';
        }
        void setter (int health, int dmg)   //per assegnare un nuovo valore a un solo paramentro assegnare "0" all'altro
        {
            if (health != 0)
                this->health=health;
            if (dmg != 0)
                this->dmg=dmg;
        }
        void health_changer(int dmg = -1)   //in base al segno di dmg incrementa o decrementa
        {
            this->health += dmg;
        }
        void dmg_changer(int dmg = -1)  //in base al segno di dmg incrementa o decrementa
        {
            this->health += dmg;
        }
    };
    class fortnite_enemy : public fortnite_user
    {
    public:
        fortnite_enemy (int health = 5, int dmg = -1) : fortnite_user (health, dmg)
        {
            this->health = health;
            this->dmg = dmg;
            icon[0] = '@';
            icon[1] = '@';
            icon[2] = '\0';
        }
    };
}
*/