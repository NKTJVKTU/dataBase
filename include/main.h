#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"


// typedef struct capital
// {
//     int countryid;
//     char name[20];
// } Capital;

#define COUNTRY_ID   0
#define COUNTRY_NAME 1

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ACTION_EXIT  0
#define ACTION_PRINT 1
#define ACTION_ADD   2
