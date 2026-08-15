
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

// fscanf used to read data from file
   /* while (fscanf(fp, "%d %s %lf %d",
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
}*/
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


/*--------------------------------------------------
    Display Available Foods
    Return:
    1 = Successfully displayed
    0 = No food available
--------------------------------------------------
int display_foods()
{
    int i;

    if (foodCount == 0)
    {
        printf("No food available.\n");
        return 0;
    }
*/
// fixed bug and edited from here .
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

