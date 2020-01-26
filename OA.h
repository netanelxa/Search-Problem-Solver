//
// Created by netanel on 15/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H


#include "Solver.h"
#include "Searcher.h"
#include "BestFS.h"
#include "DFS.h"
#include "BFS.h"
#include "Astar.h"
#include "Point.h"
#include "MatrixBuilder.h"
#include <mutex>

/**
*Object Adaptor design pattern.
 */

template<class P, class S>
class OA : public Solver<P, S> {
    Searcher<Point> *searcher;


public:
    OA(Searcher<Point> *searcher1) {
        this->searcher = searcher1;
    }

    virtual S solve(P line) {
        size_t rows = std::count(line.begin(), line.end(), '\n') - 4;
        int cols = 0;
        for (int i = 0; i < line.find('\n'); i++) {
            if (line[i] == ',')
                cols++;
        }
        auto *matrixbuilder = new MatrixBuilder(rows, cols);  //build new matrix- the problem
        mutex g_i_mutex;
        g_i_mutex.lock();
        State<Point> ***StateVector = matrixbuilder->build(line);
        g_i_mutex.unlock();
        Searchable<Point> *searchable = matrixbuilder;
        vector<State<Point> *> solution = searcher->search(searchable);

        string final = "";
        int sumOfCost = solution.at(0)->getCost();          //conclusion and preparing path
        int solSize = solution.size();
        for (unsigned long i = 0; i < solution.size() - 1; i++) {
            int x1 = solution.at(i)->getState()->getX();
            int y1 = solution.at(i)->getState()->getY();
            int x2 = solution.at(i + 1)->getState()->getX();
            int y2 = solution.at(i + 1)->getState()->getY();
            sumOfCost += solution.at(i + 1)->getCost();
            if (y1 < y2) {
                final += "Right (" + to_string(sumOfCost) + "), ";
                continue;
            }
            if (y1 > y2) {
                final += "Left (" + to_string(sumOfCost) + "), ";
                continue;
            }
            if (x1 < x2) {
                final += "Down (" + to_string(sumOfCost) + "), ";
                continue;
            }
            if (x1 > x2) {
                final += "Up (" + to_string(sumOfCost) + "), ";
                continue;
            }
        }
        //   delete matrix;
        final.erase(final.length() - 2, 2);
        cout<<"Matrix Size: "<<rows+1<<" * "<<cols+1<<endl;
        cout<<"Number of nodes: "<<solSize+1<<endl;
        cout<<"Path: "<<final<<endl;
        return final;
    }


    virtual ~OA() {
        delete searcher;
    }
};


#endif //EX4_OA_H
