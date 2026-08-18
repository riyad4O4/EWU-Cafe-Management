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
/* 1. ADD FOOD */
void addFood()
{
    if (foodCount >= MAX_FOOD)
    {
        printf("\n[Error] Food list is full!\n");
        return;
    }

    printf("\n========== ADD FOOD ==========\n");

    /* Ask for new Food ID */
    printf("Enter Food ID: ");
    scanf("%d", &foods[foodCount].id);

    /* Check if ID already exists */
    if (findFoodIndex(foods[foodCount].id) != -1)
    {
        printf("\n[Error] This Food ID already exists!\n");
        return;
    }

    /* Ask for new Food Name */
    printf("Enter Food Name: ");
    scanf(" %[^\n]", foods[foodCount].name);

    /* Ask for new Food Price */
    printf("Enter Food Price: ");
    scanf("%f", &foods[foodCount].price);

    /* Ask for new Food Quantity */
    printf("Enter Food Quantity: ");
    scanf("%d", &foods[foodCount].quantity);

    /* Increase number of foods */
    foodCount++;

    /* Save new food permanently */
    saveToFile();

    printf("\nFood added successfully!\n");
}
/* 2. EDIT FOOD */
void editFood()
{
    int id;

    printf("\n========== EDIT FOOD ==========\n");

    printf("Enter Food ID to edit: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food with ID %d not found.\n", id);
        return;
    }

    printf("\nCurrent Name: %s\n", foods[index].name);
    printf("Current Price: %.2f\n", foods[index].price);

    printf("\nEnter New Name: ");
    scanf(" %[^\n]", foods[index].name);

    printf("Enter New Price: ");
    scanf("%f", &foods[index].price);

    saveToFile();

    printf("\nFood updated successfully!\n");
}
/* 3. DELETE FOOD */
void deleteFood()
{
    int id;

    printf("\n========== DELETE FOOD ==========\n");

    printf("Enter Food ID to delete: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food with ID %d not found.\n", id);
        return;
    }

    for (int i = index; i < foodCount - 1; i++)
    {
        foods[i] = foods[i + 1];
    }

    foodCount--;

    saveToFile();

    printf("\nFood item deleted successfully!\n");
}
/* 4. VIEW FOOD LIST */
void viewFood()
{
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
}


/* 5. UPDATE QUANTITY */
void updateQuantity()
{
    int id;

    printf("\n========== UPDATE QUANTITY ==========\n");

    printf("Enter Food ID: ");
    scanf("%d", &id);

    int index = findFoodIndex(id);

    if (index == -1)
    {
        printf("\n[Error] Food with ID %d not found.\n", id);
        return;
    }

    printf("\nFood: %s\n", foods[index].name);
    printf("Current Quantity: %d\n", foods[index].quantity);

    printf("Enter New Quantity: ");
    scanf("%d", &foods[index].quantity);

    saveToFile();

    printf("\nQuantity updated successfully!\n");
}


/* 6. SEARCH FOOD */
void searchFood()
{
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
}
/* MAIN MENU */
int main()
{
    /* Load saved food data when program starts */
    loadFromFile();

    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("       TASK 3 - ADMIN MENU          \n");
        printf("====================================\n");

        printf("1. Add Food\n");
        printf("2. Edit Food\n");
        printf("3. Delete Food\n");
        printf("4. View Food List\n");
        printf("5. Update Quantity\n");
        printf("6. Search Food\n");
        printf("7. Exit\n");

        printf("Enter choice (1-7): ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addFood();
                break;

            case 2:
                editFood();
                break;

            case 3:
                deleteFood();
                break;

            case 4:
                viewFood();
                break;

            case 5:
                updateQuantity();
                break;

            case 6:
                searchFood();
                break;

            case 7:
                saveToFile();

                printf("\nExiting Admin Panel. Goodbye!\n");

                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
