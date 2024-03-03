//
// Created by DaniilBorovoy on 03.03.2024.
//

#ifndef RSA_H
#define RSA_H

class RSA final {
public:
    static long int encrypt(long int i, long int e, long int n);

    static long int decrypt(long int i, long int d, long int n);

    static long int calculateD(long int e, long int t);

    static long int calculateE(long int t);

    static bool isPrime(long int prime);

private:
    static long int greatestCommonDivisor(long int e, long int t);
};


#endif //RSA_H
