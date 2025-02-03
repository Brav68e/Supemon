#include <unistd.h>





void displayNewplayer(void){

    char *texte = 
        "On dirait que tu es nouveau par ici !\n"
        "Ne t'en fais pas, je vais t'expliquer\n"
        "Tu vas devoir devenir le plus fort...\n"
        "Mais avant cela, il va te falloir un supémon\n";

    write(1, texte, 160);
}



void displayStarter(void){

    char *menu =
        "+-------------------------------+\n"
        "| Choisis ton starter Supémon:  |\n"
        "|  1 - Supmander                |\n"
        "|  2 - Supasaur                 |\n"
        "|  3 - Supirtle                 |\n"
        "+-------------------------------+\n";

    write(1, menu, 206);
}