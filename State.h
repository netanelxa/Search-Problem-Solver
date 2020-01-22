//
// Created by netanel on 19/01/2020.
//

#ifndef EX4_STATE_H
#define EX4_STATE_H


#include <list>

using namespace std;
template <class T>
class State {
    T* state;
    State<T>* parent;
    double cost;
    double distance;
    bool visited;
    double heur;
public:
        State(double cost, T *state){
        this->cost = cost;
        this->distance = cost;
        this->parent = nullptr;
        this->state = state;
        this->heur = 0;
        this->visited=false;
    }

    T* getState(){
        return this->state;
    }
    State<T>* getParent(){
        return this->parent;
    }
    void setParent( State<T>* dad){
        this->parent = dad;
    }
    bool equals(State<T> *s){
        return this == s;
    }

    double getDistance() {
        return distance;
    }
    void setVisited() {
        this->visited = true;
    }
    bool getVisited() {
        return visited;
    }
    void setCost(double x){
        this->cost = x;
    }
    double getCost(){
        return this->cost;
    }
    void setDistance(double d) {
        this->distance = d;
    }

    double getHeur() {
        return heur;
    }

    void setHeur(double heur) {
        this->heur = heur;
    }

    ~State() {
        delete this->state;
    }
    void initDis(){
        this->distance =cost;
    }


};


#endif //EX4_STATE_H
