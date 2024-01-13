#include "include/main.h"
#include "include/database.h"

int main()
{
    printf("\n");
    int action;
    initDataBase();

    // get_country_by_id(3);
    get_country_by_name("Russia");
    
    free_data();
    
    return 0;
}
