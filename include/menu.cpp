#include "menu.hpp"

menu::menu():display() {                                                                                                                                                                                                                                              
    set_dimensions(21, 58);
    menu_win = newwin(height, width, 0, 0);
    refresh();

    const char *  r00[] = {"                      lllllll UUUUUUU     UUUUUUU "};
    const char *  r01[] = {"                      l:::::l U:::::U     U:::::U "};
    const char *  r02[] = {"                      l:::::l UU::::U     U:::::U "};
    const char *  r03[] = {" rrrrr   rrrrrrrrr    l::::l  U:::::U     U:::::U "};
    const char *  r04[] = {" r::::rrr:::::::::r   l::::l  U:::::D     D:::::U "};
    const char *  r05[] = {" r:::::::::::::::::r  l::::l  U:::::D     D:::::U "};
    const char *  r06[] = {" rr::::::rrrrr::::::r l::::l  U:::::D     D:::::U "};
    const char *  r07[] = {"  r:::::r     r:::::r l::::l  U:::::D     D:::::U "};
    const char *  r08[] = {"  r:::::r     rrrrrrr l::::l  U:::::D     D:::::U "};
    const char *  r09[] = {"  r:::::r             l::::l  U:::::D     D:::::U "};
    const char *  r10[] = {"  r:::::r             l::::l  U::::::U   U::::::U "};
    const char *  r11[] = {"  r:::::r            l::::::l U:::::::UUU:::::::U "};
    const char *  r12[] = {"  r:::::r            l::::::l UU:::::::::::::UU   "};
    const char *  r13[] = {"  r:::::r            l::::::l   UU:::::::::UU     "};
    const char *  r14[] = {"  rrrrrrr            llllllll     UUUUUUUUU       "};
    const char *  r15[] = {"                                                  "};
    const char *  r16[] = {"              ROGUELIKE UNIBO                     "};
    const char *  r17[] = {"            PREMI X PER INIZIARE                  "};

    
    //touchwin(menu_win);
    mvwprintw(menu_win, 1, 1, r00[1]);
    mvwprintw(menu_win, 2, 1, r01[1]);
    mvwprintw(menu_win, 3, 1, r02[1]);
    mvwprintw(menu_win, 4, 1, r03[1]);
    mvwprintw(menu_win, 5, 1, r04[1]);
    mvwprintw(menu_win, 6, 1, r05[1]);
    mvwprintw(menu_win, 7, 1, r06[1]);
    mvwprintw(menu_win, 8, 1, r07[1]);
    mvwprintw(menu_win, 9, 1, r08[1]);
    mvwprintw(menu_win, 10, 1, r09[1]);
    mvwprintw(menu_win, 11, 1, r10[1]);
    mvwprintw(menu_win, 12, 1, r11[1]);
    mvwprintw(menu_win, 13, 1, r12[1]);
    mvwprintw(menu_win, 14, 1, r13[1]);
    mvwprintw(menu_win, 15, 1, r14[1]);
    mvwprintw(menu_win, 16, 1, r15[1]);
    mvwprintw(menu_win, 17, 1, r16[1]);
    mvwprintw(menu_win, 18, 1, r17[1]);
    box(menu_win, 0, 0);
    wrefresh(menu_win);
    
}
