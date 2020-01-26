//
// Created by netanel on 15/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

#include "State.h"
/**
*this class represents searchable object
 */

template<class T>
class Searchable {
protected:
    State<T> *current;
public:
    virtual State<T> *getInitialState() = 0;

    virtual bool isGoalState(State<T> *state) = 0;

    virtual State<T> *getCurrent() {
        return current;
    }

    virtual void setCurrVisited() {
        current->setVisited();
    }

    virtual bool getCurrVisited() {
        return current->getVisited();
    }

    virtual list<State<T> *> getAllPossibleStates(State<T> *s, char type) = 0;

    virtual void setCurr(State<T> *curr) = 0;

    virtual double calculateHValue(State<T> *cur) = 0;

    virtual State<T> *getGoalState()=0;

    virtual void initDis() = 0;
};


#endif //EX4_SEARCHABLE_H
