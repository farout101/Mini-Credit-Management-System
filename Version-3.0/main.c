#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "avl_tree.h"
#include "encryption.h"

#define INITIAL_CREDITS 100
#define INITIAL_ADMIN_CREDITS 500

char foldername[20] = "program_data";
char transactionFile[30] = "program_data/transition.txt";
char datafile[30] = "program_data/data.txt";
char keyfile[30] = "program_data/key.txt";

struct User **sortedUsersToadd;
struct Transition **sortedTransactionsfToadd;
struct Key **sortedKeysToadd;

struct Key keys[50];
struct User users[50];
struct Transition transitions[500];

int keyCount = 0;
int userCount = 0;
int transactionCount = 0;

// Function declaration
int isNumeric(const char *str);
void createFile(const char *file_name);
int isStrongPassword(const char *password);
int emailChecker(const char *username);
void shareCredits(struct User *sender, struct User *receiver);
void registration();
int login();
void readFile(const char *file_name);
void appendFile(const char *file_name, struct User **sortedUsers, int keyCount);
void loadUserData(const char *file_name);
void deleteUser();
void banUser();
void unbanUser();
int isValidPhoneNumber(const char *phoneNumber);
void appendtransactionFile(const char *file_name, struct Transition **sortedTransactionsf, int transactionCount);
void loadTransactionData(const char *file_name);
void savedata();
void create_folder(const char *folder_name);
void appendKeyFile(const char *file_name, struct Key **sortedKeysf, int keyCount);
void loadKeyFile(const char *file_name);
// End of declaration

int loggedInUserIndex = -1; // to track the logged-in user's credit

