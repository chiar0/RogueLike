#pragma once
#include <iostream>
#include "display.hpp"
#include <string>

const char   r00[] = {"                      lllllll UUUUUUU     UUUUUUU "};
const char   r01[] = {"                      l:::::l U:::::U     U:::::U "};
const char   r02[] = {"                      l:::::l UU::::U     U:::::U "};
const char   r03[] = {" rrrrr   rrrrrrrrr    l::::l  U:::::U     U:::::U "};
const char   r04[] = {" r::::rrr:::::::::r   l::::l  U:::::D     D:::::U "};
const char   r05[] = {" r:::::::::::::::::r  l::::l  U:::::D     D:::::U "};
const char   r06[] = {" rr::::::rrrrr::::::r l::::l  U:::::D     D:::::U "};
const char   r07[] = {"  r:::::r     r:::::r l::::l  U:::::D     D:::::U "};
const char   r08[] = {"  r:::::r     rrrrrrr l::::l  U:::::D     D:::::U "};
const char   r09[] = {"  r:::::r             l::::l  U:::::D     D:::::U "};
const char   r10[] = {"  r:::::r             l::::l  U::::::U   U::::::U "};
const char   r11[] = {"  r:::::r            l::::::l U:::::::UUU:::::::U "};
const char   r12[] = {"  r:::::r            l::::::l UU:::::::::::::UU   "};
const char   r13[] = {"  r:::::r            l::::::l   UU:::::::::UU     "};
const char   r14[] = {"  rrrrrrr            llllllll     UUUUUUUUU       "};
const char   r15[] = {"                                                  "};
const char   r16[] = {"              ROGUELIKE UNIBO                     "};
const char   r17[] = {"            PREMI X PER INIZIARE                  "};

class menu : public display{
    protected:
        WINDOW *menu_win;
    public:
        menu();
        void display();
};


