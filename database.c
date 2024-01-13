#include "include/database.h"

static DataBase db;

void initDataBase()
{
    load_table("countries.csv", &db);
}

static void load_table(char *table_name, DataBase *db)
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

static int get_file_rows(FILE *f)
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

void get_country_by_id(int country_id)
{
    for (int i = 0; i <= db.elements_count - 1; i++)
        if (db.countries[i].id == country_id)
            printf("id: %d name: %s\n", db.countries[i].id, db.countries[i].name);
}

void get_country_by_name(char *county_name)
{
    for (int i = 0; i <= db.elements_count - 1; i++)
        if (strcmpi(db.countries[i].name, county_name) == 0)
            printf("id: %d name: %s\n", db.countries[i].id, db.countries[i].name);
}

void print_all_data()
{
    for (int i = 0; i <= db.elements_count - 1; i++)
        printf("id: %d name: %s\n", db.countries[i].id, db.countries[i].name);
}

static int strcmpi(char* s1, char* s2)
{
    int i;
     
    if(strlen(s1) != strlen(s2))
        return -1;
         
    for(i = 0; i < strlen(s1); i++){
        if(toupper(s1[i]) != toupper(s2[i]))
            return s1[i] - s2[i];
    }
    
    return 0;
}

void free_data()
{
    free(db.countries);
}