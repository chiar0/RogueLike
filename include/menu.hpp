//
// Created by lxchiar on 01/12/22.
//

#ifndef GAME_CPP_MENU_HPP
#define GAME_CPP_MENU_HPP

#include "display.hpp"

class menu : public display{
    protected:
        WINDOW *menu_win;
        char title[14];
    public:
        menu();
        ~menu();
        bool loop();
};

#endif //GAME_CPP_MENU_HPP
