#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int id;
    char name[20];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int num_accounts = 0;

bool nameexists(char name[20]);
bool idexists(int id);
void createaccount();
void menu();
void pickaccount();
void acctmenu(int);
void findaccount();
void screenclear();
void deposit(int);
void withdraw(int);
void transfer(int);
void acctdetails(int);
void transhistory(int);

int main() {
    srand(time(NULL));
    int choice;
    bool first = true;

    menu();
    printf("Enter your choice: ");
    scanf("%d", &choice);

    while (choice != 4) {
        if (first) {first = false;}
        switch (choice) {
            case 1:
                screenclear();
                createaccount();
                break;
            case 2:
                screenclear();
                findaccount();
                break;
            case 3:
                screenclear();
                pickaccount();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice\n");
        }
        menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
    }

    screenclear();
    printf("EXITING\n");

    return 0;
}

void createaccount() {
    if (num_accounts >= MAX_ACCOUNTS) {
        printf("Account limit reached. Cannot create more accounts.\n");
        return;
    }

    Account new_account;
    char newname[20];

    printf("ACCOUNT CREATION\n\n");

    printf("Enter your name:  ");
    scanf("%s", newname);
    while(nameexists(newname)){
        printf("Name already exists. Please enter a new name:  ");
        scanf("%s", newname);
    }
    strcpy(new_account.name,newname);

    int newid = rand() % 1000 + 1000;
    while(idexists(newid)){
        newid = rand() % 1000 + 1000;
    }
    new_account.id = newid;
    printf("Enter the initial deposit amount:  ");
    scanf("%f", &new_account.balance);

    accounts[num_accounts++] = new_account;

    printf("Account created successfully\n");
    printf("Account Details:\n");
    printf("Name: %s\n", new_account.name);
    printf("Account ID: %d\n", new_account.id);
    printf("Balance: $%.2f\n", new_account.balance);
    printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
    char na[20];
    scanf("%s", na);
    screenclear();
}

bool nameexists(char name[20]){
    for(int i=0;i<num_accounts;i++){
        if(strcmp(accounts[i].name,name)==0){
            return true;
        }
    }
    return false;
}

bool idexists(int id){
    for(int i=0;i<num_accounts;i++){
        if(accounts[i].id==id){
            return true;
        }
    }
    return false;
}

void menu() {
    printf("MAIN MENU\n");
    printf("1. Create Account\n");
    printf("2. Find Account\n");
    printf("3. Account Menu\n");
    printf("4. Exit Program\n");
}

void acctmenu(int id) {
    for(int i=0;i<num_accounts;i++) {
        if(accounts[i].id==id){
            printf("%s's ACCOUNT MENU\n", accounts[i].name);
        }
    }
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Account Details\n");
    printf("5. Transaction History\n");
    printf("6. Back\n");

    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            deposit(id);
        break;
        case 2:
            withdraw(id);
        break;
        case 3:
            transfer(id);
        break;
        case 4:
            acctdetails(id);
        break;
        case 5:
            transhistory(id);
        break;
        case 6:
            break;
        default:
            printf("Invalid choice, re-displaying menu\n");
        acctmenu(id);

    }
}

void findaccount() {
    int choice;
    printf("FIND ACCOUNT\n");
    printf("1. Find by Name\n");
    printf("2. Find by Account ID\n");
    printf("3. Back\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter Account name: ");
                char name[20];
                scanf("%s", name);
                if(nameexists(name))
                {
                    for(int i=0;i<num_accounts;i++){
                        if(strcmp(accounts[i].name,name)==0){
                            printf("Account Details:\n");
                            printf("Name: %s\n", accounts[i].name);
                            printf("Account ID: %d\n", accounts[i].id);
                            printf("Balance: $%.2f\n", accounts[i].balance);
                        }
                    }
                }
                else{
                    printf("Account not found\n");
                }
                printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
                char na[20];
                scanf("%s", na);
                screenclear();
                break;
            case 2:
                printf("Enter Account ID: ");
                int id;
                scanf("%d", &id);
                if(idexists(id)) {
                    for(int i=0;i<num_accounts;i++){
                        if(accounts[i].id==id){
                            printf("Account Details:\n");
                            printf("Name: %s\n", accounts[i].name);
                            printf("Account ID: %d\n", accounts[i].id);
                            printf("Balance: $%.2f\n", accounts[i].balance);
                        }
                    }
                }
                else {
                    printf("Account not found\n");
                }
                printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
                char la[20];
                scanf("%s", la);
                screenclear();
                break;
            case 3:
                break;
            default:
                printf("Invalid choice, re-displaying menu\n");
                findaccount();
        }
}

void screenclear() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void pickaccount() {
    screenclear();
    printf("CHOOSE AN ACCOUNT\n");
    printf("1. By Account Name\n");
    printf("2. By Account ID\n");
    printf("3. Back\n");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1: {
            printf("Enter Account Name: ");
            char name[20];
            scanf("%s", name);
            if(nameexists(name))
            {
                for(int i=0;i<num_accounts;i++){
                    if(strcmp(accounts[i].name,name)==0){
                        acctmenu(accounts[i].id);
                    }
                }
            }
            else{
                printf("Account not found\n");
            }
            break;
        }
        case 2: {
            int id;
            printf("Enter Account ID: ");
            scanf("%d", &id);
            if(idexists(id)) {
                for(int i=0;i<num_accounts;i++){
                    if(accounts[i].id==id){
                        acctmenu(id);
                    }
                }
            }
            else {
                printf("Account not found\n");
            }
            break;
        }
        case 3:
            break;
        default:
            printf("Invalid choice, re-displaying menu\n");
            pickaccount();
    }
}

