all: lloyd kmeans rand_index


CFLAGS = -g -Wall

lloyd: Lloyd.cpp
	g++ $(CFLAGS) -o lloyd Lloyd.cpp

kmeans: kmeans.cc
	g++ $(CFLAGS) -o kmean kmeans

rand_index: rand_index.cc
	g++ $(CFLAGS) -o rand_index rand_index.cc


clean:
	rm lloyd
	rm kmean
	rm rand_index
