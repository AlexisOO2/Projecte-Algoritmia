#include "ClusteringTools.cc"
#include <utility>

using namespace std;

void Usage(){
    cout << "Usage(): ./elbow2 filename iterations ndimensions" << endl;
    exit(-1);
}

void kmeanspp(vector <Point>& points, int iterations, int num_dimensions, vector <pair<int,double> > &Elbow, int &c){
    double sumaact = -1;
    double ultimasum = -1;
    while (ultimasum/sumaact > 1.01 or c < 3) {
        vector <Point> centroids (c);
        vector <Point> ant_centroids (c);

        //el primer punt es random
        int luck = rand() % points.size();
        centroids[0].vd = points[luck].vd;
        centroids[0].cluster = 0;
        for (int i = 1; i < c; ++i){
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
        }
        
        bool convergence = false;

        for (int i = 0; i < iterations and (not convergence) ; i++){

            vector <Point> sumas (c);

            for (int j = 0; j < c; j++){
                sumas[j].vd = vector <double> (num_dimensions,0.0);
            }

            vector <int> puntos_x_cluster (c,0);
            //Calculamos la distancia entre cada punto y un cluster y lo asignamos al más próximo.
            for (int j = 0; j < points.size(); ++j){
                Point punto = points[j];

                double dist_min = INT_MAX;
                for (int k = 0; k < c; ++k){
                    double dist = punto.distance(centroids[k]);
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
            
            

            for (int l = 0; l < c; ++l){
                Point mean;
                for (int m = 0; m < num_dimensions; ++m){
                    mean.vd.push_back(sumas[l].vd[m]/puntos_x_cluster[l]);
                }  

                ant_centroids[l] = centroids[l];

                centroids[l] = mean;
                
            }

            for (int j = 0; j < c and (not convergence); ++j){
                bool change = false; 
                for (int k = 0; k < num_dimensions and not change; ++k){
                    change = ant_centroids[j].vd[k] != centroids[j].vd[k];
                }
                convergence = not change;
            }

            if (convergence) cout << "Convergencia a la iteracio " << i << endl;
        }
        double sumaelbow = 0.0;
        for (int j = 0; j < points.size(); ++j) {
            double distmin = INT_MAX;
            Point punto = points[j];
            for (int k = 0; k < c; ++k) {
                double dist = punto.distance(centroids[k]);
                if (dist < distmin) {
                    distmin = dist;
                }
            }
            sumaelbow += distmin;
        }
        ultimasum = sumaact;
        sumaact = sumaelbow;
        Elbow[c] = make_pair(c,sumaelbow);
        ++c;
    }
    int divisor = 1;
    while (Elbow[1].second > 100) {
        Elbow[1].second/= 10;
       divisor *= 10;
   }
   for (int z = 2; z < Elbow.size(); ++z) {
       Elbow[z].second = Elbow[z].second/divisor;
   }
}

void writeres(const string filename, vector <pair<int,double> > Elbow, int c) {
    ofstream outfile;
    outfile.open(filename, fstream::trunc);
    for (int i = 1; i < c; ++i) {
        outfile << '(' << Elbow[i].first << "," << Elbow[i].second << ')' <<endl;
    }
    outfile.close();
}

int main(int argc, char *argv[]) {
    string filename = ""; // file = Dataset
    int iterations; // Nº de iteracions
    int d = -1; // d = Nº Dimensiones
    bool labelled = false; //etiq = Dataset etiquetat
    int k = -1; // k = Nº Clústers

    vector <pair<int,double> > Elbow(20);
    int c = 1;

    srand(time(0));

    if (argc <= 3) Usage();
    if (argc >= 4){
            filename = argv[1];
            iterations = atoi(argv[2]);
            d = atoi(argv[3]);
    }
    if (argc >= 5) labelled = (atoi(argv[4]) == 1);

    vector<Point> points = readcsv(filename,d);

    kmeanspp(points,iterations, d, Elbow, c);

    writeres("output_elbow_kmeans++.csv", Elbow, c);
}