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
#include "Searchable.h"
#include <iostream>

using namespace std;

class MatrixBuilder : public Searchable<Point> {
    State<Point> ***matrix;
    int cols;
    size_t rows;
    State<Point> *initialState;
    State<Point> *goalState;

public:
    MatrixBuilder(size_t rows, int cols);

    State<Point> ***build(string line);

    virtual bool isGoalState(State<Point> *state);

    void setInitalState(State<Point> *startPoint);
    void setGoalState(State<Point> *endPoint);

    void setGoalState(Point *endPoint);

    virtual State<Point> *getInitialState();

    virtual list<State<Point> *> getAllPossibleStates(State<Point> *s, char type);

    virtual void initDis();

    virtual void setCurr(State<Point> *curr);

    virtual double calculateHValue(State<Point> *cur);

    vector<vector<string>> toString();

    virtual State<Point> *getGoalState();

    virtual ~MatrixBuilder() {
        for (int i = 0; i < rows; ++i)
            delete[] matrix[i];
        delete[] matrix;

    };
};


#endif //EX4_MATRIXBUILDER_H
