













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
    int current = 0;

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