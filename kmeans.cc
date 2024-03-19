#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include <ctime>
#include <climits>
#include <cmath>

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
        return sqrt(dist);
    }


};

void Usage(){
    cout << "Usage(): ./lloyd filename iterations ndimensions {labelled, nclusters}" << endl;
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
                double value = 1000*stod(word);
                p.vd.push_back(value);
        }
        //inicializamos el clúster al que pertenece en 0.
        points.push_back(p);
    }
    return points;
}



void writecsv(const string filename, vector<Point> points) {

    ofstream outfile;
    outfile.open(filename, fstream::trunc);

    for (int i = 0; i < points.size(); ++i){
        for (int j = 0; j < points[0].vd.size(); j++){
            outfile << points[i].vd[j];
            if (j != points[0].vd.size()-1) outfile << ";";
            else outfile << "; " << points[i].cluster;
        }
        outfile << endl;
    }
    outfile.close();
}


void lloyds_algorithm(vector <Point> points, int num_clusters, int iterations, int num_dimensions){
    vector <Point> centroids (num_clusters);
    vector <Point> ant_centroids (num_clusters);

    //el primer punt es random
    int luck = rand() % points.size();
    centroids[0].vd = points[luck].vd;
    centroids[0].cluster = 0;
    for (int i = 1; i < num_clusters; ++i){
        double distmax = 0.0;
        int centnew;
        for (int j = 0; j < points.size(); ++j) {
            Point punto = points[j];
            int distmin = INT_MAX;
            int centproper = 0;
            for (int k = 0; k < i; ++k) {
                //calculem el cluster mes proper a un punt sobre els cluster que tenim
                double dist = punto.distance(centroids[k]);
                if (dist < distmin) {
                    distmin = dist;
                    centproper = k;
                }
            }
            //actualitzem distancia maxima com la distancia més llunyana d'un punt al cluster més proper
            double dist2 = punto.distance(centroids[centproper]);
            if (dist2 > distmax) {
                distmax = dist2;
                centnew = j;
            }
        }
        centroids[i].vd = points[centnew].vd;
        centroids[i].cluster = i;
       // cout << "centroide " << centnew << "  nou centroide iteracio " << i <<endl; 
    }

    
    /*
    for (int i = 0; i < num_clusters; ++i){
        cout << "Cluster " << centroids[i].cluster << " points: " << endl; 
        for (int j = 0; j < num_dimensions; ++j){
            cout << centroids[i].vd[j] << " ";
        }
        cout << endl;
    }
    */
    

    bool convergence = false;

    for (int i = 0; i < iterations and (not convergence) ; i++){

        vector <Point> sumas (num_clusters);

        for (int j = 0; j < num_clusters; j++){
            sumas[j].vd = vector <double> (num_dimensions,0.0);
        }

        vector <int> puntos_x_cluster (num_clusters,0);
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

            puntos_x_cluster[points[j].cluster] +=1;

            for (int n = 0; n < num_dimensions; n++) {
                sumas[points[j].cluster].vd[n] += points[j].vd[n];
            }
        }
        
        

        for (int l = 0; l < num_clusters; ++l){
            //cout <<"cluster " << l << " tiene: " << endl;
            //cout << puntos_x_cluster[l] << " puntos, su suma es igual a: ";

            //for (int m = 0; m < num_dimensions; ++m) cout << sumas[l].vd[m]  << " ";
            //cout << "y su mean es ";

            Point mean;
            for (int m = 0; m < num_dimensions; ++m){
                mean.vd.push_back(sumas[l].vd[m]/puntos_x_cluster[l]);
            }  

            ant_centroids[l] = centroids[l];

            centroids[l] = mean;

            cout << "(";

            for (int m = 0; m < num_dimensions; ++m){
                cout << mean.vd[m];
                if (m == 0) cout  << ",";
            }
            cout << ")" << " [" << i << "]"<< endl;
        }
        cout << endl;

        for (int j = 0; j < num_clusters and (not convergence); ++j){
            bool change = false; 
            for (int k = 0; k < num_dimensions and not change; ++k){
                change = ant_centroids[j].vd[k] != centroids[j].vd[k];
            }
            convergence = not change;
        }

        if (convergence) cout << "Convergencia a la iteracio " << i << endl;
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

    writecsv("output_Lloyd.csv",points);
}
