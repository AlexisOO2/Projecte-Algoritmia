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

    // Calcula la distància eucladiana al quadrat entre el punt i un altre punt.
    double distance(Point p) {
        double dist = 0.0;
        for (int i = 0; i < p.d.size(); i++) {
            dist += (p.d[i] - d[i]) * (p.d[i] - d[i]);
        }
        return dist;
    }
};

//leer fichero csv separado por ";".
vector<Point> readcsv(const string filename, int num_dimensions) {
    vector<Point> points;
    string line,word;
    ifstream file(filename); //Abrimos el fichero de entrada
    bool seen = false;
    //Leemos cada fila
    while (getline(file, line)) {
        stringstream lineStream(line);
        Point p; // Inicializamos el punto

        // Leemos el valor de cada columna y lo guardamos en los atributos del punto.
        for (int i = 0; i < num_dimensions; i++) {
                getline(lineStream, word, ';');
                double value = stod(word);
                p.vd.push_back(value);
                if (not seen) cout << value;
        }
        //inicializamos el clúster al que pertenece en 0.
        if (not seen) cout << endl;
        p.cluster = -1;

        if (not seen){
            for (int i = 0; i < num_dimensions; ++i) cout << p.vd[i] << " ";
            cout << endl;
            seen = true;
        }   
        points.push_back(p);
    }
    return points;
}
