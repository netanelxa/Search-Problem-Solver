//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_SOLVER_H
#define EX4_SOLVER_H


template<class P, class S>
class Solver {
public:

    virtual S solve(P) = 0;

    virtual ~Solver() {};
};


#endif //EX4_SOLVER_H
