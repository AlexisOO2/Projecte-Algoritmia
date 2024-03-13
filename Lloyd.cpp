#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>

using namespace std;

//Este algoritmo de momento es de 2 dimensiones

struct Point {
    double x, y;     // coordinates
    int cluster;     // no default cluster
    double minDist;  // default infinite dist to nearest cluster

    Point() : 
        x(0.0), 
        y(0.0),
        cluster(-1),
        minDist(__DBL_MAX__) {}
        
    Point(double x, double y) : 
        x(x), 
        y(y),
        cluster(-1),
        minDist(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

void lloyd_clustering(vector <Point> vpoints, int k, int max_it){

}

int main(int argc, char const *argv[])
{
	Point P1 = Point(0.0,0.0);
	Point P2 = Point(1.0,1.0);
	Point P3 = Point(1.0,-1.0);
	Point P4 = Point(-1.0,1.0);
	Point P5 = Point(-1.0,-1.0);

	vector <Point> vpoints = {P1,P2,P3,P4,P5};



	return 0;
}

