#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin_menu.h"

#define MAX_FOOD 100
#define FILE_NAME "food_data.txt"
#define MAX_CUSTOMER 100
#define MAX_ORDERS 100
#define CUSTOMER_FILE "customer_data.txt"
#define ORDER_FILE "order_data.txt"

typedef struct
{
    int id;
    char name[50];
    float price;
    int quantity;
} Food;

typedef struct {
    char id[50]; /* Updated to support formatted string IDs (e.g., 2026-2-60-091) */
    char phone[30];
} Customer;

typedef struct {
    int orderId;
    char customerId[50]; /* Updated to match customer string ID */
    char foodName[50];
    int quantity;
    float totalPrice;
} Order;

static Customer customers[MAX_CUSTOMER];
static int customerCount = 0;

static Order orders[MAX_ORDERS];
static int orderCount = 0;

static Food foods[MAX_FOOD];
static int foodCount = 0;

/* Helper Declarations */
int preloadDefaultFoods(void);

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

/* Save food data to text file */
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

/* Create the original default foods */
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
    return 0;
}

/* Load food data from text file */
int loadFromFile()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        preloadDefaultFoods();
        saveToFile();
        return 0;
    }

    foodCount = 0;

    while (foodCount < MAX_FOOD &&
            fscanf(fp, "%d,%49[^,],%f,%d\n",
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

/* ================= CUSTOMER & ORDER HELPERS ================= */

/* Reads live Customer data logged in by your teammate's code */
int loadCustomersFromFile() {
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    if (fp == NULL) {
        customerCount = 0;
        return 0;
    }
    customerCount = 0;
    char line[100];

    while (customerCount < MAX_CUSTOMER && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        if (sscanf(line, "%49[^,],%29s", customers[customerCount].id, customers[customerCount].phone) == 2) {
            customerCount++;
        }
    }
    fclose(fp);
    return 1;
}

/* Reads live Order data generated when customers place orders */
int loadOrdersFromFile() {
    FILE *fp = fopen(ORDER_FILE, "r");
    if (fp == NULL) {
        orderCount = 0;
        return 0;
    }
    orderCount = 0;
    char line[150];

    while (orderCount < MAX_ORDERS && fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\r\n")] = 0;
        if (sscanf(line, "%d,%49[^,],%49[^,],%d,%f",
                   &orders[orderCount].orderId,
                   orders[orderCount].customerId,
                   orders[orderCount].foodName,
                   &orders[orderCount].quantity,
                   &orders[orderCount].totalPrice) == 5) {
            orderCount++;
        }
    }
    fclose(fp);
    return 1;
}

/* ================= ADMIN FUNCTIONS ================= */

int add_Food()
{
    system("cls");

    if (foodCount >= MAX_FOOD)
    {
        printf("\n[Error] Food list is full!\n");
        return 0;
    }

    printf("\n========== ADD FOOD ==========\n");

    printf("Enter Food ID: ");
    scanf("%d", &foods[foodCount].id);

    if (findFoodIndex(foods[foodCount].id) != -1)
    {
        printf("\n[Error] This Food ID already exists!\n");
        return 0;
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

int view_FoodList()
{
    system("cls");
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

/* Option 7: Displays Customer ID and Phone Number */
int view_customer_list()
{
    system("cls");
    loadCustomersFromFile();

    printf("\n========== CUSTOMER LIST ==========\n");

    if (customerCount == 0) {
        printf("No customers found in record.\n");
    } else {
        printf("%-22s %-15s\n", "Customer/Student ID", "Phone Number");
        printf("-------------------------------------------\n");
        for (int i = 0; i < customerCount; i++) {
            printf("%-22s %-15s\n",
                   customers[i].id,
                   customers[i].phone);
        }
    }

    printf("===========================================\n");
    return 0;
}

/* Option 8: Displays all placed orders */
int view_all_orders() {
    system("cls");
    loadOrdersFromFile();

    printf("\n=================== ALL ORDERS ===================\n");
    if (orderCount == 0) {
        printf("No order history found.\n");
    } else {
        printf("%-10s %-20s %-18s %-6s %-10s\n", "Order ID", "Customer ID", "Item", "Qty", "Total Price");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < orderCount; i++) {
            printf("%-10d %-20s %-18s %-6d %.2f\n",
                   orders[i].orderId,
                   orders[i].customerId,
                   orders[i].foodName,
                   orders[i].quantity,
                   orders[i].totalPrice);
        }
    }
    printf("==================================================\n");
    return 0;
}

/* Option 9: Calculates and displays total sales */
int view_sales_report()
{
    system("cls");
    loadOrdersFromFile();

    printf("\n========== SALES REPORT ==========\n");
    if (orderCount == 0) {
        printf("No sales data available.\n");
        printf("==================================\n");
        return 0;
    }
    int totalItemsSold = 0;
    float totalRevenue = 0.0f;
    for (int i = 0; i < orderCount; i++) {
        totalItemsSold += orders[i].quantity;
        totalRevenue += orders[i].totalPrice;
    }
    printf("Total Orders Processed : %d\n", orderCount);
    printf("Total Food Items Sold  : %d\n", totalItemsSold);
    printf("Total Revenue Generated: BDT %.2f\n", totalRevenue);
    printf("==================================\n");
    return 0;