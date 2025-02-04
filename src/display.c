













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