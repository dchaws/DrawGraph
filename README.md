
I got tired of drawing graphs that have both directed and undirected edges. So
I wrote this simple program that reads in the adjacency matrix of a graph and
writes pstricks code to draw the graph.

The input should be a file with the number of nodes followed by the adjacency
graph. For example, Examples/mat8.txt

    5
    0 1 0 0 0
    1 0 0 1 0
    0 1 0 1 0
    0 0 1 0 0
    1 0 0 1 0

## What can it do?

Input is adjacency graph.

 17
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 
 0 0 1 0 0 0 0 0 0 0 0 1 0 0 0 0 0 
 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 
 0 0 1 0 1 0 0 0 0 0 0 0 0 1 0 0 1 
 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 
 0 0 0 0 0 0 1 0 0 0 1 0 0 0 0 0 0 
 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 
 0 0 0 0 0 0 1 1 0 0 0 0 0 0 0 0 1 
 1 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 
 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 
 0 0 0 1 1 0 0 0 0 0 0 0 0 0 0 0 0 
 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 
 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 

Optional is are the node names, and positions.

    ./drawgraph --textsize 2 --nodesize 0.2 --nodetextoffset -0.5 0.5 -H -n Examples/mat15_names.txt -c Examples/mat15_positions.txt -i Examples/mat15.txt > Examples/mat15.tex
    cd Examples
    latex mat15.tex;dvipdf mat15.dvi

![](https://raw.github.com/dchaws/DrawGraph/master/Examples/mat15.png)

## Simple Usage
Simple usage:

    ./drawgraph < Examples/mat8.txt > Examples/mat8.tex

The program will draw undirected edges with black and directed edges will be
drawn in red with an arrow. See Examples/mat*.pdf

## Input File
By default the program drawgraph reads in from standard input and writes to
standard output. You can also use -i and -o to control the input and output.
E.g.

    ./drawgraph -i Examples/mat8.txt -o Examples/mat8.tex

## Pstricks and Latex headers
By default the program only writes the pstricks part. But, you can have it
print the pspicture environment tags with -P, or have it print the pspicture
and latex header and tail information with -H.

    ./drawgraph -P < Examples/mat8.txt > Examples/mat8.tex

    ./drawgraph -H < Examples/mat8.txt > Examples/mat8.tex

You must use latex and not pdflatex.

## Drawing all examples
To draw all the example graphs:

    cd Examples
    for i in mat*.txt;do ../drawgraph -H < $i > ${i/txt/tex};latex ${i/txt/tex};dvipdf ${i/txt/dvi};done

## Edge-edge adjacency to vertex-vertex adjacency
The program arr2mat is a utility to convert a list of directed edges to
an adjacency matrix format.

For example, the file Example/testarrows.txt contains

    5
    0 1
    4 2
    0 3

The first line is the number of nodes in total. Each line is a
ordered pair of adjacencies. I.e. 0->1, 4->2.

The output of arr2mat can be piped directly to drawgraph.

    ./arr2mat < Examples/testarrows.txt | ./drawgraph -H

or

    ./drawgraph -H < <(./arr2mat < Examples/testarrows.txt) 

## Reading in node names and positions

Added option to read in node names. Node names are given one per line.

    ./drawgraph -H -n Examples/mat1_names.txt < Examples/mat1.txt

Added option to read in positions of the nodes. First two numbers in the position
file are the grid size. The remaining numbers are the (x,y) pairs.

    ./drawgraph -H -n Examples/mat1_names.txt -c Examples/mat1_positions.txt < Examples/mat1.txt

Added option to read in the (x,y) offset for the node names.

    ./drawgraph --nodetextoffset 0.1 0.3 -H -n Examples/mat1_names.txt -c Examples/mat1_positions.txt

## Updates 

6/4/2013
1. Now uses standalone package to draw just the graph.
2. Added --nodetextoffset option.
