#include "database.h"

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define COUNTRY_ID   0
#define COUNTRY_NAME 1

#define ACTION_EXIT  0
#define ACTION_PRINT 1
#define ACTION_ADD   2

int main()
{
    system("clear");
    static DataBase db;
    load_table("countries.csv", &db);

    int action;
    char welcome[80] = "Введите операцию";
    // scanf("%d", &action);
    // fprintf(stdout, "%d\n", action);

    while (1)
    {
        fprintf(stdout, 
           ANSI_COLOR_YELLOW "%s:\n" ANSI_COLOR_RESET
            "1. Отобразить данные\n"
            "2. Добавить данные\n"
            "0. Выход\n"
            "\n> ",
            welcome
        );
        
        if (scanf("%d", &action) != 1) {
            strcpy(welcome, "Необходимо выбрать одну из трех операций");
            scanf("%*s"); //очистка буфера
        }

        if (action != ACTION_EXIT && action != ACTION_PRINT && action != ACTION_ADD)
        {
            strcpy(welcome, "Необходимо выбрать одну из трех операций");
        }
        else if (action == ACTION_EXIT)
        {
            printf("\nBye Bye!\n");
            break;;
        }
        else if (action == ACTION_PRINT)
        {
            print_data(&db);
        }
        else if (action == ACTION_ADD)
            strcpy(welcome, "ADD");
      
    }
    
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
