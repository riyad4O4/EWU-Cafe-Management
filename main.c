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

    if (choice == 1)
    {
        printf("1.Register/n");
        printf("2.Log in");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice==1)
        {
            //create_account();
        }
        else if (choice==2)
        {
            //log_in();
        }
        
    }
    else if (choice == 2)
    {
    }
    else if (choice == 3)
    {
    }
    else if (choice == 4)
    {
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }

    return main();
}