#ifndef MENU_H
#define MENU_H

#include <string>
#include "list.h"
#include "song.h"
#include <fstream>
#include <sstream>

class Menu
{
public:
    Menu();
    void userMenu();
    void adminMenu();
    void clearScreen();
    void saveSongs();
    void loadSongs();
    void saveBuyedSongs();
    void loadBuyedSongs();
    void loadLyrics(std::string songName);
    void barProgress();

};

#endif // MENU_H
