#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};

double distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Funció per calcular la suma dels quadrats de les distàncies als centroides
double sumOfSquaredDistances(const vector<Point>& data, const vector<Point>& centroids, const vector<int>& labels) {
    double sum = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        double dist = distance(data[i], centroids[labels[i]]);
        sum += dist * dist;
    }
    return sum;
}

int main() {
    return 0;
}