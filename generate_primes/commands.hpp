#pragma once
#include <vector>
#include <set>
#include <tuple>
#include <utility>

using namespace std;
typedef unsigned long long ull;

vector<int> eratosthenesSieve(int num);
vector<pair<int, int>> factorize(ull num);
int modPow(ull a, ull exp, ull m);
int sizeNum(ull n);
void printTable(set<tuple<pair<ull, int>, bool>> data);
