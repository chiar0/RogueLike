#include "menu.hpp"

menu::menu():display() {                                                                                                                                                                                                                                              
    set_dimensions(24, 80);
    menu_win = newwin(height, width, 0, 0);
    refresh();
    //WINDOW *start_win = newwin(3, 20, 0, 0);
    //refresh();
    loop();
}

void menu::loop() {
    std::string r00 = "                                                                                                   lllllll   iiii  kkkkkkkk                                 UUUUUUUU     UUUUUUUUNNNNNNNN        NNNNNNNN IIIIIIIIII BBBBBBBBBBBBBBBB      OOOOOOOOOOOOO        \0";
    std::string r01 = "                                                                                                   l:::::l   iiii  k::::::k                                 U::::::U     U::::::UN::::::::N      N::::::N I::::::::I B:::::::::::::::B   OO:::::::::::::OO      \0";
    std::string r02 = "                                                                                                   l:::::l         k::::::k                                 UU:::::U     U:::::UUN:::::::::N     N::::::N II::::::II B::::BBBBBBB::::B  O:::::::OOO:::::::O     \0";
    std::string r03 = "     rrrrr   rrrrrrrrr      ooooooooooo      ggggggggg   ggggguuuuuu    uuuuuu      eeeeeeeeeeee    l::::l iiiiiii  k:::::k    kkkkkkk eeeeeeeeeeee          U:::::U     U:::::U N::::::::::N    N::::::N   I::::I   B::::B     B:::::B O::::::O   O::::::O     \0";
    std::string r04 = "     r::::rrr:::::::::r   oo:::::::::::oo   g:::::::::ggg::::gu::::u    u::::u    ee::::::::::::ee  l::::l i:::::i  k:::::k   k:::::kee::::::::::::ee        U:::::D     D:::::U N:::::::::::N   N::::::N   I::::I   B::::B     B:::::B O:::::O     O:::::O     \0";
    std::string r05 = "     r:::::::::::::::::r o:::::::::::::::o g:::::::::::::::::gu::::u    u::::u   e::::::eeeee:::::eel::::l  i::::i  k:::::k  k:::::ke::::::eeeee:::::ee      U:::::D     D:::::U N:::::::N::::N  N::::::N   I::::I   B::::B     B:::::B O:::::O     O:::::O     \0";
    std::string r06 = "     rr::::::rrrrr::::::ro:::::ooooo:::::og::::::ggggg::::::ggu::::u    u::::u  e::::::e     e:::::el::::l  i::::i  k:::::k k:::::ke::::::e     e:::::e      U:::::D     D:::::U N::::::N N::::N N::::::N   I::::I   B::::BBBBBB:::::B  O:::::O     O:::::O     \0";
    std::string r07 = "      r:::::r     r:::::ro::::o     o::::og:::::g     g:::::g u::::u    u::::u  e:::::::eeeee::::::el::::l  i::::i  k::::::k:::::k e:::::::eeeee::::::e      U:::::D     D:::::U N::::::N  N::::N:::::::N   I::::I   B:::::::::::::BB   O:::::O     O:::::O     \0";
    std::string r08 = "      r:::::r     rrrrrrro::::o     o::::og:::::g     g:::::g u::::u    u::::u  e:::::::::::::::::e l::::l  i::::i  k:::::::::::k  e:::::::::::::::::e       U:::::D     D:::::U N::::::N   N:::::::::::N   I::::I   B::::BBBBBB:::::B  O:::::O     O:::::O     \0";
    std::string r09 = "      r:::::r            o::::o     o::::og:::::g     g:::::g u::::u    u::::u  e::::::eeeeeeeeeee  l::::l  i::::i  k:::::::::::k  e::::::eeeeeeeeeee        U:::::D     D:::::U N::::::N    N::::::::::N   I::::I   B::::B     B:::::B O:::::O     O:::::O     \0";
    std::string r10 = "      r:::::r            o::::o     o::::og::::::g    g:::::g u:::::uuuu:::::u  e:::::::e           l::::l  i::::i  k::::::k:::::k e:::::::e                 U::::::U   U::::::U N::::::N     N:::::::::N   I::::I   B::::B     B:::::B O::::::O   O::::::O     \0";
    std::string r11 = "      r:::::r            o:::::ooooo:::::og:::::::ggggg:::::g u:::::::::::::::uue::::::::e         l::::::li::::::ik::::::k k:::::ke::::::::e                U:::::::UUU:::::::U N::::::N      N::::::::N II::::::II B::::B     B:::::B O:::::::OOO:::::::O     \0";
    std::string r12 = "      r:::::r            o:::::::::::::::o g::::::::::::::::g  u:::::::::::::::u e::::::::eeeeeeee l::::::li::::::ik::::::k  k:::::ke::::::::eeeeeeee         UU:::::::::::::UU  N::::::N       N:::::::N I::::::::I B::::BBBBBB::::::B  OO:::::::::::::OO      \0";
    std::string r13 = "      r:::::r             oo:::::::::::oo   gg::::::::::::::g   uu::::::::uu:::u  ee:::::::::::::e l::::::li::::::ik::::::k   k:::::kee:::::::::::::e           UU:::::::::UU    N::::::N        N::::::N I::::::::I B:::::::::::::::B     OO:::::::::OO        \0";
    std::string r14 = "      rrrrrrr               ooooooooooo       gggggggg::::::g     uuuuuuuu  uuuu    eeeeeeeeeeeeee lllllllliiiiiiiikkkkkkkk    kkkkkkk eeeeeeeeeeeeee             UUUUUUUUU      NNNNNNNN         NNNNNNN IIIIIIIIII BBBBBBBBBBBBBBBB        OOOOOOOOO          \0";
    std::string r15 = "                                                      g:::::g                                                                                                                                                                                                   \0";
    std::string r16 = "                                          gggggg      g:::::g                                                                                                                                                                                                   \0";
    std::string r17 = "                                          g:::::gg   gg:::::g                                                                                                                                                                                                   \0";
    std::string r18 = "                                           g::::::ggg:::::::g                                                                                                                                                                                                   \0";
    std::string r19 = "                                            gg::::::::::::gg                                                                                                                                                                                                    \0";
    std::string r20 = "                                              gggggggggggg                                                                                                                                                                                                      \0";

    int i = 0, j = 0;
    while (getch() != 'x') {  
        for (i = 0; i <= width - 1; i++) {
            bool b = true; 
            while (b == true){ 
                t->tick();
                if(t->getDeltaTime() >= 1/fps){
                    touchwin(menu_win);
                    mvwprintw(menu_win, 0, i, r00.c_str() + j);
                    mvwprintw(menu_win, 1, i, r01.c_str() + j);
                    mvwprintw(menu_win, 2, i, r02.c_str() + j);
                    mvwprintw(menu_win, 3, i, r03.c_str() + j);
                    mvwprintw(menu_win, 4, i, r04.c_str() + j);
                    mvwprintw(menu_win, 5, i, r05.c_str() + j);
                    mvwprintw(menu_win, 6, i, r06.c_str() + j);
                    mvwprintw(menu_win, 7, i, r07.c_str() + j);
                    mvwprintw(menu_win, 8, i, r08.c_str() + j);
                    mvwprintw(menu_win, 9, i, r09.c_str() + j);
                    mvwprintw(menu_win, 10, i, r10.c_str() + j);
                    mvwprintw(menu_win, 11, i, r11.c_str() + j);
                    mvwprintw(menu_win, 12, i, r12.c_str() + j);
                    mvwprintw(menu_win, 13, i, r13.c_str() + j);
                    mvwprintw(menu_win, 14, i, r14.c_str() + j);
                    mvwprintw(menu_win, 15, i, r15.c_str() + j);
                    mvwprintw(menu_win, 16, i, r16.c_str() + j);
                    mvwprintw(menu_win, 17, i, r17.c_str() + j);
                    mvwprintw(menu_win, 18, i, r18.c_str() + j);
                    mvwprintw(menu_win, 19, i, r19.c_str() + j);
                    mvwprintw(menu_win, 20, i, r20.c_str() + j);
                    box(menu_win, 0, 0);
                    wrefresh(menu_win);
                    j++;
                    b = false;
                }
                //std::cout << t->getDeltaTime() << std::endl;
                //getch();
            }
            t->reset();
            //getch();
            if (j >= 256) j-=256;
        }
        j = j - width + 1;
    }
}