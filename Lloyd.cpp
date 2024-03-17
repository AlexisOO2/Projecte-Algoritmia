#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 

using namespace std;

struct Point {
    vector <double> vd; // vector de p dimensions, cada entrada representa una coordenada en una dimensió donada
    int cluster;     // no default cluster
    double minDist;  // default infinite dist to nearest cluster

    // Calcula la distància eucladiana al quadrat entre el punt i un altre punt.
    double distance(Point p) {
        double dist = 0.0;
        for (int i = 0; i < p.vd.size(); i++) {
            dist += (p.vd[i] - vd[i]) * (p.vd[i] - vd[i]);
        }
        return dist;
    }
};

/**
 * Reads in the data.csv file into a vector of points
 * @return vector of points
 *
 */

void Usage(){
    cout << "Usage(): ./lloyd filename iterations {ndimensions, labelled, nclusters}" << endl;
    exit(-1);
}

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



int main(int argc, char *argv[]) {
    string filename = ""; // file = Dataset
    int iterations; // Nº de iteracions
    int d = -1; // d = Nº Dimensiones
    bool labelled = false; //etiq = Dataset etiquetat
    int k = -1; // k = Nº Clústers

    if (argc <= 3) Usage();
    if (argc >= 4){
            filename = argv[1];
            iterations = atoi(argv[2]);
            d = atoi(argv[3]);
    }
    if (argc >= 5) labelled = (atoi(argv[4]) == 1);
    if (argc == 6) k = atoi(argv[5]);

    if (labelled) d++; 

    vector<Point> points = readcsv(filename,d);

    for (int i = 0; i < 10; ++i){
        cout << "Punto " << i <<" cluster = " << points[i].cluster << " points: "; 
        for (int j = 0; j < d; ++j){
            Point aux = points[i];
            cout << points[i].vd[j] << " ";
        }
        cout << endl;
    }

}