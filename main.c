#include <stdio.h>
#include "main_menu.h"

int main()
{

    int choice;
    printf("Main Menu:\n");
    printf("1. Faculty\n");
    printf("2. Student\n");
    printf("3. Admin\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Faculty

    if (choice == 1) 
    {
        printf("1.Register\n");
        printf("2.Log in");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            log_in();
            printf("1. View Menu");
            printf("2. Search food");
            printf("3. View profile");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                view_FoodList();
            }
            else if (choice == 2)
            {
                search_food();
            }
            else if (choice == 3)
            {
                view_profile();
            }

        }
    }

    // Student

    else if (choice == 2) 
    {
        printf("1.Register\n");
        printf("2.Log in");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            log_in();
            printf("1. View Menu");
            printf("2. Search food");
            printf("3. View profile");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                view_FoodList();
            }
            else if (choice == 2)
            {
                search_food();
            }
            else if (choice == 3)
            {
                view_profile();
            }
        }
    }

    // Admin

    else if (choice == 3) 
    {
        printf("1.Register\n");
        printf("2.Log in");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1)
        {
            create_account();
        }
        else if (choice == 2)
        {
            log_in();
            printf("1. Edit Food");
            printf("2. view customer list");
            printf("3. View all orders");
            printf("4. View sales report");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice == 1)
            {
                edit_food();
                
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
        printf("Exiting the program.\n");
        return 0;
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }


    return main();
}
