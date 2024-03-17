all: lloyd kmeans rand_index


CFLAGS = -g -Wall

lloyd: Lloyd.cpp
	g++ -o $(CFLAGS) lloyd Lloyd.cpp

kmeans: kmeans.cc
	g++ -o $(CFLAGS) kmean kmeans

rand_index: rand_index.cc
	g++ -o $(CFLAGS) rand_index rand_index.cc


clean:
	rm lloyd
	rm kmean
	rm rand_index
