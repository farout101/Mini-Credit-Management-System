#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEY_LENGTH 16 // Define the length of the key

// Function to generate a random key and store it in a file
void generateAndStoreKey(const char* filename) {
    FILE* file = fopen(filename, "wb"); // Open file for writing in binary mode
    
    if (file != NULL) {
        srand(time(NULL)); // Seed the random number generator
        
        // Generate random key
        char key[KEY_LENGTH + 1]; // +1 for null terminator
        for (int i = 0; i < KEY_LENGTH; ++i) {
            key[i] = rand() % 128; // Generate random ASCII characters
        }
        key[KEY_LENGTH] = '\0'; // Null-terminate the string
        
        // Write key to file
        fwrite(key, sizeof(char), KEY_LENGTH, file);
        
        fclose(file); // Close the file
    } else {
        printf("Error: Unable to open file for writing.\n");
    }
}

// Function to read the key from a file
void readKeyFromFile(const char* filename, char key[]) {
    FILE* file = fopen(filename, "rb"); // Open file for reading in binary mode
    
    if (file != NULL) {
        // Read key from file
        fread(key, sizeof(char), KEY_LENGTH, file);
        
        fclose(file); // Close the file
    } else {
        printf("Error: Unable to open file for reading.\n");
    }
}

int main() {
    const char* keyFilename = "key.txt"; // File to store the key
    char key[KEY_LENGTH + 1]; // +1 for null terminator

    // Generate and store the key
    generateAndStoreKey(keyFilename);
    printf("Random key generated and stored in file '%s'.\n", keyFilename);
    
    // Read the key from file
    readKeyFromFile(keyFilename, key);
    printf("Key read from file: %s\n", key);

    return 0;
}
