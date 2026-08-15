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
