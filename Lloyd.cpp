#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include <ctime>
#include <climits>

using namespace std;

struct Point {
    vector <double> vd; // vector de p dimensions, cada entrada representa una coordenada en una dimensió donada
    int cluster = -1;     // no default cluster
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

void Usage(){
    cout << "Usage(): ./lloyd filename iterations {ndimensions, labelled, nclusters}" << endl;
    exit(-1);
}

vector<Point> readcsv(const string filename,int num_dimensions) {
    vector<Point> points;
    string line,word;
    ifstream file(filename); //Abrimos el fichero de entrada
    //Leemos cada fila
    while (getline(file, line)) {
        stringstream lineStream(line);
        Point p; // Inicializamos el punto

        // Leemos el valor de cada columna y lo guardamos en los atributos del punto.
        for (int i = 0; i < num_dimensions; i++) {
                getline(lineStream, word, ';');
                double value = stod(word);
                p.vd.push_back(value);
        }
        //inicializamos el clúster al que pertenece en 0.
        points.push_back(p);
    }
    return points;
}



void writecsv(){

}


void lloyds_algorithm(vector <Point> points, int num_clusters, int iterations, int num_dimensions){
    vector <Point> centroids (num_clusters);


    //Escogemos los puntos que serán los centroides de cada cluster aletoriamente

    for (int i = 0; i < num_clusters; ++i){
        int luck = rand() % points.size();
        centroids[i].vd = points[luck].vd;
        centroids[i].cluster = i;
        cout << "El Punto " << luck << " es escogido como centroide del cluster " << i << endl; 
    }

    for (int i = 0; i < num_clusters; ++i){
        cout << " cluster " << centroids[i].cluster << " points: " << endl; 
        for (int j = 0; j < num_dimensions; ++j){
            cout << centroids[i].vd[j] << " ";
        }
        cout << endl;
    }

    //Calculamos la distancia entre cada punto y un cluster y lo asignamos al más próximo.
    for (int j = 0; j < points.size(); ++j){
        Point punto = points[j];

        double dist_min = INT_MAX;
        for (int k = 0; k < num_clusters; ++k){
            double dist = punto.distance(centroids[k]);
            //cout << "distancia = " << dist << " al centroide " << k << endl;

            if (dist < dist_min){
                dist_min = dist;
                points[j].cluster = k;
            }
        }

    }
}



int main(int argc, char *argv[]) {
    string filename = ""; // file = Dataset
    int iterations; // Nº de iteracions
    int d = -1; // d = Nº Dimensiones
    bool labelled = false; //etiq = Dataset etiquetat
    int k = -1; // k = Nº Clústers

    srand(time(0));

    if (argc <= 3) Usage();
    if (argc >= 4){
            filename = argv[1];
            iterations = atoi(argv[2]);
            d = atoi(argv[3]);
    }
    if (argc >= 5) labelled = (atoi(argv[4]) == 1);
    if (argc == 6) k = atoi(argv[5]);

    //if (labelled) d++; 

    vector<Point> points = readcsv(filename,d);

    lloyds_algorithm(points,k,iterations,d);

}