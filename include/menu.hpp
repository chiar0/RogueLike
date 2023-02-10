#pragma once
#include <iostream>
#include "display.hpp"
#include <string>
#include "Timer.hpp"

class menu : public display{
    protected:
        Timer *t = t->Instance(); 
        float fps = 100.0f; 
        WINDOW *menu_win;
        WINDOW *start_win;
    public:
        menu();
        void loop();
};