int main()
{
    system("cls");

    create_folder(foldername);

    char choice[50];

    // Load the related files
    loadUserData(datafile);
    loadTransactionData(transactionFile);
    loadKeyFile(keyfile);
    printf("\n");

    if (access(datafile, F_OK) != -1 && access(transactionFile, F_OK) != -1 && access(keyfile, F_OK) != -1)
    {
        printf("The data files are ready...\n\n");
    }
    else
    {
        createFile(datafile);
        createFile(transactionFile);
        createFile(keyfile);
    }

    do
    {
        printf("---Welcome to Credit Management System---\n");

        printf("\n1. to Login\n2. to Register\n3. to Refresh Data\n4. to Exit");
        printf("\nEnter your choice : ");
        scanf(" %[^\n]", choice);

        if (strcmp(choice, "1") == 0)
        {
            if (login())
            {
                system("cls");
                if (users[loggedInUserIndex].isAdmin == 0)
                {
                    printf("---Successfully logged in as user [%s]---\n", users[loggedInUserIndex].name);
                }
                else if (users[loggedInUserIndex].isAdmin == 2)
                {
                    printf("---Hello [%s]---\n", users[loggedInUserIndex].name);
                }
                else
                {
                    printf("---Successfully logged in as admin [%s]---\n", users[loggedInUserIndex].name);
                }
                char option[50];

                // Display additional options for admins
                if (users[loggedInUserIndex].isAdmin == 1 || users[loggedInUserIndex].isAdmin == 2)
                {
                    do
                    {
                        printf("--Admin Menu--\n\n");

                        printf("Current user : %s\n", users[loggedInUserIndex].name);
                        printf("Current credit : %.2lf\n", users[loggedInUserIndex].credits);
                        printf("Sharable credit : %.2f\n", (users[loggedInUserIndex].credits - users[loggedInUserIndex].credits * 0.02) - 50);
                        printf("\n1. to share\n2. to delete user\n3. to ban user\n4. to unban user\n5. to Refresh Data\n6. to logout\nEnter your choice : ");
                        scanf(" %[^\n]", option);

                        if (strcmp(option, "1") == 0)
                        {
                            system("cls");
                            printf("--Transition--\n\n");
                            char recipient[50];
                            printf("Enter the username to share credits with: ");
                            scanf(" %[^\n]", recipient);

                            // Find the recipient user
                            struct User *recipientUser = NULL;
                            for (int j = 0; j < userCount; j++)
                            {
                                if (strcmp(users[j].name, recipient) == 0 && users[j].isBan == 0)
                                {
                                    recipientUser = &users[j];
                                    break;
                                }
                            }

                            if (recipientUser != NULL && strcmp(users[loggedInUserIndex].name, recipientUser->name) != 0)
                            {
                                shareCredits(&users[loggedInUserIndex], recipientUser);
                                continue;
                            }
                            else
                            {
                                system("cls");
                                printf("Recipient not found.\n");
                                continue;
                            }
                        }
                        if (strcmp(option, "2") == 0)
                        {
                            deleteUser();
                            continue;
                        }

                        if (strcmp(option, "3") == 0)
                        {
                            banUser();
                            continue;
                        }

                        if (strcmp(option, "4") == 0)
                        {
                            unbanUser();
                            continue;
                        }
                        if (strcmp(option, "5") == 0)
                        {
                            savedata();

                            system("cls");

                            continue;
                        }
                        if (strcmp(option, "6") == 0)
                        {
                            system("cls");
                            printf("You have logged out!\n");
                            loggedInUserIndex = -1; // Set loggedInUserIndex to -1 to stay in the main loop
                            break;
                        }

                        else
                        {
                            system("cls");
                            printf("Invalid choice. Please try again. \n");
                            continue;
                        }

                    } while (strcmp(option, "6") != 0);
                }
                else
                {
                    do
                    {
                        system("cls");
                        printf("--User Menu--\n\n");

                        char option[50];
                        printf("Current User : %s\n", users[loggedInUserIndex].name);
                        printf("Current credit : %.2lf\n", users[loggedInUserIndex].credits);
                        printf("Sharable credit : %.2f\n", (users[loggedInUserIndex].credits - users[loggedInUserIndex].credits * 0.02) - 50);
                        printf("\n1. to share\n2. to Refresh Data\n3. to logout\nEnter your choice : ");
                        scanf(" %[^\n]", option);

                        if (strcmp(option, "1") == 0)
                        {
                            system("cls");
                            printf("\n--Transaction--\n\n");
                            char recipient[50];
                            printf("Enter the username to share credits with: ");
                            scanf(" %[^\n]", recipient);

                            // Find the recipient user
                            struct User *recipientUser = NULL;
                            for (int j = 0; j < userCount; j++)
                            {
                                if (strcmp(users[j].name, recipient) == 0)
                                {
                                    recipientUser = &users[j];
                                    break;
                                }
                            }

                            if (recipientUser != NULL)
                            {
                                shareCredits(&users[loggedInUserIndex], recipientUser);
                                continue;
                            }
                            else
                            {
                                system("cls");
                                printf("Recipient not found.\n");
                                continue;
                            }
                        }

                        else if (strcasecmp(option, "2") == 0)
                        {
                            savedata();

                            system("cls");

                            continue;
                        }
                        else if (strcmp(option, "3") == 0)
                        {
                            system("cls");
                            printf("You have logged out!\n");
                            loggedInUserIndex = -1; // Set loggedInUserIndex to -1 to stay in the main loop
                            break;
                        }

                        else
                        {
                            system("cls");
                            printf("Invalid choice. Please try again. \n");
                            continue;
                        }
                    } while (strcmp(option, "3") != 0);
                }
            }
            continue;
        }
        if (strcmp(choice, "2") == 0)
        {
            system("cls");
            registration();
            continue;
        }
        if (strcmp(choice, "3") == 0)
        {
            savedata();

            system("cls");

            continue;
        }
        if (strcmp(choice, "4") == 0)
        {
            system("cls");
            printf("UserCount : %d \n", userCount);
            printf("transactionCount : %d \n", transactionCount);
            printf("The program terminated\n");

            savedata();

            free(sortedUsersToadd);
            free(sortedTransactionsfToadd);
            free(sortedKeysToadd);

            continue;
        }

        else
        {
            system("cls");
            printf("Invalid choice. Please try again. \n");
        }
    } while (strcmp(choice, "4") != 0);

    return 0;
}

