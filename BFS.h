//
// Created by netanel on 21/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include <vector>
#include <unordered_set>
#include <iostream>
#include "Searcher.h"
using namespace std;
template<class T>
class BFS : public Searcher<T> {
private:
    int evaluated;
    double pathCost;

public:
    BFS<T>() {
        evaluated = 0;
        pathCost = 0;
    }

    virtual vector<State<T> *> search(Searchable<T> *searchable) {
        list<State<T> *> openList;
        openList.push_back(searchable->getInitialState());
        evaluated++;
            searchable->setCurrVisited();
        vector<State<T> *> trace;
        while (openList.size() > 0) {
            State<T> *n = openList.front();
            openList.pop_front();
            if (searchable->isGoalState(n)) {
                evaluated++;
                while (n->getParent() != nullptr) {
                    trace.push_back(n);
                    pathCost += n->getCost();
                    n = n->getParent();
                }
                pathCost += n->getCost();
                trace.push_back(n);
                vector<State<T> *> back;
                for (int i = trace.size() - 1; i >= 0; i--) {
                    back.push_back(trace.at(i));
                }
                return back;
            }
            list<State<T> *> succerssors = searchable->getAllPossibleStates(n, 'b');
            for (State<T> *state : succerssors) {
                bool visited = state->getVisited();
                if (!visited) {
                    state->setVisited();
                    state->setParent(n);
                    openList.push_back(state);
                    evaluated++;
                    searchable->setCurr(state);
                    //cout<<"test"<<;
                }
            }
        }
        //return nullptr;
    }
};

#endif //EX4_BFS_H
