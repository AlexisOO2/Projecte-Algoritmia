#include "ClusteringTools.cc"

using namespace std;

void Usage(){
    cout << "Usage(): ./lloyd filename iterations ndimensions labelled, nclusters" << endl;
    exit(-1);
}

void lloyds_algorithm(vector <Point> &points, int num_clusters, int iterations, int num_dimensions){
    vector <Point> centroids (num_clusters);
    vector <Point> ant_centroids (num_clusters);



    //Escogemos los puntos que serán los centroides de cada cluster aletoriamente
    for (int i = 0; i < num_clusters; ++i){
        int luck = rand() % points.size();
        centroids[i].vd = points[luck].vd;
        centroids[i].cluster = i;
        //cout << "El Punto " << luck << " es escogido como centroide del cluster " << i << endl; 
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
            /*
            cout << "(";

            for (int m = 0; m < num_dimensions; ++m){
                cout << mean.vd[m];
                if (m == 0) cout  << ",";
            }
            cout << ")" << " [" << i << "]"<< endl;
            */
        }
        //cout << endl;

        for (int j = 0; j < num_clusters and (not convergence); ++j){
            bool change = false; 
            for (int k = 0; k < num_dimensions and not change; ++k){
                change = ant_centroids[j].vd[k] != centroids[j].vd[k];
            }
            convergence = not change;
        }

        if (convergence) cout << "Convergencia a la iteracio " << i << endl;
    }
    //elbow
    double sumaelbow = 0.0;
    for (int j = 0; j < points.size(); ++j) {
        double distmin = INT_MAX;
        Point punto = points[j];
        for (int k = 0; k < num_clusters; ++k) {
            double dist = punto.distance(centroids[k]);
               if (dist < distmin) {
                   distmin = dist;
               }
        }
        sumaelbow += distmin;
    }
    cout << sumaelbow <<endl;
}




int main(int argc, char *argv[]) {
    string filename = ""; // file = Dataset
    int iterations; // Nº de iteracions
    int d = -1; // d = Nº Dimensiones
    bool labelled = false; //etiq = Dataset etiquetat
    int k = -1; // k = Nº Clústers
    //double sumaelbow = 0.0;

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

    /*
    for (int i = 0; i < 10; ++i){
        cout << "Punt " << i << " = ";

        for (int j = 0; j < d; ++j){
            cout << points[i].vd[j] << " ";
        }
        cout << endl;
    }
    */
    lloyds_algorithm(points,k,iterations,d);

    writecsv("output_lloyd.csv",points);

} 
