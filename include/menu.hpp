//
// Created by lxchiar on 01/12/22.
//

#ifndef GAME_CPP_MENU_HPP
#define GAME_CPP_MENU_HPP

#include "display.hpp"

class menu : public display{
    protected:
        WINDOW *menu_win;
    public:
        menu();
        ~menu();
};

#endif //GAME_CPP_MENU_HPP
