// source: https://reasonabledeviations.com/2019/10/02/k-means-in-cpp/#writing-to-a-file
#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>

using namespace std;

// Representació d'un datapoint.
struct Point {
    vector <double> d; // vector de p dimensions, cada entrada representa una coordenada en una dimensió donada
    int cluster;     // no default cluster
    double minDist;  // default infinite dist to nearest cluster

    Point() : 
        x(0.0), 
        y(0.0),
        cluster(-1),
        minDist(__DBL_MAX__) {}
        
    Point(double x, double y) : 
        x(x), 
        y(y),
        cluster(-1),
        minDist(__DBL_MAX__) {}

    // Calcula la distància eucladiana al quadrat entre el punt i un altre punt.
    double distance(Point p) {
        double dist = 0.0;
        for (int i = 0; i < p.d.size(); i++) {
            dist += (p.d[i] - d[i]) * (p.d[i] - d[i]);
        }
        return dist;
    }
};

// Llegir d'un fitxer CSV. Retorna un vector de punts.
vector<Point> readcsv(const string name_file) {
    vector<Point> points;
    string line;
    ifstream file(name_file);

    // Llegir la primera línia per determinar el número de dimensions dels punts del dataset.
    getline(file, line);
    stringstream headerStream(line);
    int num_dimensions = 0;
    string header;
    while (getline(headerStream, header, ',')) 
        num_dimensions++;
    
    // Llegir la resta de línies.
    while (getline(file, line)) {
        stringstream lineStream(line);
        double value;
        Point p(0.0, 0.0, ...); // Initialize Point with num_dimensions zeros

        // Read values and populate Point object
        for (int i = 0; i < num_dimensions; i++) {
            if (getline(lineStream, header, ',') && stof(header, &value)) 
                p.d.push_back(value);
            else {
                cerr << "Error: Invalid data format in line: " << line << endl;
                break; // Skip to next line on error
            }
        }
        points.push_back(p);
    }
    return points;
}