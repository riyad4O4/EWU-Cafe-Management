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
