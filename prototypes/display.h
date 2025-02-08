#ifndef DISPLAY_H
#define DISPLAY_H
#include "../prototypes/player.h"

void displayBattlemenu(void);
void displaySupemonstats(Supemon *sup1, Supemon *sup2);
Item *displayItems(Player *player, int itemAvailable);
int *displaySupemons(Player *player, int amount);
void displayMoves(Supemon *supemon);
void displayCapture(Supemon *enemy);
void displayCapturesuccess(void);
void displayCapturefailure(void);
void displayFullsupemon(Player *player);
void displayRunsuccess(void);
void displayRunfailure(void);
void displayForcedswitch(void);
void displayNewplayer(void);
void displayOldplayer(void);
void displayStarter(void);
void displayMainmenu(void);
void displayCentermenu(void);
void displayShopmenu(Player *player);

#endif