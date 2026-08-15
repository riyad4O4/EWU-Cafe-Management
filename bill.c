
#include <stdio.h>           //student ID: 2026-2-60-024
#include <stdlib.h>
#include <string.h>

#include "bill.h"

    /* Global variables */

    Food foods[MAX_FOODS];
int foodCount = 0;

CartItem cart[MAX_CART];
int cartCount = 0;

//load foods from foods.txt


int load_foods()
{  
    //file *fp used for file handiling
    FILE *fp;

    fp = fopen("foods.txt", "r");

    if (fp == NULL)
    {
        printf("\nCannot open foods.txt\n");
        return 0;
    }

    foodCount = 0;


    /*format of foods.txt:
    1 chiken fry 120.00 10
    here the first word is ID.
    the last two values are price and stock.
    the name is between id and price.*/

}
while(fgets(line, sizeof(line), fp) != NULL)
    {
        char name[50];
        double price;
        int id;
        int stock;
        int i;
        int result;

        result = sscanf(line, "%d %[^\n] %lf %d",
                        &id,
                        name,
                        &price,
                        &stock);

        if(result == 4)
                {
            /*
               The above method can still cause problems
               because name may contain price and stock.

               So we manually find the last two values.
            */

            i = strlen(line) - 1;

            while(i >= 0 && line[i] == '\n')
            {
                line[i] = '\0';
                i--;
            }

            /* Read ID */
            if(sscanf(line, "%d", &id) != 1)
            {
                continue;
            }

            /*
               Find the food name and last two numbers.
               This method expects:
               ID Food_Name Price Stock
            */
            {
                char tempName[50];

                if(sscanf(line, "%d %49[^\n]", &id, tempName) == 2)
                {
                    char *lastSpace;
                    char *secondLastSpace;

                    lastSpace = strrchr(tempName, ' ');

                    if(lastSpace == NULL)
                    {
                        continue;
                    }

                    stock = 0;
                    price = 0;

                    sscanf(lastSpace + 1, "%d", &stock);

                    *lastSpace = '\0';

                    secondLastSpace = strrchr(tempName, ' ');

                    if(secondLastSpace == NULL)
                    {
                        continue;
                    }

                    price = 0;
                    sscanf(secondLastSpace + 1, "%lf", &price);

                    *secondLastSpace = '\0';

                    strcpy(name, tempName);
                }
                else
                {
                    continue;
                }
            }

            if(foodCount < MAX_FOODS)
            {
                foods[foodCount].id = id;

                strcpy(foods[foodCount].name, name);

                foods[foodCount].price = price;

                foods[foodCount].stock = stock;

                foodCount++;
            }
        }
    }

    fclose(fp);

    return 1;
}




// fixed bug and edited from here .
/*
    Display Available Foods
*/

int display_foods()
{
    int i;

    if(foodCount == 0)
    {
        printf("\nNo food available.\n");
        return 0;
    }
// fixed bug and edited from here .

    printf("\n=============================================\n");
    printf("          UNIVERSITY CAFE MENU\n");
    printf("=============================================\n");

    printf("%-5s %-25s %-10s %-10s\n",
           "ID",
           "Food",
           "Price",
           "Stock");

    printf("=============================================\n");

    for(i = 0; i < foodCount; i++)
    {
        printf("%-5d %-25s %-10.2lf %-10d\n",
               foods[i].id,
               foods[i].name,
               foods[i].price,
               foods[i].stock);
    }

    printf("=============================================\n");

    return 1;
}
/*
    Find Food By ID
*/

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
/*
    Add Food To Cart
*/

int add_to_cart()
{
    int id;
    int quantity;
    int position;
    int i;

    printf("\nEnter Food ID: ");

    if(scanf("%d", &id) != 1)
    {
        printf("Invalid ID. Please enter a number.\n");

        while(getchar() != '\n')
        {
        }

        return 0;
    }

    position = find_food_by_id(id);

    if(position == -1)
    {
        printf("Food not found.\n");
        return 0;
    }

    if(foods[position].stock <= 0)
    {
        printf("This food is out of stock.\n");
        return 0;
    }

    printf("Enter Quantity: ");

    if(scanf("%d", &quantity) != 1)
    {
        printf("Invalid quantity. Please enter a number.\n");

        while(getchar() != '\n')
        {
        }

        return 0;
    }

    if(quantity <= 0)
    {
        printf("Quantity must be greater than 0.\n");
        return 0;
    }
printf("Enter Quantity: ");

    if(scanf("%d", &quantity) != 1)
    {
        printf("Invalid quantity. Please enter a number.\n");

        while(getchar() != '\n')
        {
        }

        return 0;
    }

    if(quantity <= 0)
    {
        printf("Quantity must be greater than 0.\n");
        return 0;
    }

    /*
       Check actual remaining stock.
    */

    if(quantity > foods[position].stock)
    {
        printf("Not enough stock.\n");
        printf("Available stock: %d\n",
               foods[position].stock);

        return 0;
    }


    /*
       Check whether the same food
       already exists in the cart.
    */

    for(i = 0; i < cartCount; i++)
    {
        if(cart[i].foodId == foods[position].id)
        {
            /*
               Increase existing quantity.
            */

            cart[i].quantity =
                cart[i].quantity + quantity;

            /*
               Recalculate subtotal.
            */

            cart[i].subtotal =
                cart[i].price * cart[i].quantity;

            /*
               *****
               Reduce stock immediately.
            */

            foods[position].stock =
                foods[position].stock - quantity;

            printf("\nFood quantity updated in cart.\n");

            printf("New quantity: %d\n",
                   cart[i].quantity);

            printf("Remaining stock: %d\n",
                   foods[position].stock);

            return 1;
        }
    }


    /*
       If food does not already exist,
       create a new cart item.
    */

    if(cartCount >= MAX_CART)
    {
        printf("Cart is full.\n");
        return 0;
    }

    cart[cartCount].foodId =
        foods[position].id;

    strcpy(cart[cartCount].foodName,
           foods[position].name);

    cart[cartCount].price =
        foods[position].price;

    cart[cartCount].quantity =
        quantity;

    cart[cartCount].subtotal =
        foods[position].price * quantity;


    /*
       IMPORTANT:
       Reduce stock immediately after
       adding food to cart.
    */

    foods[position].stock =
        foods[position].stock - quantity;

    cartCount++;

    printf("\nFood added to cart successfully.\n");

    printf("Remaining stock: %d\n",
           foods[position].stock);

    return 1;
}

/*
    Calculate Total
*/

double calculate_total()
{
    int i;
    double total;

    total = 0;

    for(i = 0; i < cartCount; i++)
    {
        total = total + cart[i].subtotal;
    }

    return total;
}



