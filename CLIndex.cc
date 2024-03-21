#include "ClusteringTools.cc"

using namespace std;


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
    	cout << gcentroid.vd[i] << ",";
    }
    cout << endl;

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