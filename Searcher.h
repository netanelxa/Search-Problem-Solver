//
// Created by netanel on 15/01/2020.
//

#ifndef EX4_SEARCHER_H
#define EX4_SEARCHER_H

#include "Searchable.h"
#include "Solver.h"

template<class T>
class Searcher {
public:
    virtual T Search(Searchable<T> src) = 0;
};


#endif //EX4_SEARCHER_H
