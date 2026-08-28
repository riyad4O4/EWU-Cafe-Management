// ID: 2026-2-60-543
#include <stdio.h>
#include "main_menu.h"
#include "Account.h"
#include "admin_menu.h"
#include "customer.h"
#include "main_menu.h"

int main()
{
    int choice;

    printf("\n");
    printf("**************************************************\n");
    printf("*                  MAIN MENU                     *\n");
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*     [1]  Faculty                               *\n");
    printf("*     [2]  Student                               *\n");
    printf("*     [3]  Admin                                 *\n");
    printf("*     [4]  Exit                                  *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    

    printf(" Choice: ");
    scanf("%d", &choice);

    // Faculty

    if (choice == 1)
    {
        printf("\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*     [1]  Register                              *\n");
        printf("*     [2]  Log in                                *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            log_in();
            customerMenu();
        }
    }

    // Student

    else if (choice == 2)
    {
        printf("\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*     [1]  Register                              *\n");
        printf("*     [2]  Log in                                *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            log_in();
            customerMenu();
        }
    }

    // Admin

    else if (choice == 3)
    {
        printf("\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*     [1]  Register                              *\n");
        printf("*     [2]  Log in                                *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            admin_login();

            printf("\n");
            printf("**************************************************\n");
            printf("*                                                *\n");
            printf("*     [1]  Edit Food                             *\n");
            printf("*     [2]  View Customer List                    *\n");
            printf("*     [3]  View All Orders                       *\n");
            printf("*     [4]  View Sales Report                     *\n");
            printf("*                                                *\n");
            printf("**************************************************\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                edit_Food();
            }
            else if (choice == 2)
            {
                view_customer_list();
            }
            else if (choice == 3)
            {
                view_all_orders();
            }
            else if (choice == 4)
            {
                view_sales_report();
            }
        }
    }

    else if (choice == 4)
    {
        printf("\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*            Exiting the program.               *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");

        return 0;
    }

    else
    {
        printf("\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*       Invalid choice. Please try again.        *\n");
        printf("*                                                *\n");
        printf("**************************************************\n");
    }

    return main();
}
