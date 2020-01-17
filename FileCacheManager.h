//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_FILECACHEMANAGER_H
#define EX4_FILECACHEMANAGER_H


#include <string>
#include <array>
#include <list>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <functional>
#include "CacheManager.h"

using namespace std;

template<class P, class S>
class FileCacheManager : public CacheManager<P, S> {
private:
    int capacity;
    unordered_map<P, pair<S, list<string>::iterator>> _cache;
    list <string> _lru;
    fstream file;
public:
    FileCacheManager() {
        this->capacity = 5;
    }

    S DelSpace(S s) {
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ' ')
                s.erase(i, 1);
        }
        return s;
    }

    void insert(P problem, S solution) {
        auto keyLocation = _cache.find(problem);
        // exist in cache
        if (keyLocation != _cache.end()) {
            _cache.erase(_cache.find(problem));
            _lru.remove(problem);
        }
            //doesnt exist in cache
        else {
            if (_lru.size() == unsigned(capacity)) {
                _lru.pop_back();
                _cache.erase(_lru.back());
            }
        }
        // update
        _lru.push_front(problem);
        _cache[problem] = {solution, _lru.begin()};

        //open file
        file.open(problem, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "Error in opening file\n";
        }
        //write to the file
        file.write((char *) &solution, sizeof(solution));
        file.close();
    }

    S get(P problem) {
        S object;
        S solution;
        auto keyLocation2 = _cache.find(problem);
        //if the problem is  in the cache
        if (keyLocation2 != _cache.end()) {
            //update _lrs
            object = _cache.find(problem)->second.first;
        }
            //if the problem is not in the cache
        else {
            string problemFileName = DelSpace(problem);
            file.open(problemFileName, ios::in | ios::binary);
            if (!file.is_open()) {
                cout << "Error in opening file " << problem << "\n";
            } else {
                file.read((char *) &solution, sizeof(solution));
                file.close();
                object = solution;
                insert(problem, solution);
            }
        }
        return object;
    }


};

#endif //EX4_FILECACHEMANAGER_H
