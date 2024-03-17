#include <iostream>
#include <vector>
#include <cmath>


using namespace std;


double calculateRandIndex(const vector<int>& partition1, const vector<int>& partition2) {
    int n = partition1.size();
    int a = 0, b = 0, c = 0, d = 0;


    // Calculating values of a, b, c, and d
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (partition1[i] == partition1[j] && partition2[i] == partition2[j])
                ++a;
            else if (partition1[i] != partition1[j] && partition2[i] != partition2[j])
                ++b;
            else if (partition1[i] == partition1[j] && partition2[i] != partition2[j])
                ++c;
            else if (partition1[i] != partition1[j] && partition2[i] == partition2[j])
                ++d;
        }
    }


    // Calculating Rand Index
    double randIndex = (a + b) / static_cast<double>((n * (n - 1)) / 2);
    return randIndex;
}

/*
int main() {
    // Exemple de dues particions (els nombres representen els clústers)
    vector<int> partition1 = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4};
    vector<int> partition2 = {0, 0, 1, 1, 2, 2, 3, 4, 4, 4};


    double randIndex = calculateRandIndex(partition1, partition2);
    cout << "Rand Index: " << randIndex << endl;


    return 0;
}
*/
