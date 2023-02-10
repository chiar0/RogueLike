#include "menu.hpp"

menu::menu() {                                                                                                                                                                                                                                              
    set_dimensions(21, 58);
    menu_win = newwin(height, width, 0, 0);
    refresh();

    //touchwin(menu_win);
    mvwprintw(menu_win, 1, 1, r00);
    mvwprintw(menu_win, 2, 1, r01);
    mvwprintw(menu_win, 3, 1, r02);
    mvwprintw(menu_win, 4, 1, r03);
    mvwprintw(menu_win, 5, 1, r04);
    mvwprintw(menu_win, 6, 1, r05);
    mvwprintw(menu_win, 7, 1, r06);
    mvwprintw(menu_win, 8, 1, r07);
    mvwprintw(menu_win, 9, 1, r08);
    mvwprintw(menu_win, 10, 1, r09);
    mvwprintw(menu_win, 11, 1, r10);
    mvwprintw(menu_win, 12, 1, r11);
    mvwprintw(menu_win, 13, 1, r12);
    mvwprintw(menu_win, 14, 1, r13);
    mvwprintw(menu_win, 15, 1, r14);
    mvwprintw(menu_win, 16, 1, r15);
    mvwprintw(menu_win, 17, 1, r16);
    mvwprintw(menu_win, 18, 1, r17);
    box(menu_win, 0, 0);
    wrefresh(menu_win);
    
}

void menu::display(){
    mvwprintw(menu_win, 1, 1, r00);
    mvwprintw(menu_win, 2, 1, r01);
    mvwprintw(menu_win, 3, 1, r02);
    mvwprintw(menu_win, 4, 1, r03);
    mvwprintw(menu_win, 5, 1, r04);
    mvwprintw(menu_win, 6, 1, r05);
    mvwprintw(menu_win, 7, 1, r06);
    mvwprintw(menu_win, 8, 1, r07);
    mvwprintw(menu_win, 9, 1, r08);
    mvwprintw(menu_win, 10, 1, r09);
    mvwprintw(menu_win, 11, 1, r10);
    mvwprintw(menu_win, 12, 1, r11);
    mvwprintw(menu_win, 13, 1, r12);
    mvwprintw(menu_win, 14, 1, r13);
    mvwprintw(menu_win, 15, 1, r14);
    mvwprintw(menu_win, 16, 1, r15);
    mvwprintw(menu_win, 17, 1, r16);
    mvwprintw(menu_win, 18, 1, r17);
    box(menu_win, 0, 0);
    wrefresh(menu_win);
}
