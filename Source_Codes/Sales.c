//2026-2-60-547
//Doing Work on sales tracking
#include <stdio.h>
#include "sales.h"
#include "stdlib.h"

/* Appends one sale entry (amount) to sales.txt.
   Call this after a successful payment (cash or card). */
int record_sale(float amount)
{
    FILE *fp = fopen(SALES_FILE, "a"); // append mode, keeps old records
    if (fp == NULL)
    {
        printf("Error: could not open %s to save sale record\n", SALES_FILE);
        return -1;
    }

    fprintf(fp, "%.2f\n", amount);
    fclose(fp);
    return 0;
}

/* Reads sales.txt, sums up every recorded amount,
   and shows the total revenue so far. */
int total_revenue()
{
    FILE *fp = fopen(SALES_FILE, "r");
    if (fp == NULL)
    {
        printf("\nNo sales record found yet (sales.txt not created).\n");
        return 0;
    }

    float amount;
    float total = 0.0f;
    int count = 0;

    // Read each line, format: amount
    while (fscanf(fp, "%f\n", &amount) == 1)
    {
        total += amount;
        count++;
    }
    fclose(fp);

    printf("\n----- Total Revenue -----\n");
    printf("Total Orders  : %d\n", count);
    printf("Total Revenue : %.2f\n", total);
    printf("--------------------------\n");
    printf("Press Enter to continue...");
        getchar();
        getchar();

        system("cls");

    return 0;
}