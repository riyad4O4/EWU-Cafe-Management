
#ifndef BILL_H
#define BILL_H

#define MAX_FOODS 100
#define MAX_CART 50

/* Food Structure */
typedef struct
{
    int id;
    char name[50];
    double price;
    int stock;
} Food;

/* Cart Structure */
typedef struct
{
    int foodId;
    char foodName[50];
    double price;
    int quantity;
    double subtotal;
} CartItem;

/* Main Functions */
int place_order();
int add_to_cart();
int generate_bill();
int print_receipt();

/* Helper Functions */
int load_foods();
int display_foods();
int find_food_by_id(int id);
double calculate_total();
int update_stock();
int save_sale_record();

/* Global Variables */
extern Food foods[MAX_FOODS];
extern int foodCount;

extern CartItem cart[MAX_CART];
extern int cartCount;

#endif

