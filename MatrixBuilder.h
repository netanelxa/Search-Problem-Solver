//
// Created by netanel on 20/01/2020.
//

#ifndef EX4_MATRIXBUILDER_H
#define EX4_MATRIXBUILDER_H

#include "string"
#include "Point.h"
#include <bits/stdc++.h>
#include "State.h"
#include "vector"
#include <iostream>
using namespace std;

class MatrixBuilder {
public:
    vector<State<Point>*>  build(string line);
};


#endif //EX4_MATRIXBUILDER_H
