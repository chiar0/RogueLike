//
// Created by lxchiar on 01/12/22.
//

#include "menu.hpp"

menu::menu():display() {
    //menu_win = newwin(
    box(menu_win, 0, 0);
    wrefresh(menu_win);
}