void createFile(const char *file_name)
{
    FILE *file = fopen(file_name, "w");

    if (file == NULL)
    {
        perror("Error creating file!");
    }
    else
    {
        printf("The file %s is successfully created...\n", file_name);
    }
}

void appendFile(const char *file_name, struct User **sortedUsersf, int userCount)
{
    FILE *file = fopen(file_name, "w");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        fprintf(file, "%s %s %.2lf %d %d %s\n", sortedUsersf[i]->name, sortedUsersf[i]->password, sortedUsersf[i]->credits, sortedUsersf[i]->isAdmin, sortedUsersf[i]->isBan, sortedUsersf[i]->phoneNo);
    }

    fclose(file);
}

void appendtransactionFile(const char *file_name, struct Transition **sortedTransactionsf, int transactionCount)
{
    FILE *file = fopen(file_name, "w");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    for (int i = 0; i < transactionCount; i++)
    {
        fprintf(file, "%d. %s %s %.2lf %s\n", sortedTransactionsf[i]->id, sortedTransactionsf[i]->sender, sortedTransactionsf[i]->receiver, sortedTransactionsf[i]->amount, sortedTransactionsf[i]->timestamp);
    }

    fclose(file);
}

void appendKeyFile(const char *file_name, struct Key **sortedKeysf, int keyCount)
{
    FILE *file = fopen(file_name, "w");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    for (int i = 0; i < keyCount; i++)
    {
        fprintf(file, "%s %s %s\n", sortedKeysf[i]->name, sortedKeysf[i]->phoneNo, sortedKeysf[i]->key);
    }

    fclose(file);
}

void loadKeyFile(const char *file_name)
{
    keyCount = 0;

    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening (%s) for reading...\n", file_name);
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Handle user registration record
        if (sscanf(buffer, "%s %s %s\n", keys[keyCount].name, keys[keyCount].phoneNo, keys[keyCount].key) != 3)
        {
            printf("Error reading user registration record.\n");
            break;
        }

        keyCount++;

        if (keyCount >= sizeof(keys) / sizeof(keys[0]))
        {
            printf("Warning: Maximum user limit reached.\n");
            break;
        }
    }

    printf("%d keys loaded.\n", keyCount);

    fclose(file);
}

void loadUserData(const char *file_name)
{
    userCount = 0;

    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening (%s) for reading...\n", file_name);
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Handle user registration record
        if (sscanf(buffer, "%s %s %lf %d %d %s\n", users[userCount].name, users[userCount].password, &users[userCount].credits, &users[userCount].isAdmin, &users[userCount].isBan, users[userCount].phoneNo) != 6)
        {
            printf("Error reading user registration record.\n");
            break;
        }

        userCount++;

        if (userCount >= sizeof(users) / sizeof(users[0]))
        {
            printf("Warning: Maximum user limit reached.\n");
            break;
        }
    }

    printf("%d users loaded.\n", userCount);

    fclose(file);
}

void loadTransactionData(const char *file_name)
{
    transactionCount = 0;

    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening (%s) file for reading...\n", file_name);
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Handle user registration record
        if (sscanf(buffer, "%d. %s %s %lf %s", &transitions[transactionCount].id, transitions[transactionCount].sender, transitions[transactionCount].receiver, &transitions[transactionCount].amount, transitions[transactionCount].timestamp) != 5)
        {
            printf("Error reading transition record.\n");
            break;
        }

        transactionCount++;

        if (transactionCount >= sizeof(transitions) / sizeof(transitions[0]))
        {
            printf("Warning: Maximum transition record limit reached.\n");
            break;
        }
    }

    printf("%d transitions loaded.\n", transactionCount);

    fclose(file);
}

