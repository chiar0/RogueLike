#include "menu.hpp"

menu::menu():display() {                                                                                                                                                                                                                                                 
set_dimensions(24, 80);
menu_win = newwin(height, width, 0, 0);
refresh();
//loop();
}

void menu::loop() {
    const char * r00[] = {"                                                                                              lllllll   iiii  kkkkkkkk                                 UUUUUUUU     UUUUUUUUNNNNNNNN        NNNNNNNN IIIIIIIIII BBBBBBBBBBBBBBBB      OOOOOOOOOOOOO        \0"};
    const char * r01[] = {"                                                                                              l:::::l   iiii  k::::::k                                 U::::::U     U::::::UN::::::::N      N::::::N I::::::::I B:::::::::::::::B   OO:::::::::::::OO      \0"};
    const char * r02[] = {"                                                                                              l:::::l         k::::::k                                 UU:::::U     U:::::UUN:::::::::N     N::::::N II::::::II B:::::BBBBBBB::::B O:::::::OOO:::::::O     \0"};
    const char * r03[] = {"rrrrr   rrrrrrrrr      ooooooooooo      ggggggggg   ggggguuuuuu    uuuuuu      eeeeeeeeeeee    l::::l iiiiiii  k:::::k    kkkkkkk eeeeeeeeeeee          U:::::U     U:::::U N::::::::::N    N::::::N   I::::I   B::::B     B:::::B O::::::O   O::::::O     \0"};
    const char * r04[] = {"r::::rrr:::::::::r   oo:::::::::::oo   g:::::::::ggg::::gu::::u    u::::u    ee::::::::::::ee  l::::l i:::::i  k:::::k   k:::::kee::::::::::::ee        U:::::D     D:::::U N:::::::::::N   N::::::N   I::::I   B::::B     B:::::B O:::::O     O:::::O     \0"};
    const char * r05[] = {"r:::::::::::::::::r o:::::::::::::::o g:::::::::::::::::gu::::u    u::::u   e::::::eeeee:::::eel::::l  i::::i  k:::::k  k:::::ke::::::eeeee:::::ee      U:::::D     D:::::U N:::::::N::::N  N::::::N   I::::I   B::::B     B:::::B O:::::O     O:::::O     \0"};
    const char * r06[] = {"rr::::::rrrrr::::::ro:::::ooooo:::::og::::::ggggg::::::ggu::::u    u::::u  e::::::e     e:::::el::::l  i::::i  k:::::k k:::::ke::::::e     e:::::e      U:::::D     D:::::U N::::::N N::::N N::::::N   I::::I   B::::BBBBBB:::::B  O:::::O     O:::::O     \0"};
    const char * r07[] = {" r:::::r     r:::::ro::::o     o::::og:::::g     g:::::g u::::u    u::::u  e:::::::eeeee::::::el::::l  i::::i  k::::::k:::::k e:::::::eeeee::::::e      U:::::D     D:::::U N::::::N  N::::N:::::::N   I::::I   B:::::::::::::BB   O:::::O     O:::::O     \0"};
    const char * r08[] = {" r:::::r     rrrrrrro::::o     o::::og:::::g     g:::::g u::::u    u::::u  e:::::::::::::::::e l::::l  i::::i  k:::::::::::k  e:::::::::::::::::e       U:::::D     D:::::U N::::::N   N:::::::::::N   I::::I   B::::BBBBBB:::::B  O:::::O     O:::::O     \0"};
    const char * r09[] = {" r:::::r            o::::o     o::::og:::::g     g:::::g u::::u    u::::u  e::::::eeeeeeeeeee  l::::l  i::::i  k:::::::::::k  e::::::eeeeeeeeeee        U:::::D     D:::::U N::::::N    N::::::::::N   I::::I   B::::B     B:::::B O:::::O     O:::::O     \0"};
    const char * r10[] = {" r:::::r            o::::o     o::::og::::::g    g:::::g u:::::uuuu:::::u  e:::::::e           l::::l  i::::i  k::::::k:::::k e:::::::e                 U::::::U   U::::::U N::::::N     N:::::::::N   I::::I   B::::B     B:::::B O::::::O   O::::::O     \0"};
    const char * r11[] = {" r:::::r            o:::::ooooo:::::og:::::::ggggg:::::g u:::::::::::::::uue::::::::e         l::::::li::::::ik::::::k k:::::ke::::::::e                U:::::::UUU:::::::U N::::::N      N::::::::N II::::::II B::::B     B:::::B O:::::::OOO:::::::O     \0"};
    const char * r12[] = {" r:::::r            o:::::::::::::::o g::::::::::::::::g  u:::::::::::::::u e::::::::eeeeeeee l::::::li::::::ik::::::k  k:::::ke::::::::eeeeeeee         UU:::::::::::::UU  N::::::N       N:::::::N I::::::::I B::::BBBBBB::::::B  OO:::::::::::::OO      \0"};
    const char * r13[] = {" r:::::r             oo:::::::::::oo   gg::::::::::::::g   uu::::::::uu:::u  ee:::::::::::::e l::::::li::::::ik::::::k   k:::::kee:::::::::::::e           UU:::::::::UU    N::::::N        N::::::N I::::::::I B:::::::::::::::B     OO:::::::::OO        \0"};
    const char * r14[] = {" rrrrrrr               ooooooooooo       gggggggg::::::g     uuuuuuuu  uuuu    eeeeeeeeeeeeee lllllllliiiiiiiikkkkkkkk    kkkkkkk eeeeeeeeeeeeee             UUUUUUUUU      NNNNNNNN         NNNNNNN IIIIIIIIII BBBBBBBBBBBBBBBB        OOOOOOOOO          \0"};
    const char * r15[] = {"                                                 g:::::g                                                                                                                                                                                                   \0"};
    const char * r16[] = {"                                     gggggg      g:::::g                                                                                                                                                                                                   \0"};
    const char * r17[] = {"                                     g:::::gg   gg:::::g                                                                                                                                                                                                   \0"};
    const char * r18[] = {"                                      g::::::ggg:::::::g                                                                                                                                                                                                   \0"};
    const char * r19[] = {"                                       gg::::::::::::gg                                                                                                                                                                                                    \0"};
    const char * r20[] = {"                                         gggggggggggg                                                                                                                                                                                                      \0"};
    WINDOW *start_win = newwin(3, 20, 0, 0);
    box(start_win, 17, 19);
    mvwprintw(start_win, 1, 1, "Start");
    int j = 0;
    while (true) {
        for (int i = 0; i < width; i++) {
            if (j == 252) j = 0;
            
            mvwprintw(menu_win, 0, i, r00[j]);
            mvwprintw(menu_win, 1, i, r01[j]);
            mvwprintw(menu_win, 2, i, r02[j]);
            mvwprintw(menu_win, 3, i, r03[j]);
            mvwprintw(menu_win, 4, i, r04[j]);
            mvwprintw(menu_win, 5, i, r05[j]);
            mvwprintw(menu_win, 6, i, r06[j]);
            mvwprintw(menu_win, 7, i, r07[j]);
            mvwprintw(menu_win, 8, i, r08[j]);
            mvwprintw(menu_win, 9, i, r09[j]);
            mvwprintw(menu_win, 10, i, r10[j]);
            mvwprintw(menu_win, 11, i, r11[j]);
            mvwprintw(menu_win, 12, i, r12[j]);
            mvwprintw(menu_win, 13, i, r13[j]);
            mvwprintw(menu_win, 14, i, r14[j]);
            mvwprintw(menu_win, 15, i, r15[j]);
            mvwprintw(menu_win, 16, i, r16[j]);
            mvwprintw(menu_win, 17, i, r17[j]);
            mvwprintw(menu_win, 18, i, r18[j]);
            mvwprintw(menu_win, 19, i, r19[j]);
            mvwprintw(menu_win, 20, i, r20[j]);

            wrefresh(menu_win);
            wrefresh(start_win);
            j++;
        }
    }
}