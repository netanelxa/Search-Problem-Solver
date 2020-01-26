//
// Created by netanel on 19/01/2020.
//

#ifndef EX4_ASTAR_H
#define EX4_ASTAR_H


#include "Searcher.h"
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>

/**
*Implementation of A* algorithm.
 */

using namespace std;
template <class T>
class AStar :  public Searcher<T> {
private:
    int evaluated;
    double pathCost;
    class Cmp {
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getHeur()) > (right->getHeur());
        }
    };

public:
    AStar() {
        evaluated = 0;
        pathCost = 0;
    }


    //checks if a specific state is in Cmp priority queue.
    bool isExist( priority_queue<State<T> *, vector<State<T> *>, Cmp> open, State<T> *state) {
        while (!open.empty()) {
            if (state->equals(open.top())) {
                return true;
            }
            open.pop();
        }
        return false;
    }

    //updates priority queue.
    priority_queue<State<T>*,vector<State<T>*>,Cmp> updateQueue(priority_queue<State<T>*, vector<State<T>*>, Cmp> &queueOpen) {
        priority_queue<State<T>*,vector<State<T>*>,Cmp> temp;
        while (!queueOpen.empty()) {
            State<T>* node = queueOpen.top();
            temp.push(node);
            queueOpen.pop();
        }
        return temp;
    }

    //A* algorithm implementation.
    virtual vector<State<T> *> search(Searchable<T> *searchable) {
        priority_queue<State<T> *, vector<State<T> *>, Cmp> openList;
        openList.push(searchable->getInitialState());
        unordered_set<State<T> *> closed;
        vector<State<T> *> path;
        while (!openList.empty()) {
            State<T> *n = openList.top();
            openList.pop();
            evaluated++;
            n->setVisited();
            closed.insert(n);
            int s=n->getCost();
            auto a=n->getState();
            auto b= searchable->getGoalState();

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
                unsigned int i=(path.size()-1);
                while(i<-1){
                    back.push_back(path.at(i));
                    i--;
                }
                return back;
            }

            list<State<T> *> adjacent = searchable->getAllPossibleStates(n);
            for (State<T> *adj : adjacent) {   //check adj cells

                bool exist = isExist(openList, adj);
                if (!exist && closed.count(adj) != 1) {
                    adj->setParent(n);
                    adj->setHeur(searchable->calculateHValue(adj));
                    openList.push(adj);
                    adj->setDistance(n->getDistance() + adj->getCost());
                } else if (adj->getDistance() > n->getDistance() + adj->getCost()) {   //developing adj cells in matrix

                    adj->setDistance(n->getDistance() + adj->getCost());
                    adj->setParent(n);
                    adj->setHeur(searchable->calculateHValue(adj));
                    openList = updateQueue(openList);
                }
            }
        }

    }
};


#endif //EX4_ASTAR_H
