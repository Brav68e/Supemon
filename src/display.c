













void displayBattlemenu(void){
    char msg[] = 
    "+--------------------------+\n"
    "| What will you do?        |\n"
    "|  1 - Move                |\n"
    "|  2 - Change Supémon      |\n"
    "|  3 - Use item            |\n"
    "|  4 - Capture             |\n"
    "|  5 - Run away            |\n"
    "+--------------------------+\n";

    write(1, msg, 224);
}



Item *displayItems(Player *player, int itemAvailable){
    
    Item *items = malloc(sizeof(Item) * itemAvailable);
    int current = 1;

    for(int i=0; i<player->itemAmount; i++){
        if(player->items[i].amount > 0){
            Item *item = player->items[i].item;
            printf("| %d - %s (X%d)\n", current, item.name, player->items[i].amount);
            items[current] = *item;
            current++;
        }
    }

    return items;
}



int *displaySupemons(Player *player, int amount){

    int *supemonsIndex = malloc(sizeof(int) * amount);
    int current = 1;

    for(int i=1; i<player->supemonAmount; i++){
        if(player->supemon[i].hp > 0){
            printf("| %d - %s (Hp : %d)\n", current, player->supemon[i].name, player->supemon[i].hp);
            supemonsIndex[current] = i;
            current++;
        }
    }

    return supemonsIndex;
}



void displayMoves(Supemon *supemon){

    for(int i=0; i<supemon->movesAmount; i++){
        printf("%d | %s (%d dmg)\n", i+1, supemon->moves[i].name, supemon->moves[i].dmg)
    }
}



void displayCapture(Supemon *enemy){

    printf("| You're trying to capture %s ...\n", enemy->name);
}


void displayCapturesuccess(void){

    write(1, "| You've just add him to your collection look like\n", 50);
}


void displayCapturefailure(void){

    write(1, "| Wow, that was close ! Maybe you should try to lower his Hp\n", 50);
}



void displayFullsupemon(Player *player){

    write(1, "| Wait a second, you got too many supémons\n", 50);
    write(1, "| You have to choose a supemon to discard\n", 50);
    for(int i=0; i<MAX_SUPEMON; i++){
        printf("%d | %s\n", i+1, player->supemons[i].name);
    }
}



void displayRunsuccess(void){
    write(1, "| You are really good at running, You've escape the fight\n", 50);
}


void displayRunfailure(void){
    write(1, "| You can't escape this guy that easily, you failed\n", 50);
}