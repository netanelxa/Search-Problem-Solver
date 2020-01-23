//
// Created by netanel on 22/01/2020.
//

#ifndef EX4_GRAPHFILE_H
#define EX4_GRAPHFILE_H

#include <iostream>
#include <fstream>
#include "MatrixBuilder.h"

using namespace std;

class GraphFile {
    ofstream graph;
    string counter = "10";

public:
    GraphFile() {
        graph.open("graph.txt", std::ios_base::app);
        graph << counter;
        graph << "\n";
    }

    void write(MatrixBuilder *matrix);

    ~GraphFile() {
        graph.close();
    }

};


#endif //EX4_GRAPHFILE_H
