#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
using ll = long long;

double compute_sum(int power, int base, int iterations = 1000) {
    double sum = 0;
    for (int n = 1; n <= iterations; n++) {
        sum += pow(n, power) / pow(base, n);
    }
    return sum;
}

vector<double> is_rational(double value, double epsilon) {  
    double denom = 1;
    double numer = 1;
    double diff = abs(value - (numer / denom));
    int tries = 0;

    while (tries != 100) {
        if (numer / denom < value) {
            numer++;
        } else {
            denom++;
        }
        diff = abs(value - (numer / denom));
        tries++;
        if (diff < epsilon) {
            return {numer, denom, 1};
        }
    }
    return {numer, denom, 0};
}

int main() {
    int power = 1;
    int base = 1;
    cout << "Введите свои a и b: ";
    cin >> power >> base;

    if (base == 1) {
        cout << "Infinity" << endl;
    } else {
        double sum = compute_sum(power, base);
        double epsilon = 1e-10;

        vector<double> result = is_rational(sum, epsilon);

        if (!result[2]) {
            cout << "Irrational" << endl;
        } else {
            cout << result[0] << " / " << result[1];
        }
    }
}