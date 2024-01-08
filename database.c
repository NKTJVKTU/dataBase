// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define COUNTRY_ID   0
#define COUNTRY_NAME 1

int main()
{
    DataBase db;
    load_table("countries.csv", &db);
    print_data(&db);

    free(db.countries);

    return 0;
}

void load_table(char *table_name, DataBase *db)
{
    char path[100];
    sprintf(path, "./files/%s", table_name);
    FILE *pf = fopen(path, "r");
    char buf[1024];
    int row = 0;
    int column = 0;

    int elements = get_file_rows(pf);
    rewind(pf);

    db->countries = malloc(sizeof(Country) * elements);
    db->elements_count = elements;

    for (; row <= elements; row++)
    {
        fgets(buf, 1024, pf);
        column = 0;
        if (row == 0)
            continue;

        char *value = strtok(buf, ",");
        while (value != NULL)
        {
            if (column == COUNTRY_ID)
                db->countries[row - 1].id = atoi(value);

            if (column == COUNTRY_NAME)
            {
                size_t len = strlen(value);
                if (value[len-1] == '\n')
                    value[len-1] = '\0';
                strcpy(db->countries[row - 1].name, value);
            }

            value = strtok(NULL, ",");
            column++;
        }
    }
    
    fclose(pf);
}

int get_file_rows(FILE *f)
{
    char c;
    int lines = 0;
    while ((c = getc(f)) != EOF)
    {
        if (c == '\n')
            lines += 1;
    }

    return lines;
}

void print_data(DataBase *db)
{
    for (int i = 0; i <= db->elements_count - 1; i++)
        printf("i: %i: id: %d name: %s\n", i, db->countries[i].id, db->countries[i].name);
}