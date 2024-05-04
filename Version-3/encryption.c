#include "encryption.h"
#include <string.h>

void encryptPassword(const char password[], const char key[], char encryptedPassword[]) {
    size_t len = strlen(password);
    size_t keyLen = strlen(key);
    size_t j = 0; // Index for encryptedPassword

    for (size_t i = 0; i < len; ++i) {
        char encryptedChar = password[i] ^ key[i % keyLen]; // Perform XOR operation
        
        // Used to keep the char range between 32 and 126
        while (encryptedChar < 32 || encryptedChar > 126) {
            encryptedChar ^= key[i % keyLen]; // Re-apply XOR operation until character is in range
        }

        encryptedPassword[j++] = encryptedChar;
    }
    
    encryptedPassword[j] = '\0'; // Null-terminate the string
}

void decryptPassword(const char encryptedPassword[], const char key[], char decryptedPassword[]) {
    size_t len = strlen(encryptedPassword);
    size_t keyLen = strlen(key);
    size_t j = 0; // Index for decryptedPassword

    for (size_t i = 0; i < len; ++i) {
        char decryptedChar = encryptedPassword[i] ^ key[i % keyLen]; // Perform XOR operation
        
        // Used to keep the char range between 32 and 126
        while (decryptedChar < 32 || decryptedChar > 126) {
            decryptedChar ^= key[i % keyLen]; // Re-apply XOR operation until character is in range
        }

        decryptedPassword[j++] = decryptedChar;
    }
    
    decryptedPassword[j] = '\0'; // Null-terminate the string
}
