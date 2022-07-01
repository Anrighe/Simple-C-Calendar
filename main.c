#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct month
{
    char* monthName[10];
    int days;


};


void displayCurrentDate()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mday, tm.tm_mon + 1, tm.tm_hour, tm.tm_min, tm.tm_sec);    
}


void initialize()
{
    
}




int main()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    displayCurrentDate();

    int currentYear = tm.tm_year + 1900;
    
    
    
    int menu;



    printf("Enter a month: ");
    scanf("%d", &menu);
    switch (menu) 
    {
            case 1:
                printf("LOOOL???");
                break;
            case 8:
                printf("Value is 8");
                break;
            case 9:
                printf("Value is 9");
                break;
            default:
                printf("Out of range");
                break;
        }



    return 0;
}