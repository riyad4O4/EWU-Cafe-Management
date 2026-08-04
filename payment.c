#include <stdio.h>
#include "payment.h"

int cash_payment(float total_bill)
{
    int cash;
    printf("\nCASH : ");
    scanf("%d",&cash );
    printf("Change %d",cash-total_bill);
    printf("Order Paid Successfully");
}
int card_payment(float toal_bill)
{
    printf("Total Bill %d",toal_bill);
    printf("Enter Pin : ");
    printf("Enter amount to pay : ");
    printf("Order Paid Successfully");
}
int discount(float total_price)
{
    if (total_price>1000)
    {
        total_price=total_price-(total_price*0.05);
        printf("Price after 5\% discount = %d",total_price);
    }
    
}
int monthly_sales()
{
    
}
int daily_sales()
{

}