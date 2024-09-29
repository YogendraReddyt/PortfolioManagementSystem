// funds.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "port.h"

#define FUNDS_FILE "balance.csv"
port p;
// Function to check the available balance
float check_balance() {
    
    float balance = 0.0;
    int currentline=0;
    int targetline=2;
    FILE *file = fopen(FUNDS_FILE, "r");
    if (file == NULL) {
        printf("Funds file doesn't exist.\n");
        return balance;
    }
    
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        
            char *token = strtok(buffer, ",");
            if (token != NULL) {
                balance = atof(token);
            }
        
       // balance = atof(buffer);
    }
    fclose(file);
    return balance;
}

// Function to add money
void add_money(float amount) {
    float balance = check_balance();
    balance += amount;

    FILE *file = fopen(FUNDS_FILE, "w");
    if (file == NULL) {
        printf("Funds file doesn't exist.\n");
        return;
    }
    fprintf(file, "%.2f\n", balance);
    fclose(file);
    printf("Added %.2f to your balance. New balance: %.2f\n", amount, balance);
}

// Function to withdraw money
void withdraw_money(float amount) {
    float balance = check_balance();
    if (amount > balance) {
        printf("Insufficient funds. Current balance: %.2f\n", balance);
        return;
    }
    
    balance -= amount;
    FILE *file = fopen(FUNDS_FILE, "w");
    if (file == NULL) {
        printf("Funds file doesn't exist.\n");
        return;
    }
    fprintf(file, "%.2f\n", balance);
    fclose(file);
    printf("Withdrew %.2f from your balance. New balance: %.2f\n", amount, balance);
}
