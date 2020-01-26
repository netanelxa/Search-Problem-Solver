//
// Created by netanel on 14/01/2020.
//

#include "StringReverser.h"

StringReverser::StringReverser(){}


//return the reverse of a string
string StringReverser::solve(string p) {
    int n = p.length();
    for (int i = 0; i < n / 2; i++)
        swap(p[i], p[n - i - 1]);
    return p;
}