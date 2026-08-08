#include<stdio.h>
#include<string.h>
#include "Account.h"

struct Account
{
    char id[20];
    char email[40];
    char phone[15];
    char password[15];
};

int valid_password(char password[]);

void sign_up()
{
    create_account();
}

void create_account()
{
struct Account user;
struct Account temp;
FILE *fp;
fp=fopen("accounts.txt", "a+");
if(fp==NULL)
{
    printf("File Error!\n");
}
printf("\n----CREATE ACCOUNT----\n");
scanf("%s", user.id);

//Check if ID already exists
rewind(fp);
while(fscanf(fp, "%s %s %s %s", temp.id, temp.email, temp.phone, temp.password)!= EOF)
{
    if(strcmp(user.id, temp.id)== 0)
    {
        printf("This Student ID already exists!\n");
            fclose(fp);
    }
}
    printf("Enter Email: ");
    scanf("%s", user.email);

    printf("Enter Phone Number: ");
    scanf("%s", user.phone);

int valid;

    do
    {
        printf("Create Password: ");
        scanf("%s", user.password);

        valid = valid_password(user.password);

        if(valid == 0)
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
            user.password);

    fclose(fp);

    printf("\n Account Created Successfully! \n");
}
int valid_password(char password[])
{
    int upper = 0;
    int lower = 0;
    int number = 0;
    int special = 0;

    if(strlen(password) < 8)
    {
        return 0;
    }

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
        return 1;
    }

    return 0;
}

void log_in()
{
struct Account user;

    char id[20];
    char password[15];

    int found = 0;

    FILE *fp;

    fp = fopen("accounts.txt", "r");

    if(fp == NULL)
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
                 user.password) != EOF)
    {
        if(strcmp(id, user.id) == 0 &&
           strcmp(password, user.password) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if(found == 1)
    {
        printf("\nLogin Successful!\n");
    }
    else
    {
        printf("\nWrong Student ID or Password!\n");
    }
}

void change_password()
{
    struct Account user;

    char id[20];
    char oldpass[15];
    char newpass[15];

    int found = 0;
    int valid;

    FILE *fp;
    FILE *temp;

    fp = fopen("accounts.txt", "r");

    if(fp == NULL)
    {
        printf("No Account Found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if(temp == NULL)
    {
        printf("File Error!\n");
        fclose(fp);
        return;
}
printf("\n CHANGE PASSWORD: \n");

    printf("Student ID: ");
    scanf("%s", id);

    printf("Old Password: ");
    scanf("%s", oldpass);

    do
    {
        printf("New Password: ");
        scanf("%s", newpass);

        if(strcmp(oldpass, newpass) == 0)
        {
            printf("New password cannot be the same as old password.\n");
            valid = 0;
        }
        else
        {
            valid = valid_password(newpass);

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
                 user.password) != EOF)
    {
        if(strcmp(id, user.id) == 0 &&
           strcmp(oldpass, user.password) == 0)
        {
            fprintf(temp, "%s %s %s %s\n",
                    user.id,
                    user.email,
                    user.phone,
                    newpass);

            found = 1;
        }
        else
        {
            fprintf(temp, "%s %s %s %s\n",
                    user.id,
                    user.email,
                    user.phone,
                    user.password);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if(found == 1)
    {
        printf("\nPassword Changed Successfully!\n");
    }
    else
    {
        printf("\nWrong Student ID or Password!\n");
    }
}

void log_out()
{
printf("\n Logged out successfully! \n");
}

void admin_login()
{
    char password[15];
    printf("\n ADMIN LOGIN \n");

    printf("Password: ");
    scanf("%s", password);

    if(strcmp(password, "1234") == 0)
    {
        printf("\n Admin Login Successful! \n");
    }
    else
    {
        printf("\n Wrong Password! \n");
    }
    printf("\n ADMIN LOGIN \n");

    printf("Password: ");
    scanf("%s", password);

    if(strcmp(password, "1234") == 0)
    {
        printf("\n Admin Login Successful! \n");
    }
    else
    {
        printf("\n Wrong Password! \n");
    }
}