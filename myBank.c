#include <stdio.h>
#include "myBank.h"

static double bank_arr[50][3];
static int bank_size = sizeof(bank_arr)/sizeof(bank_arr[0]);
static char* menu_text = "\nPlease choose a transaction type:"
    "\n O-Open Account"
    "\n B-Balance Inquiry" 
    "\n D-Deposit"
    "\n W-Withdrawal" 
    "\n C-Close Account" 
    "\n I-Interest" 
    "\n P-Print" 
    "\n E-Exit"
    "\n";

void menu() {
    printf("%s",menu_text);
}

void openAccount() {
    int counter = 0;
    for (int i=0; i<bank_size; i++) {
        if (bank_arr[i][0]==1) {
            counter++;
        }
        else {
            int acc_num;
            double deposit_amount = deposit();
            if (deposit_amount == -1) {
                printf("Failed to read the amount\n");
                return;
            }
            if (deposit_amount < 0) {
                printf("Invalid Amount\n");
                return;
            }
            bank_arr[i][0] = 1;
            bank_arr[i][1] = i+901;
            bank_arr[i][2]+=deposit_amount;
            acc_num = bank_arr[i][1];
            printf("New account number is: %d \n",acc_num);
            return;
        }
        if (counter == 50) {
            printf("This bank can't hold more than 50 accounts and is currently full");
            return;
        }
    }
}

double deposit() {
    double deposit_amount;
    printf("Please enter amount for deposit: ");
    if (scanf("%lf", &deposit_amount) == 0) {
        return -1;
    }
    return deposit_amount;
}

void balance(int acc_num) {
    if (bank_arr[acc_num-901][0] != 1) {
        printf("This account is closed\n");
        return;
    }
    else if (acc_num > 950 || acc_num < 901) {
        printf("Invalid account number\n");
        return;
    }
    else {
        printf("The balance of account number %d is: %.2f\n",acc_num,bank_arr[acc_num-901][2]);
        return;
    }
}

void depositTrans(int acc_num) {
    if (acc_num > 950 || acc_num < 901) {
        printf("Invalid account number\n");
        return;
    }
    if (bank_arr[acc_num-901][0] != 1) {
        printf("This account is closed\n");
        return;
    }
    else {
        double deposit_amount;
        printf("Please enter amount for deposit: ");
        if (scanf("%lf", &deposit_amount) == 0) {
            printf("Failed to read the amount\n");
        }
        else if (deposit_amount < 0) {
            printf("Cannot deposit a negative amount\n");
        }
        else {
            bank_arr[acc_num-901][2] += deposit_amount;
            printf("The new balance is: %.2f\n",bank_arr[acc_num-901][2]);
        }   
    }
}

void withdraw(int acc_num) {
    if (acc_num > 950 || acc_num < 901) {
        printf("Invalid account number");
        return;
    }
    if (bank_arr[acc_num-901][0] != 1) {
        printf("This account is not active");
        return;
    }
    else {
        double w_sum;
        printf("Please enter the amount to withdraw: ");
        if (scanf("%lf", &w_sum) == 1) {
            if (bank_arr[acc_num-901][2] < w_sum) {
                printf("Cannot withdraw more than the balance\n");
                return;
            }
            else if (w_sum < 0) {
                printf("Cannot withdraw a negative amount\n");
            }
            else {
                bank_arr[acc_num-901][2] -= w_sum;
                printf("The new balance is: %.2f\n",bank_arr[acc_num-901][2]);
            }
        }
        else {
            printf("Invalid amount");
        }
    }
}

void close(int acc_num) {
    if (acc_num > 950 || acc_num < 901) {
        printf("Invalid account number\n");
        return;
    }
    if (bank_arr[acc_num-901][0] != 1) {
        printf("This account is already closed\n");
        return;
    }
    else {
        bank_arr[acc_num-901][0] = 0;
        bank_arr[acc_num-901][2] = 0;
        int closed_acc = bank_arr[acc_num-901][1];
        printf("Closed account number %d\n", closed_acc);
    }
}

void interest() {
    double interest_r;
    printf("Please enter interest rate: ");
    if (scanf("%lf", &interest_r) == 0) {
        printf("Failed to read the interest rate\n");
        return;
    } else if (interest_r < 0) {
        printf("Invalid interest rate\n");
    } else {
        for (int i=0; i<bank_size; i++) {
        if (bank_arr[i][0] == 1) {
            bank_arr[i][2] *= ((interest_r*0.01)+1);
            }
        }
    }
}

void printaccs() {
    for (int i=0; i<bank_size; i++) {
        if (bank_arr[i][0] == 1) {
            int acc_num;
            acc_num = bank_arr[i][1];
            printf("The balance of account number %d is: %.2f\n",acc_num,bank_arr[acc_num-901][2]);
        }
    } 
}