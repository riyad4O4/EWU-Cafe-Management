//ID No.: 2026-2-60-004
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Account.h"

struct Account
{
    char *id;
    char *email;
    char *phone;  
    char *password;
    char *type;
};

int create_account()
{
    struct Account *user;  //Stores new user's information
    struct Account *temp;  //Temporary stores existing account information
    int valid;

    FILE *fp;

    //Allocate Account
    user = malloc(sizeof(struct Account));
    temp = malloc(sizeof(struct Account));

    if (user == NULL || temp == NULL)
    {
        printf("Memory Error!\n");
        free(user);
        free(temp);
        return 0;
    }

    //Allocate strings
    user->id = malloc(20);
    user->email = malloc(40);
    user->phone = malloc(15);
    user->password = malloc(15);
    user->type = malloc(10);

    temp->id = malloc(20);
    temp->email = malloc(40);
    temp->phone = malloc(15);
    temp->password = malloc(15);
    temp->type = malloc(10);

    fp=fopen("accounts.txt", "a+");  //Open accounts.txt in append and reads

    if(fp==NULL)  //Check if the files could not be opened
    {
        printf("\nError! Cannot be opened.\n");
        free(user->id);
        free(user->email);
        free(user->phone);
        free(user->password);
        free(user->type);

        free(temp->id);
        free(temp->email);
        free(temp->phone);
        free(temp->password);
        free(temp->type);

        free(user);
        free(temp);
        return 0;
    }

printf("\n==================================================\n");
printf("                 CREATE ACCOUNT\n");
printf("==================================================\n");

printf("Enter Student ID/Faculty ID: ");
//Take input
fgets(user->id, 20, stdin);
user->id[strcspn(user->id, "\n")] = '\0'; // To remove a newline

rewind(fp); //Check if ID already registered

//Reads the registered accounts from the file
while (fgets(temp->id, 20, fp) != NULL)
{
        fgets(temp->email, 40, fp);
        fgets(temp->phone, 15, fp);
        fgets(temp->password, 15, fp);
        fgets(temp->type, 10, fp);

        temp->id[strcspn(temp->id, "\n")] = '\0';

        if (strcmp(user->id, temp->id) == 0)  //Compare entered ID with registered ones
    {
            printf("This ID already exists!\n");
            fclose(fp);  //Close the file

            free(user->id);
            free(user->email);
            free(user->phone);
            free(user->password);
            free(user->type);

            free(temp->id);
            free(temp->email);
            free(temp->phone);
            free(temp->password);
            free(temp->type);

            free(user);
            free(temp);
            return 0;
    }
}

//Select account type
printf("\nAccount Type\n");
    printf("------------\n");
    printf("  1. Student\n");
    printf("  2. Faculty\n");

    char *choice;
    choice = malloc(3);

    printf("Enter choice: ");
    fgets(choice, 3, stdin);

    if (choice[0] == '1')
    {
        strcpy(user->type, "student");
    }
        
    else if (choice[0] == '2')
    {
        strcpy(user->type, "faculty");
    }
        
    else
    {
        printf("\nInvalid account type.\n");
        free(choice);
        fclose(fp);
        return 0;
    }

    printf("Enter Email: ");
    fgets(user->email, 40, stdin);
    user->email[strcspn(user->email, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(user->phone, 15, stdin);
    user->phone[strcspn(user->phone, "\n")] = '\0';

    printf("Password Requirements:\n");  //Showing password requirements while asking the user to create a valid password
    printf("~ At least 8 characters\n");
    printf("~ One uppercase letter\n");
    printf("~ One lowercase letter\n");
    printf("~ One number\n");
    printf("~ One special character\n\n");

    do
    {
        printf("Create Password: ");
        fgets(user->password, 15, stdin);
        user->password[strcspn(user->password, "\n")] = '\0';

        valid = valid_password(user->password);

        if(valid == 0)  //If password is invalid, show the imposed requirements
        {
            printf("\n Invalid Password! Try Again \n");
            printf("Password must contain:- At least 8 characters\n");
            printf("~ One uppercase letter\n");
            printf("~ One lowercase letter\n");
            printf("~ One number\n");
            printf("~ One special character\n\n");
        }

    } while(valid == 0);

    fprintf(fp, "%s\n", user->id);
    fprintf(fp, "%s\n", user->email);
    fprintf(fp, "%s\n", user->phone);
    fprintf(fp, "%s\n", user->password);
    fprintf(fp, "%s\n", user->type); //Save new account's information into the file

    fclose(fp);  //Close the file

    printf("Account Created Successfully! \n");
    //Free memory
    free(user->id);
    free(user->email);
    free(user->phone);
    free(user->password);
    free(user->type);

    free(temp->id);
    free(temp->email);
    free(temp->phone);
    free(temp->password);
    free(temp->type);

    free(user);
    free(temp); 
    return 1;
}

int valid_password(char password[]) //Function to check the validity of password
{
    //Flags to check imposed reqirements for password
    int upper = 0;
    int lower = 0;
    int number = 0;
    int special = 0;

    if(strlen(password) < 8)  //The length of the password which should be constructed with at least 8 characters
    {
        return 0;
    }
//Check each character of the password
    for(int i = 0; password[i] != '\0'; i++)
    {
        if(password[i] >= 'A' && password[i] <= 'Z')
        {
            upper = 1;
        }
        else if(password[i] >= 'a' && password[i] <= 'z')
        {
            lower = 1;
        }
        else if(password[i] >= '0' && password[i] <= '9')
        {
            number = 1;
        }
        else
        {
            special = 1;
        }
    }

    if(upper == 1 && lower == 1 && number == 1 && special == 1)
    {
        return 1; //Password fulfills given requirements
    }

    return 0; //Password is invalid
}

int log_in()  //Function for user login
{
struct Account *user = malloc(sizeof(struct Account));

char *id = malloc(20);
char *password = malloc(15);

int found = 0;
FILE *fp;

if (user == NULL || id == NULL || password == NULL)
{
    printf("Memory allocation failed!\n");
    return 0;
}

user->id = malloc(20);
user->email = malloc(40);
user->phone = malloc(15);
user->password = malloc(15);
user->type = malloc(10);

if (user->id == NULL || user->email == NULL ||
    user->phone == NULL || user->password == NULL ||
    user->type == NULL)
{
    printf("Memory allocation failed!\n");
    return 0;
}

fp = fopen("accounts.txt", "r");

if (fp == NULL)
{
    printf("No Account Found!\n");
    return 0;
}

printf("\n==================================================\n");
printf("                     LOGIN\n");
printf("==================================================\n");

printf("Student/Faculty ID: ");
fgets(id, 20, stdin);
id[strcspn(id, "\n")] = '\0';

printf("Password: ");
fgets(password, 15, stdin);
password[strcspn(password, "\n")] = '\0';

while (fgets(user->id, 20, fp) != NULL)
{
    fgets(user->email, 40, fp);
    fgets(user->phone, 15, fp);
    fgets(user->password, 15, fp);
    fgets(user->type, 10, fp);

    user->id[strcspn(user->id, "\n")] = '\0';
    user->email[strcspn(user->email, "\n")] = '\0';
    user->phone[strcspn(user->phone, "\n")] = '\0';
    user->password[strcspn(user->password, "\n")] = '\0';
    user->type[strcspn(user->type, "\n")] = '\0';

    if (strcmp(id, user->id) == 0 &&
        strcmp(password, user->password) == 0)
    {
        found = 1;
        break;
    }
}

fclose(fp);

if (found == 1)
{
    printf("\nLogin Successful!\n");
}
else
{
    printf("\nWrong Student ID or Password!\n");
}

/* Free memory */
free(id);
free(password);

free(user->id);
free(user->email);
free(user->phone);
free(user->password);
free(user->type);

free(user);

return found;
}

//Function to change user's password
int change_password()
{
    struct Account *user;

    char *id;
    char *oldpass;
    char *newpass;

    int found = 0;  //Checks whecther the accound was found
    int valid;

    FILE *fp;
    FILE *temp;

    // Allocate memory
    user = malloc(sizeof(struct Account));

    id = malloc(20);
    oldpass = malloc(15);
    newpass = malloc(15);

    if(user == NULL || id == NULL || oldpass == NULL || newpass == NULL)
{
    printf("Memory allocation failed!\n");

    free(user);
    free(id);
    free(oldpass);
    free(newpass);

    return 0;
}

    user->id = malloc(20);
    user->email = malloc(40);
    user->phone = malloc(15);
    user->password = malloc(15);
    user->type = malloc(10);

    // Check memory allocation
    if(user == NULL || id == NULL || oldpass == NULL || newpass == NULL ||
       user->id == NULL || user->email == NULL || user->phone == NULL ||
       user->password == NULL || user->type == NULL)
    {
        printf("Memory allocation failed!\n");
        return 0;
    }

    fp = fopen("accounts.txt", "r");  //Open the original account file

    if(fp == NULL)  //Checks if the file not exists
    {
        printf("No Account Found!\n");
        return 0;
    }

    temp = fopen("temp.txt", "w");  //Create a temporary file

    if(temp == NULL) //Checks if the temporary file could not be created
    {
        printf("File Error!\n");
        fclose(fp);
        return 0;
}
printf("\n==================================================\n");
printf("                 CHANGE PASSWORD\n");
printf("==================================================\n");

    printf("Student/Faculty ID: ");
    fgets(id, 20, stdin);
    id[strcspn(id, "\n")] = '\0';

    printf("Old Password: ");
    fgets(oldpass, 15, stdin);
    oldpass[strcspn(oldpass, "\n")] = '\0';

    //Showing the requirements for a valid password
        printf("Password must contain:- At least 8 characters\n");
        printf("~ One uppercase letter\n");
        printf("~ One lowercase letter\n");
        printf("~ One number\n");
        printf("~ One special character\n\n");

//Keep asking for a new password until it is valid
    do
    {
        printf("New Password: ");
        fgets(newpass, 15, stdin);
        newpass[strcspn(newpass, "\n")] = '\0';

        if(strcmp(oldpass, newpass) == 0) //New password and old password cannot be same
        {
            printf("New password cannot be the same as old password.\n");
            valid = 0;
        }
        else
        {
            valid = valid_password(newpass);  //Check whether the new password fulfills requirement

            if(valid == 0)
            {
                printf("Invalid Password! Try Again.\n");
                printf("Use at least 8 characters with uppercase, lowercase, number and special character.\n");
            }
        }

    } 
    while(valid == 0);
while(fgets(user->id, 20, fp) != NULL)
    {
        fgets(user->email, 40, fp);
        fgets(user->phone, 15, fp);
        fgets(user->password, 15, fp);
        fgets(user->type, 10, fp);  //Reads all account from the original file

        user->id[strcspn(user->id, "\n")] = '\0';
        user->email[strcspn(user->email, "\n")] = '\0';
        user->phone[strcspn(user->phone, "\n")] = '\0';
        user->password[strcspn(user->password, "\n")] = '\0';
        user->type[strcspn(user->type, "\n")] = '\0';
    
        if(strcmp(id, user->id) == 0 &&
           strcmp(oldpass, user->password) == 0)  //Checks whether it's the same account who's password should be changed
        {
            fprintf(temp, "%s\n", user->id);
            fprintf(temp, "%s\n", user->email);
            fprintf(temp, "%s\n", user->phone);
            fprintf(temp, "%s\n", newpass);
            fprintf(temp, "%s\n", user->type); //Register the account with new password

            found = 1;
        }
        else
        {
            fprintf(temp, "%s\n", user->id);
            fprintf(temp, "%s\n", user->email);
            fprintf(temp, "%s\n", user->phone);
            fprintf(temp, "%s\n", user->password);
            fprintf(temp, "%s\n", user->type);  //Copy other accounts without changing them
        }
    }

    //Close both files
    fclose(fp);
    fclose(temp);

    remove("accounts.txt");  //Delete the old accounts file
    rename("temp.txt", "accounts.txt");  //Rename the temporary file as accounts.txt

    if(found == 1)  //Display the result
    {
        printf("\nPassword Changed Successfully!\n");
    }
    else
    {
        printf("\nWrong ID or Password!\n");
    }
        free(id);
        free(oldpass);
        free(newpass);

        free(user->id);
        free(user->email);
        free(user->phone);
        free(user->password);
        free(user->type);

        free(user);
        return found;
    
}

int log_out()  //Function to log out
{
printf("\n Logged out successfully! \n");
return 1;
}

int admin_login()  //Funtion for admin login
{
    char *password;
    password = malloc(15);
    printf("\n==================================================\n");
    printf("                   ADMIN LOGIN\n");
    printf("==================================================\n");

    printf("Password: ");
    fgets(password, 15, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    if(strcmp(password, "1234") == 0)  //Checks if the given password is correct
    {
        printf("\n Admin Login Successful! \n");
        free(password);
        return 1;
    }
    else
    {
        printf("\n Wrong Password! \n");
        free(password);
        return 0;
    
    }
        
}