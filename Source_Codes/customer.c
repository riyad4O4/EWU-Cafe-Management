
#include <stdio.h>
#include <string.h>
#include "customer.h"                                // stident ID: 2026-2-60-024

 struct Food food[MAX_FOOD];
struct Cart cart[MAX_CART];

int foodCount = 0;
int cartCount = 0;


/* LOAD FOOD FROM FILE */

int loadFood()
{
    FILE *file;  // load food from file using file pointer

    file = fopen("food.txt", "r");

    if(file == NULL)
    {
        printf("\nFood file not found!\n");
        return 0;
    }

    foodCount = 0;

    while(fscanf(file, "%d %s %f %d", // fscanf reads formatted input from the file and stores it in the food array
                 &food[foodCount].id,
                 food[foodCount].name,
                 &food[foodCount].price,
                 &food[foodCount].quantity) == 4)
    {
        foodCount++;

        if(foodCount >= MAX_FOOD)
        {
            break;
        }
    }

    fclose(file); // fclose closes the file after reading

    return 1;
}


/*  SAVE FOOD TO FILE  */

int saveFood()
{
    FILE *file;
    int i;

    file = fopen("food.txt", "w");

    if(file == NULL)
    {
        printf("\nCould not save food information.\n");
        return 0;
    }

    for(i = 0; i < foodCount; i++)
    {
        fprintf(file, "%d %s %.2f %d\n",
                food[i].id,
                food[i].name,
                food[i].price,
                food[i].quantity);
    }

    fclose(file);

    return 1;
}


/*  VIEW MENU  */

int viewMenu()
{
    int i;

    if(foodCount == 0)
    {
        printf("\nNo food available.\n");
        return 0;
    }

    printf("\n");
    printf("============================================================\n");
    printf("                     CAFE FOOD MENU\n");
    printf("============================================================\n");

    printf("ID\tFood\t\tPrice\t\tAvailable\n");

    printf("------------------------------------------------------------\n");

    for(i = 0; i < foodCount; i++)
    {
        printf("%d\t%-12s\t%.2f Tk\t%d\n",
               food[i].id,
               food[i].name,
               food[i].price,
               food[i].quantity);
    }

    printf("============================================================\n");

    return 1;
}


/*  SEARCH FOOD  */

