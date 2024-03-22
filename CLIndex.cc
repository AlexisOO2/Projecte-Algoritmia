#include "ClusteringTools.cc"

using namespace std;

void Usage(){
    cout << "Usage(): ./CLIndex filename ndimensions nclusters" << endl;
    exit(-1);
}

double Cal_Har_Index( vector < vector <Point>> &clusters, vector <Point> &centroids){
	double CH = 0.0;
	int nclusters = clusters.size();
	int ndimensions = clusters[0][0].vd.size();
	Point gcentroid;
    int total_punts = 0;

    gcentroid.vd = vector <double> (ndimensions,0.0);


    for (int j = 0; j < nclusters; ++j){
		total_punts += clusters[j].size();
    	for (int k = 0; k < clusters[j].size(); ++k){
		    for (int i = 0; i < ndimensions; ++i){
		    	gcentroid.vd[i] += clusters[j][k].vd[i];
		    }
		}
    }


    for (int i = 0; i < ndimensions; ++i){
    	gcentroid.vd[i] /= total_punts;
    }

	double WCSS = 0.0;
	double BCSS = 0.0;
	
	for (int i = 0; i < nclusters;++i){
		double wsum = 0.0;

		for (int j = 0; j < clusters[i].size(); ++j){
			wsum += clusters[i][j].distance(centroids[i]);
		}
		WCSS += wsum/clusters[i].size();
		BCSS += centroids[i].distance(gcentroid);
	}

	CH = (BCSS)/(WCSS) * ((total_punts - nclusters)/ (nclusters-1));
	
	return CH;
}

vector <vector <Point>> readclusters(const string filename, int d, int nclusters){
 	vector <vector <Point>> clusters (nclusters);

    string line,word;
    ifstream file(filename); //Abrimos el fichero de entrada
    //Leemos cada fila
    getline(file,line);
    while (getline(file, line)) {
        stringstream lineStream(line);

        Point p; // Inicializamos el punto

        // Leemos el valor de cada columna y lo guardamos en los atributos del punto.
        for (int i = 0; i < d; i++) {
                getline(lineStream, word, ';');
                p.vd.push_back(stod(word));
        }
        //Leemos el valor de la última columna que contiene el cluster al que pertenece el punto 
        getline(lineStream,word,';');

        int cluster = stoi(word);
        //Colocamos el punto en el cluster al que pertenece
        clusters[cluster].push_back(p);
    }
    return clusters;
}

vector <Point> calc_centroids(vector < vector <Point>>& clusters){
	vector <Point> centroids;
	vector <Point> sumas (clusters.size());
    for (int j = 0; j < clusters.size(); j++){
        sumas[j].vd = vector <double> (clusters[0][0].vd.size(),0.0);
    }
	for (int i = 0; i < clusters.size(); ++i){
		for (int j = 0; j < clusters[i].size(); ++j){
			for (int k = 0; k < clusters[0][0].vd.size(); ++k){
	            sumas[i].vd[k] += clusters[i][j].vd[k];
			}
		}
	}
	for (int i = 0; i < clusters.size(); ++i){
			for (int k = 0; k < clusters[0][0].vd.size(); ++k){
	            sumas[i].vd[k] /= clusters[i].size();
			}
		centroids.push_back(sumas[i]);
	}
	return centroids;
}

int main(int argc, char *argv[]){
	std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
	string filename = ""; // file = Dataset
    int d = -1; // d = Nº Dimensiones
    int k = -1; // k = Nº Clústers

    if (argc != 4) Usage();
    else {
            filename = argv[1];
            d = atoi(argv[2]);
            k = atoi(argv[3]);

    }


	vector < vector <Point>> clusters = readclusters(filename,d,k);	
	vector <Point> centroids = calc_centroids(clusters);

 
	double CH = Cal_Har_Index(clusters,centroids);
	cout <<"Calinski–Harabasz Index = " << CH << endl;
	end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}