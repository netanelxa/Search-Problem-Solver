//
// Created by netanel on 15/01/2020.
//

#ifndef EX4_OA_H
#define EX4_OA_H


#include "Solver.h"
#include "Searcher.h"

template<class P, class S,class T>
class OA : public Solver<P, S> {
    Searcher<T> *searcher;
public:
    S solve(P){
    } ;
};


#endif //EX4_OA_H
