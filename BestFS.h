//
// Created by netanel on 19/01/2020.
//

#ifndef EX4_BESTFS_H
#define EX4_BESTFS_H
#include "Searcher.h"
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
#include "State.h"

using namespace std;


/**
*Implementation of Best First Search algorithm.
 */

template<class T>
class BestFS : public Searcher<T> {
private:
    int evaluated;
    double pathCost;

    class Cmp {
    public:
        bool operator()(State<T> *left, State<T> *right) {
            return (left->getDistance()) > (right->getDistance());
        }
    };

public:
    //constructor
    BestFS() {
        evaluated = 0;
        pathCost = 0;
    }

    //checks if a specific state is in Cmp priority queue.
    bool isExist(priority_queue<State<T> *, vector<State<T> *>, Cmp> open, State<T> *state) {
        while (!open.empty()) {
            if (state->equals(open.top())) {
                return true;
            }
            open.pop();
        }
        return false;
    }



    //updates priority queue.
    priority_queue<State<T> *, vector<State<T> *>, Cmp>
    updateQueue(priority_queue<State<T> *, vector<State<T> *>, Cmp> &queueOpen) {
        priority_queue<State<T> *, vector<State<T> *>, Cmp> temp;
        while (!queueOpen.empty()) {
            State<T> *node = queueOpen.top();
            temp.push(node);
            queueOpen.pop();
        }
        return temp;
    }

    //BestFs algorithm implementation.
    virtual vector<State<T> *> search(Searchable<T> *searchable) {
        priority_queue<State<T> *, vector<State<T> *>, Cmp> openList;
        openList.push(searchable->getInitialState());
        unordered_set<State<T> *> closed;
        vector<State<T> *> path;
        while (!openList.empty()) {
            evaluated++;
            State<T> *n = openList.top();
            openList.pop();
            closed.insert(n);

            //reaching goal state, return the path.
            if (searchable->isGoalState(n)) {
                path.push_back(n);
                while (!n->equals(searchable->getInitialState())) {
                    path.push_back(n->getParent());
                    pathCost += n->getCost();
                    n = n->getParent();
                }
                pathCost += n->getCost();
                vector<State<T> *> back;
                for (int i = path.size() - 1; i >= 0; i--) {
                    back.push_back(path.at(i));
                }
                return back;
            }
            list<State<T> *> adjacent;
            try {
                adjacent = searchable->getAllPossibleStates(n);
            } catch (exception &e) {
            }
            for (State<T> *adj : adjacent) { ;          //check adj cells
                bool exist = isExist(openList, adj);
                if (!exist && closed.count(adj) != 1) {
                    adj->setParent(n);
                    adj->setDistance(n->getDistance() + adj->getCost());
                    openList.push(adj);
                } else if (adj->getDistance() > n->getDistance() + adj->getCost()) {
                    bool inOpen = isExist(openList, adj);

                    adj->setDistance(n->getDistance() + adj->getCost());
                    adj->setParent(n);
                    openList = updateQueue(openList);

                }
            }
        }
        return path;
    }


};


#endif //EX4_BESTFS_H
