// DrawStateMoveGraphs is for drawing state and move graphs of Markov chains.
// Copyright (C) 2012 David C. Haws

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

// Utility to convert arrows to adjacency matrix

#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector <string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector <string> split(const string &s, char delim) {
    vector<string> elems;
    return split(s, delim, elems);
}

int main(int argc, char **argv)
{
    string inputFileName = "";
    string outputFileName = "";
    ostream *someOutput;
    ofstream outputFile;

    if (argc <= 0) {
        cout << "Error message goes here." << endl;
        exit(0);

    }

    if (argc > 1 )
    {
        for (int i=1;i<argc;i++)
        {
            string tempS = argv[i];
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
        }
    }

    if (outputFileName == "")
        someOutput = &cout;
    else 
    {
        outputFile.open(outputFileName.c_str());
        if (!outputFile.is_open())
            cout << "Can not open " << outputFileName << endl;

        someOutput = &outputFile;
    }

    istream *someInput;
    ifstream inputFile;

    if (inputFileName == "")
        someInput = &cin;
    else 
    {
        inputFile.open(inputFileName.c_str());
        if (!inputFile.is_open())
            *someOutput << "Can not open " << inputFileName << endl;

        someInput = &inputFile;
    }

    int numNodes;
    *someInput >> numNodes;
    // Clear newline
    string input;
    getline(*someInput,input);

    int adjMat[numNodes][numNodes];
    for (int i=0;i<numNodes;i++)
        for (int j=0;j<numNodes;j++)
            adjMat[i][j] = 0;

    while(!someInput->eof())
    {
        getline(*someInput,input);
        if (input.size() == 0) 
            break;

        vector <string> splitString = split(input,' ');
        if (splitString.size() != 2)
        {
            cerr << "Incorrect formating." << endl;
            exit(0);
        }
        vector <string>::iterator vsit=splitString.begin();
        int i = atoi((*vsit).c_str());
        vsit++;
        int j = atoi((*vsit).c_str());
        adjMat[i][j] = 1;
    }

    // Write output now
    *someOutput << numNodes << endl;

    for (int i=0;i<numNodes;i++)
    {
        for (int j=0;j<numNodes;j++)
            *someOutput << adjMat[i][j] << " ";
        *someOutput << endl;
    }
}

