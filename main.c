#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h> // Header-file for boolean data-type.
#include <math.h>

/*
Jan	31
Feb	28 (29 in leap years)   if year%4 == 0 february has 29 days, esle 28 days
Mar	31
Apr	30
May	31
Jun	30
Jul	31
Aug	31
Sep	30
Oct	31
Nov	30
Dec	31
*/

struct Month
{
    bool pastMonth;
    char* monthName;
    int nDays;
    int* days;
};


void displayCurrentDate()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mday, tm.tm_mon + 1, tm.tm_hour, tm.tm_min, tm.tm_sec);    
}

int currentYear()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

int currentMonth()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mon + 1;
}

int currentDay()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}

int currentDayZeller(int day, int month, int year)
{
    int reminder;
    int increaser = 0;
    int newF;
    /*  Zeller’s Rule
        F=k+ [(13*m-1)/5] +D+ [D/4] +[C/4]-2*C where 

        k is the day of the month.
        m is the month number. March is 1, April is 2….. January is 11 and February is 12.
        D is the last two digits of the year.
                Mod = 123 % 10 ==> 3
                Num = 123 / 10 ==> 12
        C is the first two digits of the year.

        Sun	    Mon	    Tue	    Wed	    Thurs   Fri     Sat
        0	    1	    2	    3	    4	    5	    6
    */
    int F, k, m, D, C;

    k = day;

    switch (month) 
    {
            case 3:
                m = 1;
                break;
            case 4:
                m = 2;
                break;
            case 5:
                m = 3;
                break;
            case 6:
                m = 4;
                break;
            case 7:
                m = 5;
                break;
            case 8:
                m = 6;
                break;
            case 9:
                m = 7;
                break;
            case 10:
                m = 8;
                break;
            case 11:
                m = 9;
                break;
            case 12:
                m = 10;
                break;
            case 1:
                m = 11;
                break;
            case 2:
                m = 12;
                break;                 
            default:
                return(1);
                break;
    }


    D = year % 100;
    C = year / 100;
    F = abs(k + (int)(((13*m)-1)/5) + D + (int)(D/4) + (int)(C/4) - (2*C));
    //printf("(int)(((13*m)-1)/5) = %i\n", (int)(((13*m)-1)/5));


    printf("k=%i, m=%i, D=%i, C=%i\n", k, m, D, C); //debug
    printf("F=%i\n", F); //debug

    while(((F - increaser)% 7) != 0)
        increaser++;

    newF = (F - increaser)/7;

    printf("Remainder: %i\n", increaser);
    return increaser;
}

void initialize()
{
    struct Month * months = malloc(sizeof(struct Month) * 12); //creating each month
    for (int i = 0; i < 12; i++)
        months[i].monthName = malloc(sizeof(char)*10); //allocating size for each month string name
    
    months[0].monthName = "January";
    months[1].monthName = "February";
    months[2].monthName = "March";
    months[3].monthName = "April";
    months[4].monthName = "May";
    months[5].monthName = "June";
    months[6].monthName = "July";
    months[7].monthName = "August";
    months[8].monthName = "September";
    months[9].monthName = "October";
    months[10].monthName = "November";
    months[11].monthName = "December";

    months[0].nDays = 31;
    months[0].days = malloc(sizeof(int) * months[0].nDays);
    if(currentYear()%4 == 0) //days of february
    {
        months[1].nDays = 29;
        months[1].days = malloc(sizeof(int) * months[1].nDays);
    }    
    else
    {
        months[1].nDays = 28;
        months[1].days = malloc(sizeof(int) * months[1].nDays);
    }
    months[2].nDays = 31;
    months[2].days = malloc(sizeof(int) * months[2].nDays);
    months[3].nDays = 30;
    months[3].days = malloc(sizeof(int) * months[3].nDays);
    months[4].nDays = 31;
    months[4].days = malloc(sizeof(int) * months[4].nDays);
    months[5].nDays = 30;
    months[5].days = malloc(sizeof(int) * months[5].nDays);
    months[6].nDays = 31;
    months[6].days = malloc(sizeof(int) * months[6].nDays);
    months[7].nDays = 31;
    months[7].days = malloc(sizeof(int) * months[7].nDays);
    months[8].nDays = 30;
    months[8].days = malloc(sizeof(int) * months[8].nDays);
    months[9].nDays = 31;
    months[9].days = malloc(sizeof(int) * months[9].nDays);
    months[10].nDays = 30;
    months[10].days = malloc(sizeof(int) * months[10].nDays);
    months[11].nDays = 31;
    months[11].days = malloc(sizeof(int) * months[11].nDays);

    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < months[i].nDays; j++)
        {
            months[i].days[j] = currentDayZeller(j+1, i+1, currentYear());
            printf("Imposto a %i\n", months[i].days[j]);
        }
    }

    printf("Printing %s's days: \n", months[6].monthName);
    for (int i = 0; i < 31; i++)
    {
        printf("July %ith: %i\n", i+1, months[6].days[i]);
    }
    printf("Current year: %i \n", currentYear());
    
    

    
    
        

}




int main()
{
    initialize();

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    displayCurrentDate();

    printf("Current day Zeller's formula: %i, with day=%i, month = %i, year = %i\n", currentDayZeller(currentDay(), currentMonth(), currentYear()), currentDay(), currentMonth(), currentYear());
   
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