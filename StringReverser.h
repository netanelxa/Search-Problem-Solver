//
// Created by netanel on 14/01/2020.
//

#ifndef EX4_STRINGREVERSER_H
#define EX4_STRINGREVERSER_H


#include "Solver.h"
#include "string"
using namespace std;
/**
*header of StringReverser
 */
class StringReverser : public Solver<string,string>{

  public:
    StringReverser();
    virtual string solve(string p);
    virtual ~StringReverser(){};
};


#endif //EX4_STRINGREVERSER_H
