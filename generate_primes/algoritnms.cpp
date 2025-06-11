#include <iostream>
#include <random>
#include <cmath>
#include <set>

#include "commands.hpp"

using namespace std;
typedef unsigned long long ull;

//Тест миллера
bool miller_test(ull number, int rounds) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2, number - 1);

    if (number == 2 || number == 3 || number == 5 || number == 7) return true;
    if (number < 10) return false;

    set<ull> bases;
    while ((int)bases.size() != rounds) {
        bases.insert(dist(gen));
    }

    //Малая теормеа Ферма
    for (auto& base : bases) {
        if (modPow(base, number - 1, number) != 1) {
            return false;
        }
    }

    //Факторизация
    vector<pair<int, int>> primeFactors = factorize(number - 1);
    for (auto& factor : primeFactors) {
        int primeQ = factor.first;
        bool onlyOne = true;
        for (auto& base : bases) {
            if (modPow(base, (number - 1) / primeQ, number) != 1) {
                onlyOne = false;
                break;
            }
        }
        if (onlyOne) {
            return false;
        }
    }
    return true;
}

//Тест поклингтона
bool pocklington_test(ull number, int rounds) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distR(1, 3);
    uniform_int_distribution<> distA(2, number - 1);

    if (number == 2 || number == 3 || number == 5 || number == 7) return true;
    if (number < 10) return false;

    int r = distR(gen);
    vector<pair<int, int>> primeFactors = factorize((number - 1) / r);

    set<ull> bases;
    while ((int)bases.size() != rounds) {
        bases.insert(distA(gen));
    }

    //Малая теорема Ферма
    for (auto& base : bases) {
        if (modPow(base, number - 1, number) != 1) {
            return false;
        }
    }

    for (auto& base : bases) {
        bool noOne = true;
        for (auto& factor : primeFactors) {
            int primeQ = factor.first;
            if (modPow(base, (number - 1) / primeQ, number) == 1) {
                noOne = false;
                break;
            }
        }
        if (noOne) {
            return true;
        }
    }
    return false;
}

//Генерация простого с помощью теста миллера
pair<ull, int> miller_prime(int bitSize, vector<int> primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distQ(0, primes.size() - 1);
    uniform_int_distribution<> distA(1, 20);
    
    ull candidate = 1;
    int failedMillerCount = -1;
    while (!miller_test(candidate, 9)) {
        int attemptCount = 0;
        ull m = 1;
        set<int> uniqQ;
        while (sizeNum(m) != bitSize - 1) {
            int primeQ = primes[distQ(gen)];
            int expA = distA(gen);
            if (sizeNum(m * (int)pow(primeQ, expA)) <= bitSize - 1 && uniqQ.find(primeQ) == uniqQ.end()) {
                m *= (int)pow(primeQ, expA);
                uniqQ.insert(primeQ);
            }
            if (++attemptCount == 100 && sizeNum(m) != bitSize - 1) {
                m = 1;
                attemptCount = 0;
                uniqQ.clear();
            }
        }
        candidate = 2 * m + 1;
        failedMillerCount++;
    }
    return {candidate, failedMillerCount};
}

//Генерация простого с помощью теста поклингтона
pair<ull, int> pocklington_prime(int bitSize, vector<int> primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distQ(0, primes.size() - 1);
    uniform_int_distribution<> distA(1, 20);
    
    ull candidate = 1;
    int failedPocklingtonCount = -1;
    while (!pocklington_test(candidate, 9)) {
        int attemptCount = 0;
        ull f = 1;
        set<int> uniqQ;
        while (sizeNum(f) - 1 != bitSize / 2) {
            int primeQ = primes[distQ(gen)];
            int expA = distA(gen);
            if (sizeNum(f * (int)pow(primeQ, expA)) - 1 <= bitSize / 2) {
                f *= (int)pow(primeQ, expA);
                uniqQ.insert(primeQ);
            }
            if (++attemptCount == 100 && sizeNum(f) - 1 != bitSize / 2) {
                f = 1;
                attemptCount = 0;
                uniqQ.clear();
            }
        }
        ull r = f >> 1;
        if (r % 2 == 1) {
            r++;
        }
        candidate = r * f + 1;
        failedPocklingtonCount++;
    }
    return {candidate, failedPocklingtonCount};
}

//Генерация простого с помощью гост
pair<ull, int> gost_prime(int bitSize, vector<int> primes) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> distReal(0.0, 1.0);

    if (bitSize <= 1) return {0, 0};
    if (bitSize == 2) return {3, 0};

    ull p = 0;
    ull n = 0;
    ull u = 0;
    ull q = miller_prime(ceil(bitSize / 2), primes).first;
    while (true) {
        double e = distReal(gen);
        n = ceil(pow(2, bitSize - 1) / q) + ceil(pow(2, bitSize - 1) * e / q);
        if (n % 2 == 1) {
            n++;
        }

        u = 0;
        p = (n + u) * q + 1;
        if (p <= (ull)pow(2, bitSize)) {
            break;
        }
    }

    int failedGostCount = -1;
    while (!(modPow(2, p - 1, p) == 1 && modPow(2, n + u, p) != 1)) {
        u += 2;
        p = (n + u) * q + 1;
        failedGostCount++;
    }
    failedGostCount = failedGostCount == -1 ? 0 : failedGostCount;
    return {p, failedGostCount};
}