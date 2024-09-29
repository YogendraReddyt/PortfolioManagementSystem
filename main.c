#include <stdio.h>
#include <stdlib.h>
#include "login.h"
#include "port.h"
#include "funds.h"

// Function prototypes
void funds_menu();

int main() {
    char *username = malloc(100 * sizeof(char));
    char *password = malloc(100 * sizeof(char));

    if (read_login_details(username, password)) {
        // User successfully logged in, show investments
        funds_menu();// Show funds menu after investments
    } else {
        printf("Login failed. Please try again.\n");
    }

    free(username);
    free(password);
    return 0;
}

void funds_menu() {
    int choice;
    float amount;
    
    while (1) {
        printf("\nFunds Management Menu:\n");
        printf("1. Check Balance\n");
        printf("2. Add Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Show portfolio\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Current balance: %.2f\n", check_balance());
                break;
            case 2:
                printf("Enter amount to add: ");
                scanf("%f", &amount);
                add_money(amount);
                break;
            case 3:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdraw_money(amount);
                break;
            case 4: show_investments(); break;
            case 5:
                return; // Exit funds menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
