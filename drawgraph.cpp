// Copyright (C) 2011 David C. Haws

//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// See LICENSE

// This program will read in the number of nodes followed by the
// adjacency matrix of a graph. It will print out pstricks code for the graph.

// Usage:
// drawgraph < inputfile > outputfile
//      or
// drawgraph -i inputfile -o outpufile
//      or a combination
// options:
//      -i <inputfilename>
//      -o <outputfilename>
//      -H <Write latex header>
//      -P <Write pstrick header>   If -H, then -P is also set
//      -n <nodenamefilename>
//      -c <nodepositionfilename>

#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
#include <string>

using namespace std;

double arrowSep = 0.17;
double stateGraphRadius = 8.5;
double labelRadiusEpsilon = 0.5;
double degreeCountRadiusEpsilon = labelRadiusEpsilon + 0.4;
double nodeSize = 0.1;
double angleEpsilon = 5;
string standaloneborder = "1cm";

string lineWidth = "1.5pt";
string arrowSize = "9pt";
string arrowLength = "1.5";

double gridSizex = (stateGraphRadius + labelRadiusEpsilon)*2 + 1.0;
double gridSizey = (stateGraphRadius + labelRadiusEpsilon)*2 + 1.0;

double xOffset = gridSizex/2;
double yOffset = gridSizey/2;

double nodeNameScalex = 1.0;
double nodeNameScaley = 1.0;

double nodeNameOffsetx =  0.3;
double nodeNameOffsety =  0.3;

string undirectedEdgeColor = "black";
string directedEdgeColor = "red";

string arrowDrawColor="black";
int numArrowDrawColors = 4;
string arrowDrawColors[] = {"red","blue", "green", "yellow"};



