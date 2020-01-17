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
#include <mutex>

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


    void insert(P problem, S solution) {
        mutex g_i_mutex;
        g_i_mutex.lock();
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
        file.open(problem + ".txt", ios::out);
        if (!file.is_open()) {
            cout << "Error in opening file\n";
        }
        //write to the file
        file << solution;
        file.close();
        g_i_mutex.unlock();

    }

    S get(P problem) {
        mutex g_i_mutex;
        g_i_mutex.lock();
        S object;
        S solution;
        auto keyLocation2 = _cache.find(problem);
        //if the problem is  in the cache
        if (keyLocation2 != _cache.end()) {
            //update _lrs
            solution = _cache.find(problem)->second.first;
        }
            //if the problem is not in the cache
        else {
            auto problemFileName = problem;
            file.open(problemFileName + ".txt", ios::in | ios::binary);
            if (!file.is_open()) {
                cout << "there is no existing solution from the problem " << "\n";
                return "-1";
            } else {
                getline(file,object);
                //file.read((char *) &object, sizeof(object));
                file.close();
                solution = object;
            }
        }
        g_i_mutex.unlock();
        return solution;
    }
};

#endif //EX4_FILECACHEMANAGER_H
