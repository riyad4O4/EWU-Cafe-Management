#include<stdio.h>
#include "menu.h"
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

    if(choice == 1) 
    {
        account();
    } 
    else if(choice == 2) 
    {
        account();
    } 
    else if(choice == 3) 
    {
        account();
    } 
    else if(choice == 4) 
    {
        account();
    } 
    else 
    {
        printf("Invalid choice. Please try again.\n");
    }
    
    return main();
}



