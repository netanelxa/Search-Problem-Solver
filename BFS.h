//
// Created by USER on 18/01/2020.
//

#ifndef UNTITLED6_BFS_H
#define UNTITLED6_BFS_H

#include "Search.h"
#include <string>
#include "string"
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class BFS: public Search {

public: BFS();
    struct Point
    {
        int x;
        int y;
    };

// A Data Structure for queue used in BFS
    struct queueNode
    {
        Point pt; // The cordinates of a cell
        int dist; // cell's distance of from the source
        string direction;
        string weight;
    };

    bool isValid(int row, int col);
    string classifyDirection(int i);
    void print_vectors(vector<string> splitedDirec, vector<string> splitedWeight);
    vector<string> split_sentence(string str,vector<string> splitedVec);
    int bfs(int mat[][], Point src, Point dest);



};


#endif //UNTITLED6_BFS_H
