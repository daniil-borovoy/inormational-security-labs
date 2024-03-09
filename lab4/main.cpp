#include <iostream>
#include <fstream>
#include <cmath>
#include "RSA.h"

void encryptFile(const std::string &inputFile, const std::string &outputFile, long int e, long int n);

void decryptFile(const std::string &inputFile, const std::string &outputFile, long int d, long int n);

void test_file_rsa(long int p, long int q, long int n, long int t, long int e, long int d);

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

    if (d == e) {
        std::cout << "Wrong params" << std::endl;
        exit(1);
    }

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

    std::cout << "Text:" << std::endl;
    for (size_t i = 0; i < maxLength; ++i) {
        std::cout << (int) msg[i] << " ";
    }
    std::cout << std::endl;

    // Encryption
    for (size_t i = 0; i < maxLength; i++) {
        encryptedText[i] = RSA::encrypt(msg[i], e, n);
    }

    std::cout << "Encrypted Text:" << std::endl;
    for (size_t i = 0; i < maxLength; ++i) {
        std::cout << encryptedText[i] << " ";
    }
    std::cout << std::endl;

    // Encryption
    for (size_t i = 0; i < maxLength; i++) {
        long a = RSA::decrypt(encryptedText[i], d, n);
        decryptedText[i] = a;
    }

    std::cout << "\n\nTHE DECRYPTED MESSAGE IS:" << std::endl;
    for (size_t i = 0; i < maxLength; ++i) {
        std::cout << decryptedText[i] << " ";
    }


    std::cout << std::endl << std::endl;

    // Freeing dynamically allocated memory
    delete[] encryptedText;
    delete[] decryptedText;

    test_file_rsa(p, q, n, t, e, d);

    return 0;
}

void encryptFile(const std::string &inputFile, const std::string &outputFile, long int e, long int n) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile) {
        std::cerr << "Error: Unable to open input file " << inputFile << std::endl;
        return;
    }

    if (!outFile) {
        std::cerr << "Error: Unable to open output file " << outputFile << std::endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        long int encryptedChar = RSA::encrypt(ch, e, n);
        outFile << encryptedChar << " ";
    }

    inFile.close();
    outFile.close();

    std::cout << "File encrypted successfully." << std::endl;
}

void decryptFile(const std::string &inputFile, const std::string &outputFile, long int d, long int n) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);

    if (!inFile) {
        std::cerr << "Error: Unable to open input file " << inputFile << std::endl;
        return;
    }

    if (!outFile) {
        std::cerr << "Error: Unable to open output file " << outputFile << std::endl;
        return;
    }

    long int encryptedChar;
    while (inFile >> encryptedChar) {
        char decryptedChar = RSA::decrypt(encryptedChar, d, n);
        outFile << decryptedChar;
    }

    inFile.close();
    outFile.close();

    std::cout << "File decrypted successfully." << std::endl;
}

void test_file_rsa(long int p, long int q, long int n, long int t, long int e, long int d) {
    // long int p, q, n, t, e, d;
    bool flag;
    std::string inputFile, outputFile;

    std::cout << "Welcome to RCA program" << std::endl << std::endl;

    std::cout << "Enter input file name: ";
    std::cin >> inputFile;

    std::cout << "Enter output file name: ";
    std::cin >> outputFile;

    encryptFile(inputFile, outputFile + ".enc", e, n);

    // Decrypt file
    decryptFile(outputFile + ".enc", outputFile + ".dec", d, n);
}
