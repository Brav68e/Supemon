#ifndef SUPEMON_H
#define SUPEMON_H

typedef struct{
    char stat[16];      // Ex : atk
    int value;
} Buff;



typedef struct{
    char name[32];
    int dmg;
    int buffAmount;
    Buff *statChanges;
} Move;



typedef struct{
    char name[32];
    int level, nextLevel;
    int xp;
    int hp, maxHp;
    int atk, baseAtk;
    int def, baseDef;
    int dodge, baseDodge;
    int accuracy, baseAccuracy;
    int speed;
    Move *moves;
    int movesAmount;
} Supemon;



void freeSupemon(Supemon *supemon);
Supemon *loadSupemon(char research[32]);

#endif