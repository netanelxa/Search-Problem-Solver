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
#include "State.h"

//class T;
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

    bool isExist( priority_queue<State<T> *, vector<State<T> *>, Cmp> open, State<T> *state) {
        while (!open.empty()) {
            if (state->equals(open.top())) {
                return true;
            }
            open.pop();
        }
        return false;
    }
    priority_queue<State<T>*,vector<State<T>*>,Cmp> updateQueue(priority_queue<State<T>*, vector<State<T>*>, Cmp> &queueOpen) {
        priority_queue<State<T>*,vector<State<T>*>,Cmp> temp;
        while (!queueOpen.empty()) {
            State<T>* node = queueOpen.top();
            temp.push(node);
            queueOpen.pop();
        }
        return temp;
    }

    vector<State<T> *> search(Searchable<T> *searchable) override {

        priority_queue<State<T> *, vector<State<T> *>, Cmp> openList;
        openList.push(searchable->getInitialState());
        unordered_set<State<T> *> closed;
        vector<State<T> *> path;
        while (!openList.empty()) {
            State<T> *n = openList.top();

            // Remove this vertex from the open list
            openList.pop();
            evaluated++;
            // Add this vertex to the closed list
            n->setVisited();
            closed.insert(n);
            if (n->equals(searchable->getGoalState())) {
                //evaluated++;
                path.push_back(n);
                while (!n->equals(searchable->getInitialState())) {
                    path.push_back(n->getParent());
                    pathCost += n->getCost();
                    n = n->getParent();
                }
                pathCost += n->getCost();
                vector<State<T> *> back;
                for (unsigned long  i = path.size() - 1; i >= 0; i--) {
                    back.push_back(path.at(i));
                }
                return back;
            }
            list<State<T> *> adjacent = searchable->getAllPossibleStates(n, 'b');
            for (State<T> *adj : adjacent) {
                bool exist = isExist(openList, adj);
                if (!exist && closed.count(adj) != 1) {
                    adj->setParent(n);
                    adj->setHeur(searchable->calculateHValue(adj));
                    openList.push(adj);
                    adj->setDistance(n->getDistance() + adj->getCost());
                } else if (adj->getDistance() > n->getDistance() + adj->getCost()) {
                    adj->setDistance(n->getDistance() + adj->getCost());
                    adj->setParent(n);
                    adj->setHeur(searchable->calculateHValue(adj));
                    openList = updateQueue(openList);
                }
            }
        }

    }



    int getNumberOfNodesEvaluated()
    override{
        return evaluated;
    }

    double getPathCost()
    override{
        return pathCost;
    }


};


#endif //EX4_ASTAR_H
