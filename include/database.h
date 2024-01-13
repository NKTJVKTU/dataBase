#include "main.h"
#include <ctype.h>

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

void initDataBase();
static void load_table(char *table_name, DataBase *db);
static int get_file_rows(FILE *f);
void get_country_by_id(int country_id);
void get_country_by_name(char *county_name);
void print_all_data();
static int strcmpi(char* s1, char* s2);
void free_data();