int main(int argc, char **argv)
{
    int outputLatexHeader = 0;
    int outputpstricksHeader = 0;
    int readNodeNames = 0;
    int readPositions = 0;
    string nodeNameFileName = "";
    string positionsFileName = "";
    string inputFileName = "";
    string outputFileName = "";

    if (argc <= 0) {
        cout << "Error message goes here." << endl;
        exit(0);

    }

    ostream *someOutput;
    ofstream outputFile;
    ifstream nodeNamesFile;
    ifstream positionsFile;


    if (argc > 1 )
    {
        for (int i=1;i<argc;i++)
        {
            string tempS = argv[i];
            //*someOutput << argv[i] << endl;
            if (tempS == "-H")
            {
                outputLatexHeader = 1;
                outputpstricksHeader = 1;
            }
            if (tempS == "-P")
            {
                outputpstricksHeader = 1;
            }
            if (tempS == "-i")
            {
                inputFileName  = argv[i+1];
                i++;
            }
            if (tempS == "-o")
            {
                outputFileName  = argv[i+1];
                i++;
            }
            if (tempS == "-n")
            {
                readNodeNames = 1;
                nodeNameFileName = argv[i+1];
                i++;
            }
            if (tempS == "-c")
            {
                readPositions = 1;
                positionsFileName = argv[i+1];
                i++;
            }
            if (tempS == "--nodesize")
            {
                sscanf(argv[i+1],"%lf",&nodeSize);
                i++;
            }
            if (tempS == "--textsize")
            {
                sscanf(argv[i+1],"%lf",&nodeNameScalex);
                nodeNameScaley=nodeNameScalex;
                i+=2;
            }
            if (tempS == "--nodetextoffset")
            {
                sscanf(argv[i+1],"%lf",&nodeNameOffsetx);
                sscanf(argv[i+2],"%lf",&nodeNameOffsety);
                i+=2;
            }
        }
    }

    if (outputFileName == "")
    {
        someOutput = &cout;
    }
    else 
    {
        outputFile.open(outputFileName.c_str());
        if (!outputFile.is_open())
        {
            cout << "Can not open " << outputFileName << endl;
        }
        someOutput = &outputFile;
    }



    
    istream *someInput;
    ifstream inputFile;

    if (inputFileName == "")
    {
        someInput = &cin;
    }
    else 
    {
        inputFile.open(inputFileName.c_str());
        if (!inputFile.is_open())
        {
            *someOutput << "Can not open " << inputFileName << endl;
        }
        someInput = &inputFile;
    }

    int numNodes;
    *someInput >> numNodes;

    int adjMat[numNodes][numNodes];
    for (int i=0;i<numNodes;i++)
    {
        for (int j=0;j<numNodes;j++)
        {
            *someInput >> adjMat[i][j];
        }
    }


    double xStates[numNodes];
    double yStates[numNodes];

    if (readPositions == 1)
    {
        positionsFile.open(positionsFileName.c_str());
        if (!positionsFile.is_open())
        {
            cerr << "Could not open " << positionsFileName << endl;
            exit(0);
        }
        positionsFile >> gridSizex;
        positionsFile >> gridSizey;
        for (int i=0;i<numNodes;i++)
        {
            positionsFile >> xStates[i];
            positionsFile >> yStates[i];
        }
        positionsFile.close();
    }
    else
    {
        for (int i=0;i<numNodes;i++)
        {
            xStates[i] = stateGraphRadius*cos(2*i*M_PI/(double)numNodes) + xOffset;
            yStates[i] = stateGraphRadius*sin(2*i*M_PI/(double)numNodes) + yOffset;
        }
    }

    string nodeNames[numNodes];
    if (readNodeNames == 1)
    {
        nodeNamesFile.open(nodeNameFileName.c_str());
        if (!nodeNamesFile.is_open())
        {
            cerr << "Could not open " << nodeNameFileName << endl;
            exit(0);
        }
        for (int i=0;i<numNodes;i++)
        {
            nodeNamesFile >> nodeNames[i];
        }
        nodeNamesFile.close();
    }
    else
    {
        char buff[100];
        for (int i=0;i<numNodes;i++)
        {
            sprintf(buff,"%d",i);
            nodeNames[i] = buff;
        }
    }

    if (outputLatexHeader == 1)
    {
        *someOutput << "\\documentclass[preview=true,pstricks=true,border=" << standaloneborder << "]{standalone}" << endl;
        //*someOutput << "\\textwidth 8in" << endl;
        //*someOutput << "\\textheight 10in" << endl;
        //*someOutput << "\\voffset -1.2in" << endl;
        //*someOutput << "\\hoffset -1.6in " << endl;
        //*someOutput << "\\usepackage[landscape]{geometry}" << endl;
        *someOutput << "\\usepackage{pstricks}" << endl;
        *someOutput << "\\usepackage{color}" << endl;
        *someOutput << "\\pagestyle{empty}" << endl;
        *someOutput << "\\begin{document}" << endl;
        //*someOutput << "\\begin{center}" << endl;
    }
    if (outputpstricksHeader == 1)
    {
        *someOutput << "\\begin{pspicture}(" << gridSizex << "," << gridSizey << ")" << endl;
//        *someOutput << "\\psgrid" << endl;
    }

    // Draw undirected edges
    for (int i=0;i<numNodes;i++)
    {
        for (int j=0;j<numNodes;j++)
        {
            if (adjMat[i][j] == 1 && adjMat[j][i] == 1)
            {
                *someOutput << "\\psline[linecolor=" << undirectedEdgeColor << ",linewidth=" << lineWidth << "](";
                *someOutput << xStates[i] << "," << yStates[i] << ")";
                *someOutput << "(" << xStates[j] << "," << yStates[j] << ")";
                *someOutput << endl;
            }
        }
    }

    // Draw directed edges
    for (int i=0;i<numNodes;i++)
    {
        for (int j=0;j<numNodes;j++)
        {
            if (adjMat[i][j] == 1 && adjMat[j][i] == 0)
            {
                *someOutput << "\\psline[linecolor=" << directedEdgeColor << ",linewidth=" << lineWidth;
                *someOutput << ",arrowsize=" << arrowSize << ",arrowlength=" << arrowLength << "]{->}(";
                *someOutput << xStates[i] << "," << yStates[i] << ")";
                *someOutput << "(" << (xStates[i]*0.4 + xStates[j]*0.6) << "," << (yStates[i]*0.4 + yStates[j]*0.6) << ")";

                *someOutput << "\\psline[linecolor=" << directedEdgeColor << ",linewidth=" << lineWidth;
                *someOutput <<"](";
                *someOutput << (xStates[i]*0.5 + xStates[j]*0.5) << "," << (yStates[i]*0.5 + yStates[j]*0.5) << ")";
                *someOutput << "(" << xStates[j] << "," << yStates[j] << ")";
                *someOutput << endl;
            }
        }
    }

    // Draw the nodes for the graph.
    for (int i=0;i<numNodes;i++)
    {
        *someOutput << "\\pscircle*[linecolor=black](";
        *someOutput << xStates[i];
        *someOutput << ",";
        *someOutput << yStates[i];
        *someOutput << "){" << nodeSize << "}" << endl;


        *someOutput << "\\rput(";
        *someOutput << xStates[i] + nodeNameOffsetx;
        *someOutput << ",";
        *someOutput << yStates[i] + nodeNameOffsety;
        *someOutput << "){\\psscalebox{" << nodeNameScalex << " " << nodeNameScaley << "}{" << nodeNames[i] << "}}" << endl;
    }



    if (outputpstricksHeader == 1)
    {
        *someOutput << "\\end{pspicture}" << endl;
    }
    if (outputLatexHeader == 1)
    {
        //*someOutput << "\\end{center}" << endl;
        *someOutput << "\\end{document}" << endl;
    }

    exit(1);
}
