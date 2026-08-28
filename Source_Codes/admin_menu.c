#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin_menu.h"

#define MAX_FOOD 100
#define FILE_NAME "Database/food.txt"

typedef struct
{
    int id;
    char name[50];
    float price;
    int quantity;
} Food;

Food foods[MAX_FOOD];
int foodCount = 0;

/* Helper Declarations */
int preloadDefaultFoods(void);
int findFoodIndex(int id);
int saveToFile(void);
int loadFromFile(void);


/* ================= FIND FOOD ================= */

int findFoodIndex(int id)
{
    for (int i = 0; i < foodCount; i++)
    {
        if (foods[i].id == id)
        {
            return i;
        }
    }

    return -1;
}


/* ================= SAVE FOOD DATA ================= */

int saveToFile()
{
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL)
    {
        printf("\n[Error] Could not save food data!\n");
        return 0;
    }

    for (int i = 0; i < foodCount; i++)
    {
        fprintf(fp, "%d,%s,%.2f,%d\n",
                foods[i].id,
                foods[i].name,
                foods[i].price,
                foods[i].quantity);
    }

    fclose(fp);

    return 1;
}


/* ================= DEFAULT FOOD LIST ================= */

int preloadDefaultFoods()
{
    Food defaultItems[] =
    {
        {1, "Chicken Burger", 250, 20},
        {2, "Beef Burger", 300, 15},
        {3, "Cheese Burger", 280, 15},
        {4, "Chicken Pizza", 450, 10},
        {5, "Beef Pizza", 500, 10},
        {6, "French Fries", 150, 30},
        {7, "Lemonade", 100, 25},
        {8, "Milkshake", 200, 20},
        {9, "Chocolate Shake", 220, 15},
        {10, "Coffee", 120, 40},
        {11, "Tea", 80, 50}
    };

    foodCount = 11;

    for (int i = 0; i < foodCount; i++)
    {
        foods[i] = defaultItems[i];
    }

    return 1;
}


/* ================= LOAD FOOD DATA ================= */

int loadFromFile()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        /* If file doesn't exist, load the 11 default foods */
        preloadDefaultFoods();
        saveToFile();

        return 0;
    }

    foodCount = 0;

    while (foodCount < MAX_FOOD &&
           fscanf(fp, "%d,%49[^,],%f,%d",
                  &foods[foodCount].id,
                  foods[foodCount].name,
                  &foods[foodCount].price,
                  &foods[foodCount].quantity) == 4)
    {
        foodCount++;
    }

    fclose(fp);

    return 1;
}


/* ================= ADD FOOD ================= */

int add_Food()
{
    system("cls");

    if (foodCount >= MAX_FOOD)
    {
        printf("\n[Error] Food list is full!\n");
        return 0;
    }

    printf("\n========== ADD FOOD ==========\n");

    while (1)
    {
        printf("Enter Food ID: ");
        scanf("%d", &foods[foodCount].id);

        if (findFoodIndex(foods[foodCount].id) != -1)
        {
            printf("\nSorry, this Food ID already exists!\n");
            printf("Please enter a different Food ID.\n\n");
        }
        else
        {
            break;
        }
    }

    printf("Enter Food Name: ");
    scanf(" %[^\n]", foods[foodCount].name);

    printf("Enter Food Price: ");
    scanf("%f", &foods[foodCount].price);

    printf("Enter Food Quantity: ");
    scanf("%d", &foods[foodCount].quantity);

    foodCount++;

    saveToFile();

    printf("\nFood added successfully!\n");

    return 0;
}


/* ================= EDIT FOOD ================= */

int edit_Food()
{
    system("cls");

    int id;

    printf("\n========== EDIT FOOD ==========\n");

    printf("Enter Food ID to edit: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food with ID %d not found.\n", id);
        return 0;
    }

    printf("\nCurrent Name: %s\n", foods[index].name);
    printf("Current Price: %.2f\n", foods[index].price);

    printf("\nEnter New Name: ");
    scanf(" %[^\n]", foods[index].name);

    printf("Enter New Price: ");
    scanf("%f", &foods[index].price);

    saveToFile();

    printf("\nFood updated successfully!\n");

    return 0;
}


/* ================= DELETE FOOD ================= */

int delete_Food()
{
    system("cls");

    int id;

    printf("\n========== DELETE FOOD ==========\n");

    printf("Enter Food ID to delete: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food with ID %d not found.\n", id);
        return 0;
    }

    for (int i = index; i < foodCount - 1; i++)
    {
        foods[i] = foods[i + 1];
    }

    foodCount--;

    saveToFile();

    printf("\nFood item deleted successfully!\n");

    return 0;
}


/* ================= VIEW FOOD LIST ================= */

int view_FoodList()
{
    system("cls");

    /*
       Load the food data when View Food List is selected.
       If the file doesn't exist, the 11 default foods
       will automatically be created.
    */
    if (foodCount == 0)
    {
        loadFromFile();
    }

    printf("\n========== FOOD MENU ==========\n");

    if (foodCount == 0)
    {
        printf("No food items available.\n");
    }
    else
    {
        for (int i = 0; i < foodCount; i++)
        {
            printf("%d. %-20s Price: %.2f  Available: %d\n",
                   foods[i].id,
                   foods[i].name,
                   foods[i].price,
                   foods[i].quantity);
        }
    }

    printf("===============================\n");

    return 0;
}


/* ================= UPDATE QUANTITY ================= */

int update_Quantity()
{
    system("cls");

    int id;

    printf("\n========== UPDATE QUANTITY ==========\n");

    printf("Enter Food ID: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food with ID %d not found.\n", id);
        return 0;
    }

    printf("\nFood: %s\n", foods[index].name);
    printf("Current Quantity: %d\n", foods[index].quantity);

    printf("Enter New Quantity: ");
    scanf("%d", &foods[index].quantity);

    saveToFile();

    printf("\nQuantity updated successfully!\n");

    return 0;
}


/* ================= SEARCH FOOD ================= */

int search_Food()
{
    system("cls");

    int id;

    printf("\n========== SEARCH FOOD ==========\n");

    printf("Enter Food ID to search: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food item not found.\n");
    }
    else
    {
        printf("\n========== ITEM FOUND ==========\n");

        printf("ID: %d\n", foods[index].id);
        printf("Name: %s\n", foods[index].name);
        printf("Price: %.2f\n", foods[index].price);
        printf("Available: %d\n", foods[index].quantity);

        printf("================================\n");
    }

    return 0;
}