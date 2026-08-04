#include <stdio.h>
#include "payment.h"

int cash_payment(int a)
{

}
int card_payment()
{

}
int discount(int total_price)
{
    if (total_price>1000)
    {
        total_price=total_price-(total_price*0.05);
    }
    else if (total_price>2000)
    {
       total_price=total_price-(total_price*0.1);
    }
    
    
}
int monthly_sales()
{

}
int daily_sales()
{

}