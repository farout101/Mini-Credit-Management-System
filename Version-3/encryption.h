#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stddef.h> // Include for size_t

void encryptPassword(const char password[], const char key[], char encryptedPassword[]);
void decryptPassword(const char encryptedPassword[], const char key[], char decryptedPassword[]);
void generateRandomKey(char key[], size_t keyLen);

#endif
