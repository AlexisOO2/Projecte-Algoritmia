#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string> 
#include <cstdlib> 
#include <ctime>
#include <climits>
#include <cmath>
#include <algorithm>

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

    //Operación que 
    bool operator == (Point const& p){
    	bool equal = true;
    	if (this->vd.size() != p.vd.size()) equal = false;
    	else {
    		for (int i = 0; i < this->vd.size() and equal; ++i){
                equal = this->vd[i] == p.vd[i];
            }
    	} 
        return equal;
    }

};

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
                replace( word.begin(), word.end(), ',', '.');
                double value = 1000*stod(word);
                p.vd.push_back(value);
        }
        //inicializamos el clúster al que pertenece en 0.
        points.push_back(p);
    }
    return points;
}

    // output: un fitxer csv igual que el Dataset d'on provenen les dades amb una columna més per assignar el cluster corresponent.
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