//
// Created by DaniilBorovoy on 03.03.2024.
//

#include "RSA.h"

#include <complex>
#include <iostream>
#include <string>

long int RSA::decrypt(long int i, long int d, long int n) {
    long int current = i;
    long int result = 1;

    for (long int j = 0; j < d; j++) {
        result = result * current;
        result = result % n;
    }

    return result + 97;
}


long int RSA::encrypt(long int i, long int e, long int n) {
    long int current = i - 97;
    long int result = 1;

    for (long int j = 0; j < e; j++) {
        result = result * current;
        result = result % n;
    }

    return result;
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
