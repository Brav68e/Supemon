#include <unistd.h>





void displayNewplayer(void){

    char *texte = 
        "\n| It looks like you're new here !\n"
        "| Don't worry tho, I'll guide you through\n"
        "| Your objectif is to become the strongest Trainer.\n"
        "| But first, you need a starter Supémon\n\n";

    write(1, texte, 172);
}


void displayOldplayer(void){
    char *texte =
        "\n| Welcome back Trainer !\n"
        "| It's been a while since your last visit\n"
        "| I guess you remember your goal, don't you ?\n"
        "| Well, you need to become the strongest Trainer\n"
        "| You have options, but what are you gonna pick this time\n\n";

    write(1, texte, 223);
}




void displayStarter(void){

    char *menu =
        "+-------------------------------+\n"
        "| Choose your starter Supémon:  |\n"
        "|  1 - Supmander                |\n"
        "|  2 - Supasaur                 |\n"
        "|  3 - Supirtle                 |\n"
        "+-------------------------------+\n";

    write(1, menu, 206);
}



void displayMainmenu(void){
    char *menu =
        "+-------------------------------+\n"
        "| Where do you want to go ?     |\n"
        "|  1 - Into the Wild            |\n"
        "|  2 - In the shop              |\n"
        "|  3 - In the Supémon Center    |\n"
        "|  4 - Leave the Game           |\n"
        "+-------------------------------+\n";

    write(1, menu, 240);
}