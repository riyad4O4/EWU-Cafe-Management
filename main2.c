#include <stdio.h>

#include <string.h>

#define MAX_FOOD 100
#define FILE_NAME "food_data.txt"

typedef struct {
    int id;
    char name[50];
    float price;
    int quantity;
} Food;

Food foods[MAX_FOOD];
int foodCount = 0;


/* Function Declarations */
int findFoodIndex(int id);
void saveToFile();
void loadFromFile();
void preloadDefaultFoods();
void addFood();
void editFood();
void deleteFood();
void viewFood();
void updateQuantity();
void searchFood();

/* Find food by ID */
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
/* Save data to text file */
void saveToFile()
{
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL)
    {
        printf("\n[Error] Could not save food data!\n");
        return;
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
}
/* Load data from text file */
void loadFromFile()
{
    FILE *fp = fopen(FILE_NAME, "r");

    /*
       If the file does not exist,
       create the 11 default foods.
    */
    if (fp == NULL)
    {
        preloadDefaultFoods();
        saveToFile();
        return;
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
}
/* Create the original 11 foods */
void preloadDefaultFoods()
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
}
