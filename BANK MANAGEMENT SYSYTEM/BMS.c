#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct account {
    char username[20];
    char Fullname[200];
    char transaction[36];
    char address[200];
    char phone[11];
    char credialfile[40];
    char email[100];
    char password[16];
    float balance;
    int choice;
} acc;

void login_cred_check(char name[], char password[]);
void debit();
void payment();
void accounts();
void deposit();
void create_account();
void login_cred_store(char name[], char password[]);
void TransactionPrint();

void login_cred_check(char name[], char password[]) {
    FILE *fp;
    char stored_username[20], stored_password[16];
    float temp_balance = 0.0;
    int login_success = 0, choice;

    printf("Enter your credential file (usernameCredential.txt): ");
    scanf("%s", acc.credialfile);

    fp = fopen(acc.credialfile, "r");
    if (fp == NULL) {
        printf("Error: Credentials file not found!\n");
        return;
    }

    while (fscanf(fp, "%19s %15s", stored_username, stored_password) == 2) {
        if (strcmp(stored_username, name) == 0 && strcmp(stored_password, password) == 0) {
            login_success = 1;
            break;
        }
    }
    fclose(fp);

    if (!login_success) {
        printf("Login failed ❌\n");
        return;
    }

    printf("Login successful ✅\n");

    // Load balance from transaction file
    fp = fopen(name, "r");
    if (fp != NULL) {
        while (fscanf(fp, "Balance: %f", &temp_balance) == 1) {
            acc.balance = temp_balance;
        }
        fclose(fp);
    } else {
        acc.balance = 0.0;
    }

    printf("Your current balance: %.2f\n", acc.balance);

    do {
        printf("\n1. Deposit\n2. Withdraw\n3. Payment\n4. Print Transaction\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                deposit();
                break;
            case 2:
                debit();
                break;
            case 3:
                payment();
                break;
            case 4:
                TransactionPrint();
                break;
            case 5:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);
}

void login_cred_store(char name[], char password[]) {
    FILE *fp;
    printf("Enter your credential file (usernameCredential.txt): ");
    scanf("%s", acc.credialfile);

    fp = fopen(acc.credialfile, "a");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    fprintf(fp, "%s %s\n", name, password);
    fclose(fp);
}

void TransactionPrint() {
    FILE *fp;
    char ch;
    printf("Enter transaction file (usernameTransaction.txt): ");
    scanf("%s", acc.transaction);

    fp = fopen(acc.transaction, "r");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}

void payment() {
    FILE *fp;
    float payment_amount;
    long acc_no;

    printf("Enter transaction file (usernameTransaction.txt): ");
    scanf("%s", acc.transaction);

    fp = fopen(acc.transaction, "a");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    printf("Enter payment amount: ");
    scanf("%f", &payment_amount);
    printf("Enter recipient's account number: ");
    scanf("%ld", &acc_no);

    if (payment_amount > acc.balance) {
        printf("Insufficient balance\n");
    } else {
        acc.balance -= payment_amount;
        fprintf(fp, "Payment: %.2f on %s %s to account %ld\n", payment_amount, __DATE__, __TIME__, acc_no);
        fprintf(fp, "Balance: %.2f\n", acc.balance);
        printf("Payment successful ✅\n");
        printf("Your current balance is %.2f\n", acc.balance);
    }

    fclose(fp);
}

void debit() {
    FILE *fp;
    float withdraw_amount;

    printf("Enter transaction file (usernameTransaction.txt): ");
    scanf("%s", acc.transaction);

    fp = fopen(acc.transaction, "a");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    printf("Enter withdrawal amount: ");
    scanf("%f", &withdraw_amount);

    if (withdraw_amount > acc.balance) {
        printf("Insufficient balance\n");
    } else {
        acc.balance -= withdraw_amount;
        fprintf(fp, "Withdraw: %.2f on %s %s\n", withdraw_amount, __DATE__, __TIME__);
        fprintf(fp, "Balance: %.2f\n", acc.balance);
        printf("Withdrawal successful ✅\n");
        printf("Your current balance is %.2f\n", acc.balance);
    }

    fclose(fp);
}

void deposit() {
    FILE *fp;
    float deposit_amount;

    printf("Enter transaction file (usernameTransaction.txt): ");
    scanf("%s", acc.transaction);

    fp = fopen(acc.transaction, "a");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    printf("Enter deposit amount: ");
    scanf("%f", &deposit_amount);

    acc.balance += deposit_amount;
    fprintf(fp, "Deposit: %.2f on %s %s\n", deposit_amount, __DATE__, __TIME__);
    fprintf(fp, "Balance: %.2f\n", acc.balance);
    printf("Deposit successful ✅\n");
    printf("Your current balance is %.2f\n", acc.balance);

    fclose(fp);
}

void create_account() {
    FILE *fp;

    printf("Enter your username: ");
    scanf("%s", acc.username);
    printf("Enter your password: ");
    scanf("%s", acc.password);
    login_cred_store(acc.username, acc.password);

    printf("Enter your full name: ");
    scanf("%s", acc.Fullname);
    printf("Enter your transaction file (usernameTransaction.txt): ");
    scanf("%s", acc.transaction);

    fp = fopen(acc.transaction, "w");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    acc.balance = 0.0;
    fprintf(fp, "Fullname: %s\n", acc.Fullname);
    fprintf(fp, "Name: %s\n", acc.username);
    fprintf(fp, "Balance: %.2f\n", acc.balance);

    printf("Account created successfully ✅\n");
    fclose(fp);
}

int main() {
    while (1) {
        printf("\n........Welcome to V Bank............\n");
        printf("1. Create account\n2. Login\n3. Exit\n");
        scanf("%d", &acc.choice);

        if (acc.choice == 1) {
            create_account();
        } else if (acc.choice == 2) {
            printf("Enter your username: ");
            scanf("%s", acc.username);
            printf("Enter your password: ");
            scanf("%s", acc.password);
            login_cred_check(acc.username, acc.password);
        } else if (acc.choice == 3) {
            exit(0);
        }
    }
}
