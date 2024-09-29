#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include "port.h"

#define Stocks 17
#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1B[0m"
/*
typedef struct {
    float invested;
    float current;
    float balance;
} port;*/

typedef struct {
    int slno;
    char *ticker;
    int quantity;
    float avg_price;
    float cmp;
} stock;

void bar(float in, float c);
void show_stocks();
void display(stock s[], int count);

// Simulate slight changes in CMP
float simulate_CMP(float current) {
    srand(time(NULL));  // Seed random number
    float change = ((rand() % 5) - 2) / 100.0;  // Simulate ±2% variation
    return current * (1 + change);
}

void show_investments() {
    char buffer[256];
    int target_line = 2;
    int current_line = 0;
    FILE *file = fopen("portfolio.csv", "r");
    if (file == NULL) {
        printf("File Doesn't Exist");
        return;
    }

    port p;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        current_line++;
        if (current_line == target_line) {
            char *token = strtok(buffer, ",");
            if (token != NULL) {
                p.invested = atof(token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    p.current = atof(token);
                    token = strtok(NULL, ",");
                    if(token!=NULL)
                        p.balance=atof(token);
                }
            }
            break;
        }
    }
    fclose(file);

    bar(p.invested, p.current);
    show_stocks();
}

void bar(float in, float c) {
    int bar_height_in = in / 5000;
    int bar_height_c = c / 5000;

    printf("Invested value : ");
    for (int i = 0; i < bar_height_in; i++) {
        printf("#");
    }
    printf("  %.2f\n", in);
    printf("Current value  : ");
    for (int i = 0; i < bar_height_c; i++) {
        printf("#");
    }
    printf("  %.2f\n", c);

    if (c > in) {
        printf(GREEN "Your portfolio is in profit!\n" RESET);
    } else {
        printf(RED "Your portfolio is in loss.\n" RESET);
    }
}

void show_stocks() {
    stock s[Stocks];
    char buffer[256];
    int current_line = 0;
    FILE *file = fopen("sto.csv", "r");
    if (file == NULL) {
        printf("File Doesn't Exist\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        current_line++;
        if (current_line == 1) {
            continue;  // Skip header
        }

        char *token = strtok(buffer, ",");
        int i = current_line - 2;

        if (token != NULL) s[i].slno = atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL) s[i].ticker = strdup(token);
        token = strtok(NULL, ",");
        if (token != NULL) s[i].quantity = atoi(token);
        token = strtok(NULL, ",");
        if (token != NULL) s[i].avg_price = atof(token);
        token = strtok(NULL, ",");
        if (token != NULL) s[i].cmp = simulate_CMP(atof(token));  // Simulate real-time change
    }
    fclose(file);

    display(s, Stocks);
}

void display(stock s[], int count) {
    printf("Displaying All Stocks:\n\n");

    for (int i = 0; i < count; i++) {
        printf("-----------------------------------\n");
        printf("| %-3d | %-12s |\n", s[i].slno, s[i].ticker);
        printf("| Qty: %-5d   | Avg Price: %-8.2f |\n", s[i].quantity, s[i].avg_price);
        printf("| CMP: %-7.2f |\n", s[i].cmp);

        if (s[i].cmp > s[i].avg_price) {
            printf(GREEN "| Gain: %.2f%% |\n" RESET, ((s[i].cmp - s[i].avg_price) / s[i].avg_price) * 100);
        } else {
            printf(RED "| Loss: %.2f%% |\n" RESET, ((s[i].avg_price - s[i].cmp) / s[i].avg_price) * 100);
        }

        printf("-----------------------------------\n\n");
        sleep(1);
    }
}
