#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sales.h"

//2026-2-60-547
//Doing Work on monthly sales and daily sales

/* Appends one sale entry to sales.txt with today's date.
   Call this after a successful payment (cash or card). */
int record_sale(float amount)
{
    FILE *fp = fopen(SALES_FILE, "a"); // append mode, keeps old records
    if (fp == NULL)
    {
        printf("Error: could not open %s to save sale record\n", SALES_FILE);
        return -1;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_str[11]; // "YYYY-MM-DD" + '\0'
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", t);

    fprintf(fp, "%s,%.2f\n", date_str, amount);
    fclose(fp);
    return 0;
}

/* Shows total sales for TODAY, by reading sales.txt and summing
   every line whose date matches today's date. */
int daily_sales()
{
    FILE *fp = fopen(SALES_FILE, "r");
    if (fp == NULL)
    {
        printf("\nNo sales record found yet (sales.txt not created).\n");
        return 0;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", t);

    char line_date[11];
    float amount;
    float total = 0.0f;
    int count = 0;

    // Read each line, format: YYYY-MM-DD,amount
    while (fscanf(fp, "%10[^,],%f\n", line_date, &amount) == 2)
    {
        if (strcmp(line_date, today) == 0)
        {
            total += amount;
            count++;
        }
    }
    fclose(fp);

    printf("\n----- Daily Sales Report (%s) -----\n", today);
    printf("Total Orders : %d\n", count);
    printf("Total Sales  : %.2f\n", total);
    printf("------------------------------------\n");

    return 0;
}

/* Shows total sales for the CURRENT MONTH, by reading sales.txt and
   summing every line whose date's year-month matches the current month. */
int monthly_sales()
{
    FILE *fp = fopen(SALES_FILE, "r");
    if (fp == NULL)
    {
        printf("\nNo sales record found yet (sales.txt not created).\n");
        return 0;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char this_month[8]; // "YYYY-MM" + '\0'
    strftime(this_month, sizeof(this_month), "%Y-%m", t);

    char line_date[11];
    float amount;
    float total = 0.0f;
    int count = 0;

    while (fscanf(fp, "%10[^,],%f\n", line_date, &amount) == 2)
    {
        // compare only first 7 chars "YYYY-MM"
        if (strncmp(line_date, this_month, 7) == 0)
        {
            total += amount;
            count++;
        }
    }
    fclose(fp);

    printf("\n----- Monthly Sales Report (%s) -----\n", this_month);
    printf("Total Orders : %d\n", count);
    printf("Total Sales  : %.2f\n", total);
    printf("--------------------------------------\n");

    return 0;
}