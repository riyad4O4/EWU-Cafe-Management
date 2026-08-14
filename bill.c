
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
    //file *fp used for file handiling
    FILE *fp;

    fp = fopen("foods.txt", "r");

    if (fp == NULL)
    {
        printf("\nUnable to open foods.txt\n");
        return 0;
    }

    foodCount = 0;
// fscanf used to read data from file
    while (fscanf(fp, "%d %s %lf %d",
                  &foods[foodCount].id,
                  foods[foodCount].name,
                  &foods[foodCount].price,
                  &foods[foodCount].stock) == 4)
    {
        foodCount++;

        if (foodCount >= MAX_FOODS)
        {
            break;
        }
    }

    fclose(fp);
     //fclose used to close the file after reading

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
        printf("No food available.\n");
        return 0;
    }

    printf("\n=============================================\n");
    printf("            UNIVERSITY CAFE MENU\n");
    printf("=============================================\n");
    printf("ID\tfood\t\tPrice\tStock\n");
    for (i = 0; i < foodCount; i++)
    {
        printf("%d\t%s\t\t%.2lf\t%d\n",
               foods[i].id,
               foods[i].name,
               foods[i].price,
               foods[i].stock);
    }
    printf("=============================================\n");
    return 1;
}

/* Find food by ID */

int find_food_by_id(int id)
{
    int i;

    for(i = 0; i < foodCount; i++)
    {
        if(foods[i].id == id)
        {
            return i;
        }
    }

    return -1;
}
/* Add food to cart */

int add_to_cart()
{
    int id;
    int quantity;
    int position;

    printf("\nEnter Food ID: ");
    scanf("%d", &id);

    position = find_food_by_id(id);

    if(position == -1)
    {
        printf("Food not found.\n");
        return 0;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if(quantity <= 0)
    {
        printf("Invalid quantity.\n");
        return 0;
    }

    if(quantity > foods[position].stock)
    {
        printf("Not enough stock.\n");
        return 0;
    }

    if(cartCount >= MAX_CART)
    {
        printf("Cart is full.\n");
        return 0;
    }

    cart[cartCount].foodId = foods[position].id;

    strcpy(cart[cartCount].foodName,
           foods[position].name);

    cart[cartCount].price = foods[position].price;

    cart[cartCount].quantity = quantity;

    cart[cartCount].subtotal =
        foods[position].price * quantity;

    cartCount++;

    printf("Food added to cart.\n");

    return 1;
}/* Calculate total */

double calculate_total()
{
    int i;
    double total = 0;

    for(i = 0; i < cartCount; i++)
    {
        total = total + cart[i].subtotal;
    }

    return total;
}

