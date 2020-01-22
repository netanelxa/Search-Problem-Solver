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

template<class P, class S>
class OA : public Solver<P,S> {
    Searcher<Point> *searcher;

public:
    OA(Searcher<Point> *searcher1) {
        this->searcher = searcher1;
    }

    virtual S solve(P line)  {
        size_t rows = std::count(line.begin(), line.end(), '\n')-4;
        int cols = 0;
        for (int i = 0; i < line.find('\n'); i++) {
            if (line[i] == ',')
                cols++;
        }
        auto *matrixbuilder = new MatrixBuilder(rows, cols);
        State<Point> ***StateVector = matrixbuilder->build(line);
        Searchable<Point> *searchable = matrixbuilder;
        cout << "From Here" << endl;
        for (int i = 0; i <= cols; i++) {
            for (int j = 0; j <= rows; j++) {
                std::cout << StateVector[i][j]->getCost() << " ";
            }
            std::cout << std::endl;
        }
        vector<State<Point> *> solution = searcher->search(searchable);
        string final = "";
        int sumOfCost=0;
        for (unsigned long i = 0; i < solution.size() - 1; i++) {
            int x1 = solution.at(i)->getState()->getX();
            int y1 = solution.at(i)->getState()->getY();
            int x2 = solution.at(i + 1)->getState()->getX();
            int y2 = solution.at(i + 1)->getState()->getY();
            sumOfCost+=solution.at(i)->getCost();
            if (y1 < y2) {
                final += "Right ("+to_string(sumOfCost)+"), ";
                continue;
            }
            if (y1 > y2) {
                final += "Left ("+to_string(sumOfCost)+"), ";
                continue;
            }
            if (x1 < x2) {
                final += "Down ("+to_string(sumOfCost)+"), ";
                continue;
            }
            if (x1 > x2) {
                final += "Up ("+to_string(sumOfCost)+"), ";
                continue;
            }
        }
        //   delete matrix;
        final.erase(final.length() - 2, 2);
        return final;
    }


    virtual ~OA() {
        delete searcher;
    }
};



#endif //EX4_OA_H