int searchFood()
{
    char searchName[30];
    int i;
    int found = 0;

    printf("\nEnter food name to search: ");
    scanf("%s", searchName);

    for(i = 0; i < foodCount; i++)
    {
        if(strcmp(food[i].name, searchName) == 0)
        {
            printf("\nFood Found!\n");
            printf("-----------------------------\n");

            printf("ID          : %d\n", food[i].id);
            printf("Name        : %s\n", food[i].name);
            printf("Price       : %.2f Tk\n", food[i].price);
            printf("Availability: %d\n", food[i].quantity);

            printf("-----------------------------\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nFood not found.\n");
    }

    return found;
}


/* SELECT FOOD  */

int selectFood()
{
    int id;
    int quantity;
    int i;
    int position = -1;

    viewMenu();

    printf("\nEnter Food ID: ");
    scanf("%d", &id);

    /* Find food */

    for(i = 0; i < foodCount; i++)
    {
        if(food[i].id == id)
        {
            position = i;
            break;
        }
    }

    if(position == -1)
    {
        printf("\nInvalid Food ID.\n");
        return 0;
    }

    printf("\nSelected Food : %s\n", food[position].name);
    printf("Price         : %.2f Tk\n", food[position].price);
    printf("Available     : %d\n", food[position].quantity);

    if(food[position].quantity <= 0)
    {
        printf("\nSorry! This food is not available.\n");
        return 0;
    }

    printf("\nEnter Quantity: ");
    scanf("%d", &quantity);

    if(quantity <= 0)
    {
        printf("\nInvalid quantity.\n");
        return 0;
    }

    if(quantity > food[position].quantity)
    {
        printf("\nSorry! Only %d item(s) are available.\n",
               food[position].quantity);

        return 0;
    }

    /* Add item to cart */

    cart[cartCount].id = food[position].id;

    strcpy(cart[cartCount].name,
           food[position].name);

    cart[cartCount].price =
        food[position].price;

    cart[cartCount].quantity =
        quantity;

    cart[cartCount].subtotal =
        food[position].price * quantity;

    cartCount++;

    /* Update available quantity */

    food[position].quantity =
        food[position].quantity - quantity;

    saveFood();

    printf("\nFood added to cart successfully!\n");

    printf("Item ID       : %d\n", food[position].id);
    printf("Item Name     : %s\n", food[position].name);
    printf("Price         : %.2f Tk\n", food[position].price);
    printf("Quantity      : %d\n", quantity);
    printf("Remaining     : %d\n", food[position].quantity);

    return 1;
}


/* ADD MORE FOOD  */

int addToCart()
{
    int choice;

    while(1)
    {
        printf("\n====================================\n");
        printf("             ADD FOOD\n");
        printf("====================================\n");

        if(selectFood() == 0)
        {
            printf("\nFood was not added.\n");
        }

        printf("\nDo you want to add another item?\n");
        printf("1. Yes\n");
        printf("2. No\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 2)
        {
            break;
        }

        if(choice != 1)
        {
            printf("\nInvalid choice.\n");
            break;
        }
    }

    return 1;
}


/*  VIEW CART  */

int viewCart()
{
    int i;
    float total = 0;

    if(cartCount == 0)
    {
        printf("\nYour cart is empty.\n");
        return 0;
    }

    printf("\n");
    printf("============================================================\n");
    printf("                       YOUR CART\n");
    printf("============================================================\n");

    printf("ID\tFood\t\tPrice\tQty\tSubtotal\n");

    printf("------------------------------------------------------------\n");

    for(i = 0; i < cartCount; i++)
    {
        printf("%d\t%-12s\t%.2f\t%d\t%.2f\n",
               cart[i].id,
               cart[i].name,
               cart[i].price,
               cart[i].quantity,
               cart[i].subtotal);

        total = total + cart[i].subtotal;
    }

    printf("------------------------------------------------------------\n");

    printf("Total : %.2f Tk\n", total);

    printf("============================================================\n");

    return 1;
}


/*  REMOVE ITEM  */

int removeItem()
{
    int id;
    int i;
    int j;
    int found = -1;
    int quantityBack;

    if(cartCount == 0)
    {
        printf("\nYour cart is empty.\n");
        return 0;
    }

    viewCart();

    printf("\nEnter Food ID to remove: ");
    scanf("%d", &id);

    /* Find item in cart */

    for(i = 0; i < cartCount; i++)
    {
        if(cart[i].id == id)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("\nThis item is not in your cart.\n");
        return 0;
    }

    quantityBack = cart[found].quantity;

    /* Return quantity to food stock */

    for(i = 0; i < foodCount; i++)
    {
        if(food[i].id == id)
        {
            food[i].quantity =
                food[i].quantity + quantityBack;

            break;
        }
    }

    /* Remove item from cart */

    for(j = found; j < cartCount - 1; j++)
    {
        cart[j] = cart[j + 1];
    }

    cartCount--;

    saveFood();

    printf("\nItem removed successfully.\n");
    printf("Returned Quantity : %d\n", quantityBack);

    return 1;
}


/*  GENERATE BILL  */

int generateBill()
{
    int i;
    float total = 0;

    if(cartCount == 0)
    {
        printf("\nYour cart is empty.\n");
        return 0;
    }

    printf("\n");
    printf("============================================================\n");
    printf("                    WELCOME TO THE CAFE\n");
    printf("============================================================\n");

    printf("                     FINAL BILL\n");

    printf("------------------------------------------------------------\n");

    printf("ID\tFood\t\tQty\tPrice\tSubtotal\n");

    printf("------------------------------------------------------------\n");

    for(i = 0; i < cartCount; i++)
    {
        printf("%d\t%-12s\t%d\t%.2f\t%.2f\n",
               cart[i].id,
               cart[i].name,
               cart[i].quantity,
               cart[i].price,
               cart[i].subtotal);

        total = total + cart[i].subtotal;
    }

    printf("------------------------------------------------------------\n");

    printf("Total Amount : %.2f Tk\n", total);

    printf("============================================================\n");
    printf("              THANK YOU FOR VISITING!\n");
    printf("============================================================\n");

    return 1;
}


/*  CUSTOMER MENU  */

int customerMenu()
{
        int choice;

    loadFood();

    while(1)
    {
        printf("\n");
        printf("============================================\n");
        printf("           WELCOME TO THE CAFE\n");
        printf("============================================\n");

        printf("1. View Menu\n");
        printf("2. Search Food\n");
        printf("3. Select Food\n");
        printf("4. Add More Items\n");
        printf("5. View Cart\n");
        printf("6. Remove Item\n");
        printf("7. Generate Bill\n");
        printf("8. Exit\n");

        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                viewMenu();
                break;

            case 2:
                searchFood();
                break;

            case 3:
                selectFood();
                break;

            case 4:
                addToCart();
                break;

            case 5:
                viewCart();
                break;

            case 6:
                removeItem();
                break;

            case 7:
                generateBill();
                break;

            case 8:
                printf("\nThank you for visiting the cafe.\n");
                return 1;

            default:
                printf("\nInvalid choice.\n");
        }
    }

    return 0;
}
