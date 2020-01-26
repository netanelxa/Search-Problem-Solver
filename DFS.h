//
// Created by netanel on 19/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H


#include "Searcher.h"
#include "State.h"
#include "vector"

template<class T>
class DFS : public Searcher<T> {
private:
    int evaluated;
    double pathCost;

public:
    DFS() {
        evaluated = 0;
    }

    virtual vector<State<T> *> search(Searchable<T> *searchable) {

        searchable->setCurrVisited();
        vector<State<T> *> trace;
        this->helpSearch(searchable, searchable->getInitialState(), trace);
        return trace;
    }

    int helpSearch(Searchable<T> *searchable, State<T> *curr, vector<State<T> *> &trace) {
       auto a=curr->getState();
        if (searchable->isGoalState(curr)) {
            evaluated++;
            while (curr->getParent() != nullptr) {
                trace.push_back(curr);
                pathCost += curr->getCost();
                curr = curr->getParent();
            }
            pathCost += curr->getCost();
            trace.push_back(curr);
            vector<State<T> *> back;
            for (int i = trace.size() - 1; i >= 0; i--) {
                back.push_back(trace.at(i));
            }
            trace = back;
            return 1;
        }
        curr->setVisited();
        evaluated++;
        searchable->setCurr(curr);
        list<State<T> *> succerssors = searchable->getAllPossibleStates(curr, 'b');
        for (State<T> *state : succerssors) {
            bool visited = state->getVisited();
            if (!visited) {
                state->setParent(curr);
                if (helpSearch(searchable, state, trace) == 1) {
                    return 1;
                }
            }
        }
    }

};


#endif //EX4_DFS_H
