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
    getchar();

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
            fcreate_account();
        }
        else if (choice == 2)
        {
            int a;
            a = flog_in();
            if (a == 1)
            {
                customerMenu();
            }
            else
            {
                main();
            }
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
        getchar();

        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            int a;
            a = log_in();
            if (a == 1)
            {
                customerMenu();
            }
            else
            {
                main();
            }
        }
    }

    // Admin

    else if (choice == 3)
    {
        printf("\n");

        int a;

        a = admin_login();
        if (a == 1)
        {

            printf("\n");
            printf("**************************************************\n");
            printf("*                                                *\n");
            printf("*     [1]  Add Food                              *\n");
            printf("*     [2]  Edit Food                             *\n");
            printf("*     [3]  Delete Food                           *\n");
            printf("*     [4]  View Food List                        *\n");
            printf("*     [5]  Update Quantity                       *\n");
            printf("*     [6]  Search Food                           *\n");
            printf("*     [7]  Total Revenue                         *\n");
            printf("**************************************************\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 1)
            {
                add_Food();
            }
            else if (choice == 2)
            {
                edit_Food();
            }
            else if (choice == 3)
            {
                delete_Food();
            }
            else if (choice == 4)
            {
                view_FoodList();
            }
            else if (choice == 5)
            {
                update_Quantity();
            }
            else if (choice == 6)
            {
                search_Food();
            }
            else if (choice == 7)
            {
                total_revenue();
            }
            
        }
        else
        {
            main();
        }
    }

    else if (choice == 4)
    {
        printf("\n");
        printf("**************************************************\n");
        printf("*                                                *\n");
        printf("*            Program Exited                      *\n");
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
