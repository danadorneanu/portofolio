#include <stdio.h>

static char daytab[2][13] = {
       {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
       {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
   int ret = 0;
   int year = 2000;
   int month = 5;
   int day = 5;
   int yearday = 0;

   int pmonth = 0, pday = 0;
   yearday = day_of_year(year, month, day);
   printf("\nThe day of the year for %d-%d-%d is %d\n", day, month, year,yearday);

   month_day(year, yearday, &pmonth, &pday);
   printf("\nFor the yearday %d the day is %d and the month is %d\n", yearday, pmonth, pday);

   return ret;


}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
   int i, leap;
   leap = (((year%4 == 0) && (year%100 != 0)) || (year%400 == 0));
   for (i = 1; i < month; i++)
   {
      day += *(*(daytab + leap) + i);
   }

   return day;
}
/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
   int i, leap;
   leap = (((year%4 == 0) && (year%100 != 0)) || (year%400 == 0));

   for (i = 1; yearday > daytab[leap][i]; i++)
      yearday -= *(*(daytab + leap) + i);
   *pmonth = i;
   *pday = yearday;
}

