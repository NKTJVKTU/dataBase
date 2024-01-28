#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define EOFields 0x0D
/*
    gcc temp.c -o temp && ./temp
*/

// #define EOFields 0x0D
typedef unsigned char byte;

typedef struct
{
    char version;
    char updYear;
    char updMonth;
    char updDay;
    unsigned int nRows;
    unsigned short headerLen;
    unsigned short recordLen;
    char other[20];
} DbfHeader;

typedef struct
{
    char name[11];
    char type;
    unsigned int fAddr;
    char fLen;
    char fDec;
    char other[14];
} DbfField;

typedef struct
{
    char name[80];
    char iso2[80];
    char un[11];
    char iso3[80];
    char other;
} DbfRow;

int main()
{
    int fd, fieldCount;
    size_t currPos;

    fd = open("world.dbf",O_RDONLY);
    struct stat st;
    fstat(fd, &st);

    void * buff;
    buff = mmap(0, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    DbfHeader *hdr = (DbfHeader *)buff;
    fieldCount = (hdr->headerLen / 32) - 1;

    DbfField *fields[fieldCount];
    currPos = sizeof(DbfHeader);
    for (int i = 0; i < fieldCount; i++, currPos += sizeof(DbfHeader))
        fields[i] = (DbfField *)(buff + currPos);
    
    DbfRow *rows[hdr->nRows];
    currPos = hdr->headerLen; // hdr->headerLen == началу блока с данными
    for (int i = 0; i < hdr->nRows; i++, currPos += sizeof(DbfRow)) // каждый раз прибавляем к началу блока с данными размер структуры DbfRow
        rows[i] = (DbfRow *)(buff + currPos);



    
    printf("\n");
    
    return 0;
}
