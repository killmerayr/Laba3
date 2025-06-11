#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <set>

using namespace std;
using ull = unsigned long long;

vector<int> eratosthenesSieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= limit; p++) {
        if (is_prime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime[i] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

vector<pair<int, int>> factorize(ull num) { 
    vector<pair<int, int>> result;
    vector<int> primes = eratosthenesSieve(500);
    
    for (auto& primeElm : primes) {
        int exponent = 0;
        while (num % primeElm == 0 && num > 0) {
            exponent++;
            num /= primeElm;
        }
        if (exponent) {
            result.push_back({primeElm, exponent});
        }
    }

    return result;
}

int modPow(ull a, ull exp, ull m) {
    int res = 1;
    int base = a % m;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % m;
        }
        base = (base * base) % m;
        exp >>= 1;
    }
    return res;
}

int sizeNum(ull n) {
    return (int)log2(n);
}

void printTable(set<tuple<pair<ull, int>, bool>> data) {
    int colWidth = 15;
    for (auto& elm : data) {
        cout << setw(colWidth) << left << get<0>(elm).first;
    }
    cout << endl;

    for (auto& elm : data) {
        if (get<1>(elm)) {
            cout << setw(colWidth) << left << "+";
        } else {
            cout << setw(colWidth) << left << "-";
        }
    }
    cout << endl;

    for (auto& elm : data) {
        cout << setw(colWidth) << left << get<0>(elm).second;
    }
    cout << endl;
}