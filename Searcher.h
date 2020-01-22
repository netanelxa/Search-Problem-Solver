//
// Created by netanel on 15/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"
#include "Solver.h"
#include "vector"
template<class T>
class Searcher {
public:
    //virtual T search(Searchable<T> src) = 0;
    virtual vector<State<T>*> search(Searchable<T>* searchable)=0;
    };


#endif //EX4_SEARCHER_H
