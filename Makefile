all: drawgraph 

drawgraph: drawgraph.cpp 
	g++ -o drawgraph drawgraph.cpp

clean:
	rm -f drawraph drawgraph *.o
