#ifndef BILL_H
#define BILL_H

#define MAX_FOODS 100
#define MAX_CART 50

/* Food Structure */
typedef struct
{
    int id;
    char name[50];
    double price;
    int stock;
} Food;

/* Cart Structure */
typedef struct
{
    int foodId;
    char foodName[50];
    double price;
    int quantity;
    double subtotal;
} CartItem;

/* Main Functions */
void place_order();
void add_to_cart();
void generate_bill();
void print_receipt();

/* Helper Functions */
void load_foods();
void display_foods();
int find_food_by_id(int id);
double calculate_total();
void update_stock();
void save_sale_record();

/* Global Variables */
extern Food foods[MAX_FOODS];
extern int foodCount;

extern CartItem cart[MAX_CART];
extern int cartCount;

#endif
//***************
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
--------------------------------------------------*/
void load_foods()
{
    FILE *fp;

    fp = fopen("foods.txt", "r");

    if(fp == NULL)
    {
        printf("\nUnable to open foods.txt\n");
        return;
    }

    foodCount = 0;

    while(fscanf(fp,"%d %s %lf %d",
                 &foods[foodCount].id,
                 foods[foodCount].name,
                 &foods[foodCount].price,
                 &foods[foodCount].stock) == 4)
    {
        foodCount++;

        if(foodCount >= MAX_FOODS)
            break;
    }

    fclose(fp);
}
/*--------------------------------------------------
    Display Available Foods
--------------------------------------------------*/
void display_foods()
{
    int i;

    printf("\n=============================================\n");
    printf("            UNIVERSITY CAFE MENU\n");
    printf("=============================================\n");

    printf("%-5s %-20s %-10s %-10s\n",
           "ID","Food","Price","Stock");

    printf("=============================================\n");

    for(i=0;i<foodCount;i++)
    {
        printf("%-5d %-20s %-10.2lf %-10d\n",
               foods[i].id,
               foods[i].name,
               foods[i].price,
               foods[i].stock);
    }

    printf("=============================================\n");
}
/*--------------------------------------------------
    Search Food Using ID
--------------------------------------------------*/
int find_food_by_id(int id)
{
    int i;

    for(i=0;i<foodCount;i++)
    {
        if(foods[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


