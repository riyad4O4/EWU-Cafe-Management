// ID: 2026-2-60-094
#include <stdio.h>
#include "payment.h"
#include <string.h>
#include <time.h>


#define SALES_FILE "sales.txt"

static int record_sale(float amount);


int cash_payment(float total_bill) // takes total bill
{
    float cash;
    printf("\nCASH : ");
    scanf("%f", &cash); // takes customers cash amount
    if (cash < total_bill)
    {
        printf("Insufficient cash\n");
        return cash_payment(total_bill); // if customer pays less than total bill it starts again
    }
    printf("Change %f\n", cash - total_bill); // calculates change
    printf("Order Paid Successfully\n");
    record_sale(total_bill);
    return 0;
}
int card_payment(float total_bill) // takes total bill
{
    float temp, amount;
    int count = 0;
    while (1) // infinite loop until payments success
    {
        printf("Total Bill %f\n", total_bill);
        printf("Enter amount to pay : \n");
        scanf("%f", &amount);

        if (amount == total_bill)
        {
            printf("Enter Pin : \n");
            scanf("%f", &temp); // sudo pin input
            printf("Order Paid Successfully\n");
            record_sale(total_bill);
            return 0;
        }
        else
        {
            printf("Payment Failed !!!\n");
            printf("Invalid amount \n");
            count++;
        }

        if (count == 3)
        {
            printf("Order cancelled\n");
            printf("Pay Via Cash\n");
            cash_payment(total_bill);
            break;
        }
    }
    return 0;
}
int discount(float total_bill) // takes total bill
{
    if (total_bill > 1000) // if bill is greater than 1000 added 5% discount
    {
        total_bill = total_bill - (total_bill * 0.05); // 5% discount added
        printf("\nPrice after 5%% discount = %f\n", total_bill);
    }

    return 0;
}


//2026-2-60-547

//Doing Work on monthly sales and daily sales 


/* Appends one sale entry to sales.txt with today's date.
   Call this after a successful payment (cash or card). */
static int record_sale(float amount)
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

/* Shows total sales for TODAY, by reading sales.txt and do sum
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