//
// Created by DaniilBorovoy on 03.03.2024.
//

#include "RSA.h"

#include <complex>
#include <iostream>
#include <string>

long modPow(long base, long exponent, long modulus) {
    long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

long int RSA::decrypt(long int i, long int d, long int n) {
    return (long) modPow(i, d, n);
}

long int RSA::encrypt(long int i, long int e, long int n) {
    return (long) modPow(i, e, n);
}


bool RSA::isPrime(long int prime) {
    long int i;

    long int j = (long int) std::sqrt((long double) prime);

    for (i = 2; i <= j; i++) {
        if (prime % i == 0) {
            return false;
        }
    }

    return true;
}

long int RSA::calculateE(long int t) {
    // Выбирается целое число e ( 1 < e < t ) // взаимно простое со значением функции Эйлера (t)
    for (long int e = 2; e < t; e++) {
        if (greatestCommonDivisor(e, t) == 1) {
            return e;
        }
    }

    return -1;
}


long int RSA::greatestCommonDivisor(long int e, long int t) {
    while (e > 0) {
        long int myTemp = e;
        e = t % e;
        t = myTemp;
    }

    return t;
}

long int RSA::calculateD(long int e, long int t) {
    // Вычисляется число d, мультипликативно обратное к числу e по модулю φ(n), то есть число, удовлетворяющее сравнению:
    //    d ⋅ e ≡ 1 (mod φ(n))

    long int d;
    long int k = 1;

    while (true) {
        k = k + t;

        if (k % e == 0) {
            d = (k / e);
            return d;
        }
    }
}
