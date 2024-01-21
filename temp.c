#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define DATABASE_FILE "database.db"
#define MAX_TABLES 5
#define PAGESIZE 4096

struct Table {
    int id;
    char name[30];
};

struct Tables
{
    struct Table tables[MAX_TABLES];
    int tables_count;
};

void create_table(char *table_name);
void write_data(void);
void read_file(void);

static struct Tables t_arr;

int main(void)
{
    create_table("table_one");
    create_table("table_two");
    create_table("table_three");
    create_table("table_four");
    create_table("table_five");

    write_data();

    read_file();

    return 0;
}

void create_table(char *table_name)
{
    struct Table table;
    table.id = t_arr.tables_count;
    strcpy(table.name, table_name);

    //t_arr.tables = malloc(sizeof(struct Table) * (t_arr.tables_count + 1));
    t_arr.tables[t_arr.tables_count] = table;
    t_arr.tables_count = t_arr.tables_count + 1;
}

void write_data(void)
{
    struct Tables *map;
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
    printf("file size: %ld\n", st.st_size);

    result = lseek(fd, (sizeof(struct Tables)), SEEK_SET); // (st.st_size + sizeof(struct Tables)) -1 need? 
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

    map = (struct Tables*)mmap(0, (sizeof(struct Tables)), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    map[0] = t_arr;

    munmap(map, st.st_size);
    close(fd);
}

void read_file(void)
{
    int fd, sz;
    fd = open(DATABASE_FILE, O_RDONLY);
    struct Tables *map;

    struct stat st;
    if (fstat(fd, &st) == -1)
    {
        printf("\n\"%s \" could not open\n", DATABASE_FILE);
        exit(2);
    }
    printf("file size: %ld\n", st.st_size);

    map = (struct Tables *)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    for (int i = 0; i < MAX_TABLES; i++)
        fprintf(stdout, "id: %d name: %s\n", map->tables[i].id, map->tables[i].name);
}
