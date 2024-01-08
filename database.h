#include <stdio.h>

// typedef struct capital
// {
//     int countryid;
//     char name[20];
// } Capital;

typedef struct country
{
    int id;
    char name[50];
    // Capitals capital;
} Country;

typedef struct dataBase
{
    int elements_count;
    Country *countries;
} DataBase;


void load_table(char *table_name, DataBase *db);
int get_file_rows(FILE *f);
void print_data(DataBase *db);