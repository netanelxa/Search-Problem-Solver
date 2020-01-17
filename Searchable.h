//
// Created by netanel on 15/01/2020.
//

#ifndef EX4_SEARCHABLE_H
#define EX4_SEARCHABLE_H

template<class T>
class Searchable {
public:
    virtual T getInitialState()=0;
    virtual bool isGoalState(T state)=0;
    virtual T getAllPossibleStates(T state)=0;
};


#endif //EX4_SEARCHABLE_H
