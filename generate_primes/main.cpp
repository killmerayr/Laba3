#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <tuple>
#include <set>

#include "algorithms.hpp"
#include "commands.hpp"

using namespace std;
typedef unsigned long long ull;

typedef pair<ull, int> (*Algorithm)(int, vector<int>);

int main() {
    vector<int> primes = eratosthenesSieve(500);

    cout << "Алгоритмы для генерации простых числе:" << endl;
    cout << "- Генерация с помощью теста Миллера - 1." << endl;
    cout << "- Генерация с помощью теста Поклингтона - 2." << endl;
    cout << "- Генерация с помощью ГОСТ - 3." << endl;
    int algorithmNum = -1;
    while (true) {
        cin >> algorithmNum;
        if (algorithmNum > 0 && algorithmNum < 4) {
            break;
        } else if (algorithmNum == 0) {
            return 0;
        }
        cout << "Неверный номер алгоритма. Попробуйте еще раз (1/2/3), или \"0\", чтобы выйти: ";
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(5, 13);

    Algorithm algorithms[] = {
        miller_prime,
        pocklington_prime,
        gost_prime
    };

    set<tuple<pair<ull, int>, bool>> primeNums;
    while (primeNums.size() != 10) {
        int num_size = dist(gen);
        pair<ull, int> result = algorithms[algorithmNum - 1](num_size, primes);
        
        bool probTest = false;
        if (algorithmNum == 1) {
            probTest = pocklington_test(result.first, 10);
        } else {
            probTest = miller_test(result.first, 10);
        }
        
        primeNums.insert({result, probTest});
    }

    cout << endl << "Таблица:" << endl;
    printTable(primeNums);
}