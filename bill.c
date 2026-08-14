
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bill.h"

    /* Global Arrays */

    Food foods[MAX_FOODS];
int foodCount = 0;

CartItem cart[MAX_CART];
int cartCount = 0;

/*--------------------------------------------------
    Load foods from foods.txt
    Return:
    1 = Successfully loaded
    0 = Failed to load
--------------------------------------------------*/
int load_foods()
{
    FILE *fp;

    fp = fopen("foods.txt", "r");

    if (fp == NULL)
    {
        printf("\nUnable to open foods.txt\n");
        return 0;
    }

    foodCount = 0;

    while (fscanf(fp, "%d %s %lf %d",
                  &foods[foodCount].id,
                  foods[foodCount].name,
                  &foods[foodCount].price,
                  &foods[foodCount].stock) == 4)
    {
        foodCount++;

        if (foodCount >= MAX_FOODS)
            break;
    }

    fclose(fp);

    return 1;
}

/*--------------------------------------------------
    Display Available Foods
    Return:
    1 = Successfully displayed
    0 = No food available
--------------------------------------------------*/
int display_foods()
{
    int i;

    if (foodCount == 0)
    {
        printf("\nNo food available.\n");
        return 0;
    }

    printf("\n=============================================\n");
    printf("            UNIVERSITY CAFE MENU\n");
    printf("=============================================\n");

    printf("%-5s %-20s %-10s %-10s\n",
           "ID", "Food", "Price", "Stock");

    printf("=============================================\n");

    for (i = 0; i < foodCount; i++)
    {
        printf("%-5d %-20s %-10.2lf %-10d\n",
               foods[i].id,
               foods[i].name,
               foods[i].price,
               foods[i].stock);
    }

    printf("=============================================\n");

    return 1;
}

int print_receipt(total_bill, selected_id)
{
    int id;
    char name[30];
    float price;
    FILE *file;
    file = fopen("foods.txt", "a");
    while (file = !EOF)
    {
        fscanf(file, "%d %s %f", &id, &name, &price);
    }
}