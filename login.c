#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

//int check_cred(char *, char *);

int read_login_details(char *username, char *password) {
    char buffer[256];
    int found_user = 0;
    FILE *file = fopen("cred.csv", "r");
    if (file == NULL) {
        printf("File doesn't exist.\n");
        return 0;
    }

    printf("----------------------------------\n");
    printf("----Welcome to YR Portfolio----\n");
    printf("----------------------------------\n");

    printf("Please enter your username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';  // Remove newline

    printf("Please enter your password: ");
    fgets(password, 100, stdin);
    password[strcspn(password, "\n")] = '\0';  // Remove newline

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *file_username = strtok(buffer, ",");
        char *file_password = strtok(NULL, ",");

        if (file_username != NULL && file_password != NULL) {
            file_password[strcspn(file_password, "\n")] = '\0';  // Remove newline

            if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
                found_user = 1;
                break;
            }
        }
    }
    fclose(file);

    if (found_user) {
        printf(GREEN "Login Successful! Welcome, %s!\n" RESET, username);
        return 1;
    } else {
        printf(RED "Invalid credentials. Try again.\n" RESET);
        return 0;
    }
}
