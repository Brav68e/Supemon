#ifndef DISPLAY_H
#define DISPLAY_H

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

#endif