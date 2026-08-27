
#ifndef CUSTOMER_H                 //STUDENT ID: 2026-2-60-024
#define CUSTOMER_H

#define MAX_FOOD 50
#define MAX_CART 50

struct Food
{
    int id;
    char name[30];
    float price;
    int quantity;
};

struct Cart
{
    int id;
    char name[30];
    float price;
    int quantity;
    float subtotal;
};

int loadFood();
int saveFood();

int viewMenu();
int searchFood();
int selectFood();
int addToCart();
int viewCart();
int removeItem();
int generateBill();

int customerMenu();

#endif