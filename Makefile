all: lloyd kmeans rand_index


lloyd: Lloyd.cpp
	g++ -o lloyd Lloyd.cpp

kmeans: kmeans.cc
	g++ -o kmean kmeans

rand_index: rand_index.cc
	g++ -o rand_index rand_index.cc


clean:
	rm lloyd
	rm kmean
	rm rand_index
