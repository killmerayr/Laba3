#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Функция моделирования остывания кофе
vector<double> coffee(double Tk, double Tsr, double r, int totalMinutes) {
    vector<double> temperatures;
    for (int t = 0; t <= totalMinutes; ++t) {
        double T = Tsr + (Tk - Tsr) * exp(-r * t);
        temperatures.push_back(T);
    }
    return temperatures;
}

// Функция вывода результатов
void printResults(int totalMinutes, const vector<double>& temperatures) {
    cout << "Результаты моделирования остывания кофе:\n";
    cout << "----------------------------------------\n";
    cout << "|  Время (мин)  |  Температура (°C)  |\n";
    cout << "----------------------------------------\n";
    for (int t = 0; t <= totalMinutes; ++t) {
        cout << "|" << setw(10) << t << setw(7) << " |"
             << setw(14) << fixed << setprecision(2) << temperatures[t] << setw(8) << " |\n";
    }
    cout << "----------------------------------------\n";
}

int main() {
    double Tk = 0;
    double Tsr = 0;
    double r = 0;
    int totalMinutes = 0;

    cout << "Введите начальную температуру кофе (в градусах цельсия): ";
    cin >> Tk;

    cout << "Введите температуру окружающей среды (в градусах цельсия): ";
    cin >> Tsr;

    cout << "Введите коэффициент охлаждения (0 < r < 1): ";
    cin >> r;

    cout << "Введите время наблюдения (в минутах): ";
    cin >> totalMinutes;

    vector<double> temperatures = coffee(Tk, Tsr, r, totalMinutes);
    printResults(totalMinutes, temperatures);
}