#include <iostream>
#include <fstream>
#include <cmath>
#include "RSA.h"

int main() {
    long int p, q, n, t, e, d;
    bool flag;
    std::string msg;

    std::cout << "Welcome to RCA program" << std::endl << std::endl;

    // Inputting prime numbers p and q
    do {
        std::cout << "Enter a Prime number p:";
        std::cin >> p;
        flag = RSA::isPrime(p);
        if (!flag) {
            std::cout <<
                    "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n"
                    << std::endl;
        }
    } while (!flag);

    do {
        std::cout << "Enter a Prime number q:";
        std::cin >> q;
        flag = RSA::isPrime(q);
        if (!flag) {
            std::cout <<
                    "\nWRONG INPUT (This number is not Prime. A prime number is a natural number greater than 1 that has no positive divisors other than 1 and itself)\n"
                    << std::endl;
        }
    } while (!flag);

    // Computing n = p * q
    n = p * q;
    std::cout << "\nResult of computing n = p*q = " << n << std::endl;

    // Computing Euler's totient function: t = (p−1) * (q−1)
    t = (p - 1) * (q - 1);
    std::cout << "Result of computing Euler's totient function:\t t = " << t << std::endl;

    // Calculating public and private keys
    e = RSA::calculateE(t);
    d = RSA::calculateD(e, t);

    std::cout << "\nRSA public key is (n = " << n << ", e = " << e << ")" << std::endl;
    std::cout << "RSA private key is (n = " << n << ", d = " << d << ")" << std::endl;

    std::cout << "\nEnter Message to be encrypted:" << std::endl;
    std::cin.ignore(); // Clearing input buffer
    std::getline(std::cin, msg);
    std::cout << "\nThe message is: " << msg << std::endl;

    // Determine maximum length of the message
    const int maxLength = msg.length();

    // Creating arrays for encrypted and decrypted text with dynamic memory allocation
    long int *encryptedText = new long int[maxLength];
    long int *decryptedText = new long int[maxLength];

    // Encryption
    for (size_t i = 0; i < maxLength; i++) {
        encryptedText[i] = RSA::encrypt(msg[i], e, n);
    }

    std::cout << "\nTHE ENCRYPTED MESSAGE IS:" << std::endl;
    for (size_t i = 0; i < maxLength; i++) {
        printf("%c", (char) encryptedText[i]);
    }

    // Decryption
    for (size_t i = 0; i < maxLength; i++) {
        decryptedText[i] = RSA::decrypt(encryptedText[i], d, n);
    }

    std::cout << "\n\nTHE DECRYPTED MESSAGE IS:" << std::endl;
    for (size_t i = 0; i < maxLength; i++) {
        printf("%c", (char) decryptedText[i]);
    }

    std::cout << std::endl << std::endl;

    // Freeing dynamically allocated memory
    delete[] encryptedText;
    delete[] decryptedText;

    return 0;
}
