#ifndef GAME_CPP_MENU_HPP
#define GAME_CPP_MENU_HPP

#include <iostream>
#include "display.hpp"
#include <string>

class menu : public display{
    protected:
        WINDOW *menu_win;
    public:
        menu();
};

#endif //GAME_CPP_MENU_HPP
