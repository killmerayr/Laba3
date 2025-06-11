#pragma once
#include <vector>
#include <utility>

using namespace std;
typedef unsigned long long ull;

// Тест Миллера
bool miller_test(ull n, int t);

// Тест Поклингтона
bool pocklington_test(ull n, int t);

// Генерация простого числа с помощью теста Миллера
pair<ull, int> miller_prime(int num_size, vector<int> primes);

// Генерация простого числа с помощью теста Поклингтона
pair<ull, int> pocklington_prime(int num_size, vector<int> primes);

// Генерация простого числа по ГОСТ
pair<ull, int> gost_prime(int num_size, vector<int> primes);
