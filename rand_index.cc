#include <iostream>
#include <vector>
#include <cmath>
#include "ClusteringTools.cc"

using namespace std;


double calculateRandIndex(const vector<int>& partition1, const vector<int>& partition2) {
    int n = partition1.size();
    int a = 0, b = 0, c = 0, d = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (partition1[i] == partition1[j] && partition2[i] == partition2[j])
                ++a;
            else if (partition1[i] != partition1[j] && partition2[i] != partition2[j])
                ++b;
            else if (partition1[i] == partition1[j] && partition2[i] != partition2[j])
                ++c;
            else if (partition1[i] != partition1[j] && partition2[i] == partition2[j])
                ++d;
        }
    }


    double randIndex = static_cast<double>(a + b) / (a + b + c + d);
    return randIndex;
}

vector <int> readpart (const string filename, int d){
    vector <int> partition;
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
        }
        getline(lineStream,word,';');

        int cluster = stoi(word);

        //inicializamos el clúster al que pertenece en 0.
        partition.push_back(cluster);
    }
    return partition;
}


int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    vector<int> partition1 = readpart("output_lloyd.csv",2);
    vector<int> partition2 = readpart("output_kmeans++.csv",2);
    cout << "Calculant RandIndex ..." << endl;
    double randIndex = calculateRandIndex(partition1, partition2);
    cout << "Rand Index: " << randIndex << endl;
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
