#pragma once
#include <iostream>
#include "display.hpp"
#include <string>

class menu : public display{
    protected:
        WINDOW *menu_win;
    public:
        menu();
};


