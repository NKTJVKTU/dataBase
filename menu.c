#include "include/menu.h"

int menu()
{
    char char_choice[256];
    int int_choice = 0;
    system("clear");
    startScreen();
    fprintf(stdout, "\n");
    scanf("%s", char_choice);
    sscanf(char_choice, "%[0-9]d", char_choice);
    int_choice = atoi(char_choice);
    
    return int_choice;
}

void startScreen()
{
    fprintf(stdout, "oooo   oooo oooo   oooo ooooooooooo   ooooo ooooo  oooo oooo   oooo ooooooooooo ooooo  oooo\n");
    fprintf(stdout, " 8888o  88   888  o88   88  888  88    888   888    88   888  o88   88  888  88  888    88\n");
    fprintf(stdout, " 88 888o88   888888         888        888    888  88    888888         888      888    88\n");
    fprintf(stdout, " 88   8888   888  88o       888        888     88888     888  88o       888      888    88\n");
    fprintf(stdout, "o88o    88  o888o o888o    o888o       888      888     o888o o888o    o888o      888oo88\n");
    fprintf(stdout, "                                    8o888\n");
    fprintf(stdout, "База Данных -- Главное Меню: \n\n");
    fprintf(stdout, "1. Добавить запись\n");
    fprintf(stdout, "2. Удалить запись\n");
    fprintf(stdout, "3. Показать состав таблицы\n");
    fprintf(stdout, "9. Exit\n");
}