void deposit(int id) {
    time_t tm;
    time(&tm);
    char filename[20];
    sprintf(filename, "Account%d.txt", id);
    FILE *fp = fopen(filename, "a");
    printf("DEPOSIT MONEY\n");
    printf("Enter amount to deposit: ");
    float amount;
    scanf("%f", &amount);

    amount = amount < 0 ? -amount : amount;
    for(int i=0;i<num_accounts;i++){
        if(accounts[i].id==id){
            accounts[i].balance += amount;
            printf("Deposit successful\n");
            printf("CURRENT BALANCE: $%.2f\n", accounts[i].balance);
            fprintf(fp, "Time of Transaction: %s", ctime(&tm));
            fprintf(fp, "Transaction Type: DEPOSIT($%.2f)\n\n", amount);
            fclose(fp);
        }
    }
    printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
    char na[20];
    scanf("%s", na);
    screenclear();
}

void withdraw(int id){
    time_t tm;
    time(&tm);
    char filename[20];
    sprintf(filename, "Account%d.txt", id);
    FILE *fp = fopen(filename, "a");
    printf("WITHDRAW MONEY\n");
    printf("Enter amount to withdraw: ");
    float amount;
    scanf("%f", &amount);

    amount = amount < 0 ? -amount : amount;
    for(int i=0;i<num_accounts;i++){
        if(accounts[i].id==id){
            if(accounts[i].balance < amount) {
                printf("Insufficient funds\n");
            }
            else {
                accounts[i].balance -= amount;
                printf("Withdrawal successful\n");
                printf("CURRENT BALANCE: $%.2f\n", accounts[i].balance);
                fprintf(fp, "Time of Transaction: %s", ctime(&tm));
                fprintf(fp, "Transaction Type: WITHDRAWAL($%.2f)\n\n", amount);
            }
        }
    }
    fclose(fp);
    printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
    char na[20];
    scanf("%s", na);
    screenclear();
}

void transfer(int id) {
    if(num_accounts<2){
        printf("Not enough accounts to transfer money\n");
    }
    else {
        time_t tm;
        time(&tm);
        char filename[20];
        sprintf(filename, "Account%d.txt", id);
        FILE *fp = fopen(filename, "a");
        printf("TRANSFER MONEY\n");
        for(int i=0;i<num_accounts;i++) {
            if(accounts[i].id!=id){
                printf("%d. %s\n", i, accounts[i].name);
            }
        }
        printf("Select account to transfer to: ");
        int choice;
        scanf("%d", &choice);
        if(choice>num_accounts-1){
            printf("Invalid choice\n");
        }
        else {
            printf("Enter amount to transfer: ");
            float amount;
            scanf("%f", &amount);
            amount = amount < 0 ? -amount : amount;
            for(int i=0;i<num_accounts;i++){
                if(accounts[i].id==id){
                    if(accounts[i].balance < amount) {
                        printf("Insufficient funds\n");
                    }
                    else {
                        for(int j=0;j<num_accounts;j++){
                            if(j==choice){
                                accounts[i].balance -= amount;
                                accounts[j].balance += amount;
                                printf("Transfer successful\n");
                                printf("CURRENT BALANCE: $%.2f\n", accounts[i].balance);
                                fprintf(fp, "Time of Transaction: %s", ctime(&tm));
                                fprintf(fp, "Transaction Type: TRANSFER($%.2f to %s)\n\n", amount, accounts[j].name);
                                fclose(fp);

                                char filename2[20];
                                sprintf(filename2, "Account%d.txt", accounts[j].id);
                                FILE *fp2 = fopen(filename2, "a");
                                fprintf(fp2, "Time of Transaction: %s", ctime(&tm));
                                fprintf(fp2, "Transaction Type: TRANSFER($%.2f from %s)\n\n", amount, accounts[i].name);
                                fclose(fp2);
                            }
                        }
                    }
                }
            }
        }
    }

    printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
    char na[20];
    scanf("%s", na);
    screenclear();
}

void acctdetails(int id) {
    printf("ACCOUNT DETAILS\n");
    for(int i=0;i<num_accounts;i++){
        if(accounts[i].id==id){
            printf("Name: %s\n", accounts[i].name);
            printf("Account ID: %d\n", accounts[i].id);
            printf("Balance: $%.2f\n", accounts[i].balance);
        }
    }
    
    printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
    char na[20];
    scanf("%s", na);
    screenclear();
}

void transhistory(int id) {
    char filename[20];
    sprintf(filename, "Account%d.txt", id);
    FILE *fp = fopen(filename, "r");
    if(fp==NULL){
        printf("No transactions have been made on this account\n");
    }
    else {
        printf("TRANSACTION HISTORY\n");
        printf("-------------------\n");
        char c;
        while((c=fgetc(fp))!=EOF){
            printf("%c", c);
        }
    }
    fclose(fp);
    printf("PRESS ANY KEY TO RETURN TO MAIN MENU: ");
    char na[20];
    scanf("%s", na);
    screenclear();
}