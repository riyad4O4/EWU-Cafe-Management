#include <stdio.h>
#include "admin_menu.h"
#include<stdlib.h>


#include <string.h>

#define MAX_FOOD 100
#define FILE_NAME "Database/food.txt"
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
    int id;
    char name[50];
    char phone[20];
} Customer;

typedef struct {
    int orderId;
    int customerId;
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
    return 0;
}
/* Load data from text file */
int loadFromFile()
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
    return 0;
}
/* Create the original 11 foods */
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
/* ================= CUSTOMER & ORDER HELPERS ================= */

int saveCustomersToFile() {
    FILE *fp = fopen(CUSTOMER_FILE, "w");
    if (fp == NULL) return 0;
    for (int i = 0; i < customerCount; i++) {
        fprintf(fp, "%d,%s,%s\n", customers[i].id, customers[i].name, customers[i].phone);
    }
    fclose(fp);
    return 1;
}

int preloadDefaultCustomers() {
    Customer defaultCustomers[] = {
        {101, "Rahim Ahmed", "01711223344"},
        {102, "Tanvir Hasan", "01812345678"},
        {103, "Sabbir Hossain", "01911998877"}
    };
    customerCount = 3;
    for (int i = 0; i < customerCount; i++) customers[i] = defaultCustomers[i];
    return 0;
}

int loadCustomersFromFile() {
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    if (fp == NULL) {
        preloadDefaultCustomers();
        saveCustomersToFile();
        return 0;
    }
    customerCount = 0;
    while (customerCount < MAX_CUSTOMER &&
           fscanf(fp, "%d,%49[^,],%19[^\n]\n", &customers[customerCount].id, customers[customerCount].name, customers[customerCount].phone) == 3) {
        customerCount++;
    }
    fclose(fp);
    return 1;
}

int saveOrdersToFile() {
    FILE *fp = fopen(ORDER_FILE, "w");
    if (fp == NULL) return 0;
    for (int i = 0; i < orderCount; i++) {
        fprintf(fp, "%d,%d,%s,%d,%.2f\n", orders[i].orderId, orders[i].customerId, orders[i].foodName, orders[i].quantity, orders[i].totalPrice);
    }
    fclose(fp);
    return 1;
}

int preloadDefaultOrders() {
    Order defaultOrders[] = {
        {1, 101, "Chicken Burger", 2, 500.00},
        {2, 102, "Beef Pizza", 1, 500.00},
        {3, 103, "Lemonade", 2, 200.00}
    };
    orderCount = 3;
    for (int i = 0; i < orderCount; i++) orders[i] = defaultOrders[i];
    return 0;
}

int loadOrdersFromFile() {
    FILE *fp = fopen(ORDER_FILE, "r");
    if (fp == NULL) {
        preloadDefaultOrders();
        saveOrdersToFile();
        return 0;
    }
    orderCount = 0;
    while (orderCount < MAX_ORDERS &&
           fscanf(fp, "%d,%d,%49[^,],%d,%f\n", &orders[orderCount].orderId, &orders[orderCount].customerId, orders[orderCount].foodName, &orders[orderCount].quantity, &orders[orderCount].totalPrice) == 5) {
        orderCount++;
    }
    fclose(fp);
    return 1;
}

int add_Food()
{  system("cls");

    if (foodCount >= MAX_FOOD)
    {
        printf("\n[Error] Food list is full!\n");
        return 0;
    }

    printf("\n========== ADD FOOD ==========\n");

    /* Ask for new Food ID */
    printf("Enter Food ID: ");
    scanf("%d", &foods[foodCount].id);

    /* Check if ID already exists */
    if (findFoodIndex(foods[foodCount].id) != -1)
    {
        printf("\n[Error] This Food ID already exists!\n");
        return 0;
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
    return 0;
}
int edit_Food()
{   system("cls");
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
{   system("cls");
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
{   system("cls");

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


/* 6. SEARCH FOOD */

int search_Food()
{   system("cls");
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


int view_customer_list()
{

    system("cls");

    loadCustomersFromFile();

    printf("\n========== CUSTOMER LIST ==========\n");

    if (customerCount == 0) {
        printf("No customers found in record.\n");
    } else {
        printf("%-10s %-25s %-15s\n", "ID", "Name", "Phone");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < customerCount; i++) {
            printf("%-10d %-25s %-15s\n",
                   customers[i].id,
                   customers[i].name,
                   customers[i].phone);
        }
    }

    printf("===================================\n");
    return 0;

}


    int view_all_orders() {
     system("cls");

    loadOrdersFromFile();
    printf("\n=================== ALL ORDERS ===================\n");
    if (orderCount == 0) {
        printf("No order history found.\n");
    } else {
        printf("%-10s %-12s %-20s %-8s %-10s\n", "Order ID", "Customer ID", "Item", "Qty", "Total Price");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < orderCount; i++) {
            printf("%-10d %-12d %-20s %-8d %.2f\n",
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

}



