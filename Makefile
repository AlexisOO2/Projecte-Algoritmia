all: lloyd kmeans++ rand_index CLIndex elbow1 elbow2


CFLAGS = -g

lloyd: Lloyd.cpp ClusteringTools.cc
	g++ $(CFLAGS) -o lloyd Lloyd.cpp

kmeans++: kmeans.cc ClusteringTools.cc
	g++ $(CFLAGS) -o kmeans++ kmeans.cc

rand_index: rand_index.cc ClusteringTools.cc
	g++ $(CFLAGS) -o rand_index rand_index.cc

CLIndex: CLIndex.cc ClusteringTools.cc
	g++ $(CFLAGS) -o CLIndex CLIndex.cc

elbow1: elbow.cpp
	g++ $(CFLAGS) -o elbow1 elbow.cpp

elbow2: elbow2.cpp
	g++ $(CFLAGS) -o elbow2 elbow2.cpp

clean:
	rm lloyd
	rm kmeans++
	rm rand_index
	rm CLIndex
	rm elbow1
	rm elbow2
