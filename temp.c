#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define DATABASE_FILE "database.db"
#define MAX_TABLES 50
#define PAGESIZE 4096
/*
    gcc main.c -o main && ./main   // создать файл mmap_file.txt перед выполнением
*/
struct Table {
    int id;
    char name[30];
};

struct DataBase
{
    struct Table tables[MAX_TABLES];
    int tables_count;
};

void create_table(char *table_name);
void write_data(void);
void init(void);

static struct DataBase db;

int main(void)
{
    init();

    //create_table("table_three");
    
    for (int i = 0; i < db.tables_count; i++)
        printf("id: %d name: %s\n", db.tables[i].id, db.tables[i].name);

    return 0;
}

void create_table(char *table_name)
{
    struct Table table;
    table.id = db.tables_count;
    strcpy(table.name, table_name);

    //t_arr.tables = malloc(sizeof(struct Table) * (t_arr.tables_count + 1));
    db.tables[db.tables_count] = table;
    db.tables_count = db.tables_count + 1;
    write_data();
}

void write_data(void)
{
    struct DataBase *map;
    int fd, sz, result;

    fd = open(DATABASE_FILE, O_RDWR | S_IRUSR | S_IWUSR);
    if(fd < 0){
        printf("\n\"%s \" could not open\n", DATABASE_FILE);
        exit(1);
    }

    struct stat st;
    if (fstat(fd, &st) < 0)
    {
        printf("\n\"%s \" could not open\n", DATABASE_FILE);
        exit(2);
    }

    result = lseek(fd, sizeof(struct DataBase), SEEK_SET); // (st.st_size + sizeof(struct Tables)) -1 need? 
    if (result == -1)
    {
        close(fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    result = write(fd, "", 1);
    if (result != 1)
    {
        close(fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    map = (struct DataBase*)mmap(0, (sizeof(struct DataBase)), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    map[0] = db;

    munmap(map, st.st_size);
    close(fd);
}

void init(void)
{
    int fd, sz;
    fd = open(DATABASE_FILE, O_RDONLY);
    struct DataBase *map;

    struct stat st;
    if (fstat(fd, &st) == -1)
    {
        printf("\n\"%s \" could not open\n", DATABASE_FILE);
        exit(2);
    }

    if (st.st_size == 0)
    {
        fprintf(stdout, "First init database\n");
        // create_work_tables();
    }
    else
    {
        map = (struct DataBase *)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        db = *map;
    }

    close(fd);
}
