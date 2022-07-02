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


void dayCodeToString(int code)
{
    
    //Mon	Tue	    Wed	    Thurs   Fri     Sat     Sun
    //1	    2	    3	    4	    5	    6       7
    switch (code) 
    {
            case 7:
                printf("Sunday");
                break;
            case 1:
                printf("Monday");
                break;
            case 2:
                printf("Tuesday");
                break;
            case 3:
                printf("Wednesday");
                break;
            case 4:
                printf("Thursday");
                break;
            case 5:
                printf("Friday");
                break;
            case 6:
                printf("Saturday");
                break;            
            default:
                break;
    }

}

void displayCurrentDate()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    //printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mday, tm.tm_mon + 1, tm.tm_hour, tm.tm_min, tm.tm_sec);    
    printf("%02d:%02d:%02d %d-%d-%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}



void displayDays()
{
    printf("| Mon | Tue | Wed | Thu | Fri | Sat | Sun |\n");
}

void displayMonth(int monthNumber, struct Month * month)
{
    int offset;
    if(month[monthNumber].days[0] > 0) //if the first day of the month isn't Sunday
        offset = month[monthNumber].days[0] - 1;
    else
        offset = 6;
    
    int* monthDays  = malloc(sizeof(int) * 35);

    //printf("month[monthNumber].days[0]: %i\n", month[monthNumber].days[0]); //debug
    printf("%s's offset: %i\n", month[monthNumber].monthName, offset); //debug
    printf("%s's days: %i\n", month[monthNumber].monthName, month->nDays);

    for (int i = 0; i < 35; i++)
    {
        monthDays[i] = 0;
        /*
        if(i < offset-1 || i > month->nDays)
            monthDays[i] = 0;
        else
            monthDays[i] = i-(offset-1);*/

        if (i >= offset -1 && i <= month->nDays)
            monthDays[i] = i-(offset-1);
            
    }
    /*
    char ** monthDaysStr = malloc(sizeof(char**) * 35);
    for (int i = 0; i < 35; i++)
    {
        monthDaysStr[i] = malloc(sizeof(char*)*3);
    }
    

    
    for (int i = 0; i < 35; i++)
    {
        if (monthDays[i] == 0)
        {
            monthDaysStr[i] = 0;
            //strcpy(monthDaysStr[i], "\0"); //THIS NEEDS TO BE CHECKED
        }
        else
            monthDaysStr[i][i] = monthDays[i] + '0';
            //itoa(monthDays[i], monthDaysStr[i], 10);

    }*/
    //IS CONVERTING TO CHAR THE RIGHT MOVE?
    
    printf("|-----|-----|-----|-----|-----|-----|-----|\n");
    printf("| %2i  |  %2i |  %2i |  %2i |  %2i |  %2i |  %2i |\n", monthDays[0], monthDays[1], monthDays[2], monthDays[3], monthDays[4], monthDays[5], monthDays[6]);
    printf("|-----|-----|-----|-----|-----|-----|-----|\n");
    printf("| %2i  |  %2i |  %2i |  %2i |  %2i |  %2i |  %2i |\n", monthDays[7], monthDays[8], monthDays[9], monthDays[10], monthDays[11], monthDays[12], monthDays[13]);
    printf("|-----|-----|-----|-----|-----|-----|-----|\n");
    printf("| %2i  |  %2i |  %2i |  %2i |  %2i |  %2i |  %2i |\n", monthDays[14], monthDays[15], monthDays[16], monthDays[17], monthDays[18], monthDays[19], monthDays[20]);
    printf("|-----|-----|-----|-----|-----|-----|-----|\n");
    printf("| %2i  |  %2i |  %2i |  %2i |  %2i |  %2i |  %2i |\n", monthDays[21], monthDays[22], monthDays[23], monthDays[24], monthDays[25], monthDays[26], monthDays[27]);
    printf("|-----|-----|-----|-----|-----|-----|-----|\n");
    printf("| %2i  |  %2i |  %2i |  %2i |  %2i |  %2i |  %2i |\n", monthDays[28], monthDays[29], monthDays[30], monthDays[31], monthDays[32], monthDays[33], monthDays[34]);
    printf("|-----|-----|-----|-----|-----|-----|-----|\n");
    
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

        Mon	    Tue	    Wed	    Thurs   Fri     Sat     Sun
        1	    2	    3	    4	    5	    6       7
    */
    int F, k, m, D, C;

    k = day;
    
    switch (month) 
    {
            case 3:
                m = 3;
                break;
            case 4:
                m = 4;
                break;
            case 5:
                m = 5;
                break;
            case 6:
                m = 6;
                break;
            case 7:
                m = 7;
                break;
            case 8:
                m = 8;
                break;
            case 9:
                m = 9;
                break;
            case 10:
                m = 10;
                break;
            case 11:
                m = 11;
                break;
            case 12:
                m = 12;
                break;
            case 1:
                m = 13;
                break;
            case 2:
                m = 14;
                break;                 
            default:
                return(1);
                break;
    }


    D = year % 100;
    C = year / 100;
    F = (k + (int)((13*(m+1))/5) + D + (int)(D/4) + (int)(C/4) - (2*C)) % 7;
    //printf("(int)((13*(m+1))/5) = %i\n", (int)((13*(m+1))/5));

    //printf("k=%i, m=%i, D=%i, C=%i, F=%i\n", k, m, D, C, F); //debug


    while(((F - increaser)% 7) != 0)
        increaser++;

    newF = (F - increaser)/7;

    //printf("Remainder: %i\n", increaser); //debug
    //return increaser;
    return ((F+5)%7)+1;

}

struct Month* initialize()
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
            //printf("Imposto a %i\n", months[i].days[j]); //debug
        }
    }

    
    //for debugging only
    for(int j = 0; j < 12; j++)
    {
        printf("Printing %s's days: \n", months[j].monthName);
        for (int i = 0; i < 31; i++)
        {
            printf("%s %ith %i: ",months[j].monthName, i+1, currentYear());
            dayCodeToString(months[j].days[i]);
            printf("\n");
        }
    }
    
    return months;
}




int main()
{
    struct Month * months  = initialize();

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //printf("Current day Zeller's formula: %i, with day=%i, month = %i, year = %i\n", currentDayZeller(currentDay(), currentMonth(), currentYear()), currentDay(), currentMonth(), currentYear());
   
    int menu;

    printf("\n");
    displayCurrentDate();
    //displayDays();
    //displayMonth(6, months);

    
    for (int i = 0; i < 12; i++)
    {
        printf("%s:\n", months[i].monthName);
        displayDays();
        displayMonth(i, months);
    }
    
    /*
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

    */

    return 0;
}