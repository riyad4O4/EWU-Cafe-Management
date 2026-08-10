#include<stdio.h>
#include<string.h>
#include "Account.h"

struct Account
{
    char id[20];
    char email[40];
    char phone[15];  
    char password[15];
    char type[10];
};

int create_account()
{
struct Account user;  //Stores new user's information
struct Account temp;  //Temporary stores existing account information
FILE *fp;
fp=fopen("accounts.txt", "a+");  //Open accounts.txt in append and reads
if(fp==NULL)  //Check if the files could not be opened
{
    printf("File Error!\n");
    return 0;
}
printf("\n----CREATE ACCOUNT----\n");
printf("Enter Student ID/Faculty ID");
//Take input
scanf("%s", user.id);
rewind(fp); //Check if ID already registered
while(fscanf(fp, "%s %s %s %s", temp.id, temp.email, temp.phone, temp.password)!= EOF) //Read registered accounts from the file
{
    if(strcmp(user.id, temp.id)== 0)  //Compare entered ID with registered ones
    {
        printf("This ID already exists!\n");
            fclose(fp);  //Close the file
            return 0;
    }
}

printf("\n 1. Student\n");
printf("2. Faculty\n");

int choice;

printf("Enter Account Type: ");
scanf("%d", &choice);

if(choice == 1)
{
    strcpy(user.type, "student");
}
else if(choice == 2)
{
    strcpy(user.type, "faculty");
}
else
{
    printf("Account Type Invalid! Please Try Again!");
    fclose(fp);
    return 0;
}
    printf("Enter Email: ");
    scanf("%s", user.email);

    printf("Enter Phone Number: ");
    scanf("%s", user.phone);

int valid;  //Asking for a valid password

    do
    {
        printf("Create Password: ");
        scanf("%s", user.password);

        valid = valid_password(user.password);

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

    fprintf(fp, "%s %s %s %s \n",
            user.id,
            user.email,
            user.phone,
            user.password);  //Save new account's information into the file

    fclose(fp);  //Close the file

    printf("\n Account Created Successfully! \n");
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
struct Account user;

    char id[20];
    char password[15];

    int found = 0;  //Checks whether login information is correct

    FILE *fp;

    fp = fopen("accounts.txt", "r");  //Open and reads accounts file

    if(fp == NULL)  //Checks if the file exists
    {
        printf("No Account Found!\n");
        return;
    }

    printf("\n~~~~~ LOGIN ~~~~~\n");

    printf("Student ID: ");
    scanf("%s", id);

    printf("Password: ");
    scanf("%s", password);

    while(fscanf(fp, "%s %s %s %s \n",
                 user.id,
                 user.email,
                 user.phone,
                 user.password) != EOF) //Reads each and every from the accounts file
    {
        if(strcmp(id, user.id) == 0 &&
           strcmp(password, user.password) == 0)  //Compares entered ID and password with stored infos
        {
            found = 1;  //Login info is correct
            break;  //Stop searching
        }
    }

    fclose(fp);

    if(found == 1)  //Display login result
    {
        printf("\nLogin Successful!\n");
        return 1;
    }
    else
    {
        printf("\nWrong Student ID or Password!\n");
        return 0;
    }
}
//Function to change user's password
int change_password()
{
    struct Account user;

    char id[20];
    char oldpass[15];
    char newpass[15];

    int found = 0;  //Checks whecther the accound was found
    int valid;

    FILE *fp;
    FILE *temp;

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
printf("\n CHANGE PASSWORD: \n");

    printf("Student ID: ");
    scanf("%s", id);

    printf("Old Password: ");
    scanf("%s", oldpass);

//Keep asking for a new password until it is valid
    do
    {
        printf("New Password: ");
        scanf("%s", newpass);

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
while(fscanf(fp, "%s %s %s %s \n",
                 user.id,
                 user.email,
                 user.phone,
                 user.password) != EOF)  //Reads all account from the original file
    {
        if(strcmp(id, user.id) == 0 &&
           strcmp(oldpass, user.password) == 0)  //Checks whether it's the same account who's password should be changed
        {
            fprintf(temp, "%s %s %s %s\n",
                    user.id,
                    user.email,
                    user.phone,
                    newpass);  //Register the account with new password

            found = 1;
        }
        else
        {
            fprintf(temp, "%s %s %s %s\n",
                    user.id,
                    user.email,
                    user.phone,
                    user.password);  //Copy other accounts without changing them
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
        return 1;
    }
    else
    {
        printf("\nWrong Student ID or Password!\n");
        return 0;
    }
}

int log_out()  //Function to log out
{
printf("\n Logged out successfully! \n");
return 1;
}

int admin_login()  //Funtion for admin login
{
    char password[15];
    printf("\n ADMIN LOGIN \n");

    printf("Password: ");
    scanf("%s", password);

    if(strcmp(password, "1234") == 0)  //Checks if the given password is correct
    {
        printf("\n Admin Login Successful! \n");
        return 1;
    }
    else
    {
        printf("\n Wrong Password! \n");
        return 0;
    }
}