// Unused function
void readFile(const char *file_name)
{
    FILE *file = fopen(file_name, "r");

    if (file == NULL)
    {
        printf("Error opening file: %s\n", file_name);
        return;
    }

    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);
}

int isStrongPassword(const char *password)
{
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < len; i++)
    {
        if (isupper(password[i]))
        {
            hasUpper++;
        }
        else if (islower(password[i]))
        {
            hasLower++;
        }
        else if (isdigit(password[i]))
        {
            hasDigit++;
        }
        else if (ispunct(password[i]))
        {
            hasSpecial++;
        }
        else if (isspace(password[i]))
        {
            return 0;
        }
    }

    if (len >= 6 && hasUpper && hasLower && hasDigit && hasSpecial)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int emailChecker(const char *username)
{
    int len = strlen(username);
    int atCount = 0;
    int dotCount = 0;

    for (int i = 0; i < len; i++)
    {
        if (username[i] == '@')
        {
            atCount++;
        }
        else if (username[i] == '.')
        {
            dotCount++;
        }
    }

    if (atCount == 1 && dotCount >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void shareCredits(struct User *sender, struct User *receiver)
{
    double creditToShare;

    printf("Your current credit : %.2lf\n", sender->credits);
    printf("Your sharablae credit : %.2lf\n", (sender->credits - sender->credits * 0.02) - 50);
    printf("Enter the amount of credits to share : ");
    scanf("%lf", &creditToShare);

    if (creditToShare <= ((sender->credits - creditToShare * 0.02) - 50))
    {
        double OwnerBouns = creditToShare * 0.02;

        receiver->credits += creditToShare;
        sender->credits -= creditToShare;

        // The Owner Kauk Sar
        sender->credits -= OwnerBouns;
        users[0].credits += OwnerBouns;

        printf("The user data updated successfully");

        transitions[transactionCount].id = transactionCount + 1;
        strcpy(transitions[transactionCount].sender, sender->name);
        strcpy(transitions[transactionCount].receiver, receiver->name);
        transitions[transactionCount].amount = creditToShare;

        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        if (timeinfo != NULL)
        {
            // Convert the time to a readable format and store it
            strftime(transitions[transactionCount].timestamp, sizeof(transitions[transactionCount].timestamp), "%Y-%m-%d_%H:%M:%S", timeinfo);
        }
        else
        {
            // Indicate that the timestamp is not available
            strcpy(transitions[transactionCount].timestamp, "N/A");
        }

        system("cls");
        printf("Credits shared successfully!\n");

        transactionCount++;
    }
    else
    {
        system("cls");
        printf("Insufficient credits to share.\n");
        printf("Your maximum credit that can be shared : %lf \n", (sender->credits - creditToShare * 0.02) - 50);
    }

    savedata();
}

void registration()
{

    system("cls");

    printf("---Registration---\n\n");

    if (userCount < 50)
    {
        char username[50];
        char password[50];
        char confirmPass[50];
        char phoneNo[20];
        int uExists = 0;

        printf("Enter your email : ");
        scanf(" %[^\n]", username);

        if (!emailChecker(username))
        {
            system("cls");
            printf("Not a valid email. Please enter a valid email address. \n");
            return;
        }

        for (int i = 0; i < userCount; i++)
        {
            if (strcmp(username, users[i].name) == 0)
            {
                uExists = 1;
                break;
            }
        }

        if (uExists)
        {
            system("cls");
            printf("E-mail already exists. Try another name...\n");
        }
        else
        {
            printf("Enter your phone number : ");
            scanf(" %[^\n]", phoneNo);
            // Check if the phone number is valid

            if (isValidPhoneNumber(phoneNo) == 0)
            {
                system("cls");
                printf("Not a valid phone number. Please enter a valid phone number. \n");
                return;
            }

            strcpy(users[userCount].phoneNo, phoneNo);
            strcpy(keys[keyCount].phoneNo, phoneNo);

            strcpy(users[userCount].name, username);
            strcpy(keys[keyCount].name, username);

            printf("Enter password (no space is allowed): ");
            scanf(" %[^\n]", password);

            if (!isStrongPassword(password))
            {
                system("cls");
                printf("Password is not strong enough.\n(The password must be at least 8 characters, at least 1 upper case, digit and punctuation).\nPlease use a stronger password.\n");
                return;
            }

            printf("Confirm password : ");
            scanf(" %[^\n]", confirmPass);

            if (strcmp(password, confirmPass) == 0)
            {
                password[strcspn(password, "\n")] = '\0';

                char encrypPASS[strlen(password) + 1];
                char key[strlen(password) + 1];

                generateRandomKey(key, strlen(password));
                encryptPassword(password, key, encrypPASS);

                strcpy(keys[keyCount].key, key);

                strcpy(users[userCount].password, encrypPASS);

                // Set the isAdmin flag based on userCount
                if (userCount < 1)
                {
                    users[userCount].isAdmin = 2;
                }
                else if (userCount < 3)
                {
                    users[userCount].isAdmin = 1;
                }
                else
                {
                    users[userCount].isAdmin = 0;
                }

                if (users[userCount].isAdmin == 1)
                {
                    users[userCount].credits = INITIAL_ADMIN_CREDITS;
                    system("cls");
                    printf("Successfully Registered as an Admin!!!\n");
                }
                else if (users[userCount].isAdmin == 2)
                {
                    users[userCount].credits = INITIAL_ADMIN_CREDITS;
                    system("cls");
                    printf("You are the Owner of this app.\n");
                }
                else
                {
                    users[userCount].credits = INITIAL_CREDITS;
                    system("cls");
                    printf("Successfully Registered!!!\n");
                }

                printf("Current credit of [%s] : %.2lf\n\n", users[userCount].name, users[userCount].credits);

                printf("< Your Security Key : %s >\n", keys[keyCount].key);

                userCount++;
                keyCount++;

                savedata();
            }
            else
            {
                system("cls");
                printf("Password doesn't match\n");
            }
        }
    }
    else
    {
        system("cls");
        printf("User limit reached (50 users) :( ");
    }
}

int login()
{
    int keyFound = 0;

    system("cls");

    printf("---Login---\n\n");

    char username[50];
    char password[50];
    char key[50];

    printf("Enter your e-mail : ");
    scanf(" %[^\n]", username);

    // Check if the user is banned
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0 && users[i].isBan == 1)
        {
            system("cls");
            printf("Your account has been banned. Please contact support.\n");
            return 0;
        }
    }

    printf("Enter password : ");
    scanf(" %[^\n]", password);

    char decrypPass[strlen(password) + 1];

    // Finding The key
    for (int i = 0; i < keyCount; i++)
    {
        if (strcmp(keys[i].name, username) == 0)
        {
            strcpy(key, keys[i].key);
            keyFound = 1;
        }
    }

    if (keyFound == 0)
    {
        printf("Error finding the key.\n");
    }

    // Authenticate the user
    for (int i = 0; i < userCount; i++)
    {

        decryptPassword(users[i].password, key, decrypPass);

        if (strcmp(users[i].name, username) == 0 && strcmp(decrypPass, password) == 0)
        {
            loggedInUserIndex = i;
            printf("---Successfully logged in---\n");
            return 1;
        }
    }

    // If the loop completes, the username or password is incorrect
    system("cls");
    printf("Invalid username or password. Please try again.\n");
    return 0;
}

