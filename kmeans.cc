#include "ClusteringTools.cc"

using namespace std;

void Usage(){
    cout << "Usage(): ./kmeans++ filename iterations ndimensions labelled, nclusters" << endl;
    exit(-1);
}
 
void kmeanspp(vector <Point>& points, int num_clusters, int iterations, int num_dimensions){
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
    }
    

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


            Point mean;
            for (int m = 0; m < num_dimensions; ++m){
                mean.vd.push_back(sumas[l].vd[m]/puntos_x_cluster[l]);
            }  

            ant_centroids[l] = centroids[l];

            centroids[l] = mean;


        }

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
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
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

    vector<Point> points = readcsv(filename,d);

    kmeanspp(points,k,iterations,d);

    writecsv("output_kmeans++.csv",points);
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
