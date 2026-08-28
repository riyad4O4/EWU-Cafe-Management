#ifndef ACCOUNT_H
#define ACCOUNT_H

int create_account();
int fcreate_account();
int valid_password(char password[]);
int log_in();
int flog_in();
int change_password();
int fchange_password();
int log_out();
int admin_login();

#endif