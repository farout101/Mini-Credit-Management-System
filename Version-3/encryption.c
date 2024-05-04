#include "encryption.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

void generateRandomKey(char key[], size_t keyLen)
{
    srand(time(NULL)); // Seed the random number generator with the current time

    // Define the valid characters for the key
    const char valid_characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t num_valid_characters = strlen(valid_characters);

    for (size_t i = 0; i < keyLen; ++i)
    {
        // Generate a random index to select a character from the valid_characters array
        size_t index = rand() % num_valid_characters;
        // Assign the selected character to the key
        key[i] = valid_characters[index];
    }

    key[keyLen] = '\0'; // Null-terminate the string
}

void encryptPassword(const char password[], const char key[], char encryptedPassword[])
{
    size_t len = strlen(password);
    size_t keyLen = strlen(key);
    size_t j = 0; // Index for encryptedPassword

    for (size_t i = 0; i < len; ++i)
    {
        char encryptedChar;

        // Skip space characters in the password
        if (password[i] == ' ')
        {
            continue; // Skip further processing for space characters
        }

        encryptedChar = password[i] ^ key[i % keyLen]; // Perform XOR operation

        // Used to keep the char range between 32 and 126
        while (encryptedChar < 32 || encryptedChar > 126)
        {
            encryptedChar ^= key[i % keyLen]; // Re-apply XOR operation until character is in range
        }

        encryptedPassword[j++] = encryptedChar;
    }

    encryptedPassword[j] = '\0'; // Null-terminate the string
}

void decryptPassword(const char encryptedPassword[], const char key[], char decryptedPassword[])
{
    size_t len = strlen(encryptedPassword);
    size_t keyLen = strlen(key);
    size_t j = 0; // Index for decryptedPassword

    for (size_t i = 0; i < len; ++i)
    {
        char decryptedChar = encryptedPassword[i] ^ key[i % keyLen]; // Perform XOR operation

        // Used to keep the char range between 32 and 126
        while (decryptedChar < 32 || decryptedChar > 126)
        {
            decryptedChar ^= key[i % keyLen]; // Re-apply XOR operation until character is in range
        }

        decryptedPassword[j++] = decryptedChar;
    }

    decryptedPassword[j] = '\0'; // Null-terminate the string
}
