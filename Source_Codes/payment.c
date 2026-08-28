// ID: 2026-2-60-094
#include <stdio.h>
#include "payment.h"
#include "sales.h"

int cash_payment(float total_bill) // takes total bill
{
    
    float cash;
    printf("\nCASH : ");
    scanf("%f", &cash); // takes customers cash amount
    if (cash < total_bill)
    {
        printf("Insufficient cash\n");
        return cash_payment(total_bill); // if customer pays less than total bill it starts again
    }
    printf("Change %f\n", cash - total_bill); // calculates change
    printf("Order Paid Successfully\n");
    record_sale(total_bill);
    return 0;
}
int card_payment(float total_bill) // takes total bill
{
    float temp, amount;
    int count = 0;
    while (1) // infinite loop until payments success
    {
        printf("Total Bill %f\n", total_bill);
        printf("Enter amount to pay : \n");
        scanf("%f", &amount);

        if (amount == total_bill)
        {
            printf("Enter Pin : \n");
            scanf("%f", &temp); // sudo pin input
            printf("Order Paid Successfully\n");
            record_sale(total_bill);
            return 0;
        }
        else
        {
            printf("Payment Failed !!!\n");
            printf("Invalid amount \n");
            count++;
        }

        if (count == 3)
        {
            printf("Order cancelled\n");
            printf("Pay Via Cash\n");
            cash_payment(total_bill);
            break;
        }
    }
    return 0;
}