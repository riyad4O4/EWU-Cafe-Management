#include <stdio.h>
#include "payment.h"

int cash_payment(float total_bill) // takes total bill
{
    int cash;
    printf("\nCASH : ");
    scanf("%f", &cash);                       // takes customers cash amount
    printf("Change %f\n", cash - total_bill); // calculates change
    printf("Order Paid Successfully\n");
    return 0;
}
int card_payment(float total_bill)// takes total bill
{
    int temp, amount;
    printf("Total Bill %f\n", total_bill);
    printf("Enter amount to pay : \n");
    scanf("%f", &amount);
    while (1) // infinite loop until payments success
    {

        if (amount == total_bill)
        {
            printf("Enter Pin : \n");
            scanf("%f", &temp);
            printf("Order Paid Successfully\n");
            break;//after payment successful it breaks the loop otherwise loop will be infinite
        }
        else
        {
            printf("Payment Failed !!!\n");
            printf("Invalid amount \n");
        }
    }

    return 0;
}//will add feature like maximum 3 tries than cancel the order 
int discount(float total_bill)// takes total bill
{
    if (total_bill > 1000)//if bill is greater than 1000 added 5% discount
    {
        total_bill = total_bill - (total_bill * 0.05);//5% discount added
        printf("\nPrice after 5\% discount = %f\n", total_bill);
    }

    return 0;
}
int monthly_sales()
{
}
int daily_sales()
{
}