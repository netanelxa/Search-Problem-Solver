//
// Created by netanel on 22/01/2020.
//

#include "GraphFile.h"

void GraphFile::write(MatrixBuilder *matrix) {
    string size = to_string(matrix->getSize());
    string goal = to_string(matrix->getSize() -1);
    graph << size + "," + size;
    graph<<"\n";
    graph<< "0,0";
    graph<<"\n";
    graph<< goal + ","+ goal;
    graph<<"\n";
    vector<vector<string>> stringMat = matrix->toString();
    for (vector<string> row : stringMat){
        for (string cost : row){
            graph<< cost +",";
        }
        graph<<"\n";
    }
    graph<<"\n";
    graph.flush();
}