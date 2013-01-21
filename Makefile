all: drawgraph arr2mat

drawgraph: drawgraph.cpp 
	g++ -o drawgraph drawgraph.cpp

arr2mat: arr2mat.cpp 
	g++ -o arr2mat arr2mat.cpp

clean:
	rm -f drawraph arr2mat *.o
