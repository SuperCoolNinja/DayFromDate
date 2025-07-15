#include <stdio.h>
#include <stdbool.h>

#define BASE_YEAR 1900

bool is_leap_year(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

void add_total_days_per_year(int year, int* total_days)
{
    if (total_days == NULL) return;

    if (year > BASE_YEAR)
    {
        for (int i = BASE_YEAR; i < year; i++)
            *total_days += is_leap_year(i) ? 366 : 365;
    }
    else if (year < BASE_YEAR)
    {
        for (int i = year; i < BASE_YEAR; i++)
            *total_days -= is_leap_year(i) ? 366 : 365;
    }


}

void add_total_days_per_month(int* total_days, int month, int days_in_months[])
{
    if (total_days == NULL) return;

    for (int i = 0; i < month - 1; i++)
        *total_days += days_in_months[i];
}



void edit_february_month(int year, int days_in_months[])
{
    days_in_months[1] = is_leap_year(year) ? 29 : 28;
}

int isValidDate(int month, int day, int year) {
    if (year < 1 || month < 1 || month > 12 || day < 1) return 0;

    int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    if (month == 2 && is_leap_year(year))
        return day <= 29;
    else
        return day <= daysInMonth[month];
}


int main(void)
{
    int day, month, year;
    int total_days = 0;
    int days_in_months[] = { 31, 28, 31, 30, 31, 30,31, 31, 30,31, 30,31 };
    const char* days[] = { "Monday", "Tuesday", "Wednesday", "Thirsday", "Friday", "Saturday", "Sunday" };

    printf("Enter a date (MM/DD/YYYY): ");

    if (scanf("%d/%d/%d", &month, &day, &year) != 3) {
        printf("Invalid input format. Please use MM/DD/YYYY.\n");
        return 1;
    }

    if (!isValidDate(month, day, year)) {
        printf("Invalid date.\n");
        return 1;
    }


    edit_february_month(year, days_in_months);
    add_total_days_per_year(year, &total_days);
    add_total_days_per_month(&total_days, month, days_in_months);

    total_days += day - 1;

    // this formula avoid negative rest so the result will always be a number between 0 - 6 :
    int index = (total_days % 7 + 7) % 7;

    printf("The day corresponding to the date %d/%d/%d is: %s\n", day, month, year, days[index]);

    return 0;
}