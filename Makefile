all: drawgraph 

drawgraph: drawmovegraph.cpp 
	g++ -o drawgraph drawgraph.cpp

clean:
	rm -f drawraph drawgraph *.o