void deleteUser()
{
    system("cls");

    printf("---Delete User---\n\n");

    char username[50];
    int userIndex = -1;

    printf("Enter the username to delete : ");
    scanf(" %[^\n]", username);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0)
        {
            userIndex = i;
            break;
        }
    }

    if (userIndex != -1)
    {
        // Check if the user to be deleted is an admin or not
        if (!(users[userIndex].isAdmin == 1 || users[userIndex].isAdmin == 2))
        {
            // Remove the user from the array
            for (int i = userIndex; i < userCount - 1; i++)
            {
                strcpy(users[i].name, users[i + 1].name);
                strcpy(users[i].password, users[i + 1].password);
                users[i].credits = users[i + 1].credits;
                users[i].isAdmin = users[i + 1].isAdmin;
                users[i].isBan = users[i + 1].isBan;
                strcpy(users[i].phoneNo, users[i + 1].phoneNo);
            }

            userCount--;

            for (int i = userIndex; i < keyCount - 1; i++)
            {
                strcpy(keys[i].name, keys[i + 1].name);
                strcpy(keys[i].phoneNo, keys[i + 1].phoneNo);
                strcpy(keys[i].key, keys[i + 1].key);
            }

            keyCount--;

            system("cls");
            printf("User %s is deleted successfully.\n", username);

            savedata();
        }
        else
        {
            system("cls");
            printf("Admin accounts cannot be deleted.\n");
        }
    }
    else
    {
        system("cls");
        printf("User %s doesn't exist\n", username);
    }
}

