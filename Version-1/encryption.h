#ifndef ENCRYPTION_H
#define ENCRYPTION_H

void encryptPassword(const char password[], const char key[], char encryptedPassword[]); // Changed to char array
void decryptPassword(const char encryptedPassword[], const char key[], char decryptedPassword[]); // Changed to char array

#endif /* ENCRYPTION_H */
