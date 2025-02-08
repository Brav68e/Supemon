#ifndef BATTLE_H
#define BATTLE_H


void battle(Player *player);
int checkBattleEnd(Player *player, Supemon *enemy);
int switchPossible(Player *player);
int getRandomMove(Supemon *enemy);
void useMove(Supemon *user, Supemon* opponent, int moveIndex);
int useItem(Player *player);
int switchSupemon(Player *player, int forced);
void getLevel(Supemon *supemon, int level, int display);
void getExp(Supemon *supemon, int exp);
int selectMove(Player *player);
int capture(Player *player, Supemon *enemy);
void getReward(Player *player, Supemon *enemy);
int runAway(Player *player, Supemon *enemy);
void removeBuffs(Supemon *supemon);
void enemyLevel(Supemon *enemy, Player *player);

#endif