void banUser()
{
    system("cls");
    char username[50];

    printf("---Ban User---\n\n");

    printf("Enter the email to ban : ");
    scanf(" %[^\n]", username);

    int userBanned = 0;
    int track_user = 0;

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].name, username) == 0)
        {
            track_user = 1;
            // Check if the user is an admin
            if (users[i].isAdmin == 1 || users[i].isAdmin == 2)
            {
                system("cls");
                printf("Admin accounts cannot be banned.\n");
                return;
            }
            else
            {
                // Update the ban status
                users[i].isBan = 1;

                system("cls");
                printf("The user %s has been banned.\n", username);
                userBanned = 1;
            }
        }
    }

    savedata();
}

void unbanUser()
{
    char username[50];
    system("cls");
    printf("<---Unban User--->\n\n");
    printf("Enter email to unban : ");
    scanf(" %[^\n]", username);

    int userUnbanned = 0;
    int search_tracker = 0;
    for (int i = 0; i < userCount; i++)
    {

        if (strcmp(users[i].name, username) == 0)
        {
            search_tracker = 1;
            if (users[i].isBan == 1)
            {
                system("cls");
                users[i].isBan = 0;
                printf("The user is successfully unbanned.\n");
                userUnbanned = 1;
            }
            else
            {
                system("cls");
                printf("The user is not banned yet!\n");
            }
        }
    }

    savedata();
}

int isNumeric(const char *str)
{

    for (int i = 0; str[i] != '\0'; i++)
    {
        // Check if the character is not a digit
        if (!isdigit(str[i]))
        {
            return 0; // Not a Number
        }
    }

    return 1; // Number
}

int isValidPhoneNumber(const char *phoneNumber)
{
    int len = strlen(phoneNumber);

    if (len != 10 && len != 11)
    {
        return 0;
    }

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(phoneNumber[i]))
        {
            return 0;
        }
    }

    if (len == 11 && strncmp(phoneNumber, "09", 2) != 0)
    {
        return 0;
    }

    return 1;
}

void savedata()
{
    sortedUsersToadd = sortUsers(users, userCount);
    sortedTransactionsfToadd = sortTransitions(transitions, transactionCount);
    sortedKeysToadd = sortKeys(keys, keyCount);

    appendFile(datafile, sortedUsersToadd, userCount);
    appendtransactionFile(transactionFile, sortedTransactionsfToadd, transactionCount);
    appendKeyFile(keyfile, sortedKeysToadd, keyCount);
}

void create_folder(const char *folder_name)
{
    // Check if the folder already exists
    if (access(folder_name, F_OK) != -1)
    {
        printf("The folder (%s) is ready...\n\n", folder_name);
    }
    else
    {
        // Create the folder if it does not exist
        if (mkdir(folder_name) == -1)
        {
            perror("Error creating folder!");
        }
        else
        {
            printf("The folder %s is successfully created...\n\n", folder_name);
        }
    }
}