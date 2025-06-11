#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int countNumbers, maxTake;
    cout << "Введите количество чисел и маскисмальное количество чисел за ход: ";
    cin >> countNumbers >> maxTake;

    cout << "Введите " << countNumbers << " целых чисел: ";
    vector<int> sequence(countNumbers);
    for (int &element : sequence){
        cin >> element;
    }

    vector<int> prefixSum(countNumbers + 1, 0);
    for (int idx = 0; idx < countNumbers; ++idx) {
        prefixSum[idx + 1] = prefixSum[idx] + sequence[idx];
    }

    vector<int> dpt(countNumbers + 1, 0);

    for (int pos = countNumbers - 1; pos >= 0; pos--) {
        int maxDiff = -1000000000;
        for (int take = 1; take <= maxTake && pos + take <= countNumbers; take++) {
            int sumTaken = prefixSum[pos + take] - prefixSum[pos];
            maxDiff = max(maxDiff, sumTaken - dpt[pos + take]);
        }
        dpt[pos] = maxDiff;
    }

    if (dpt[0] > 0) {
        cout << "1 - Победил Павел" << endl;
    } else {
        cout << "0 - Победила Вика" << endl;
    }
}