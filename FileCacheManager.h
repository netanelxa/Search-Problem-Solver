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

using namespace std;

template<class P,class S>
class FileCacheManager : public CacheManager<P, S> {
private:
    int capacity;
    unordered_map<string, pair<T, list<string>::iterator>> _cache;
    list<string> _lru;
    fstream file;
public:
    FileCacheManager() {
        this->capacity = 5;
    }

    void insert(T obj) {
        auto keyLocation = _cache.find(this->problem);
        // exist in cache
        if (keyLocation != _cache.end()) {
            _cache.erase(_cache.find(this->problem));
            _lru.remove(this->problem);
        }
            //doesnt exist in cache
        else {
            if (_lru.size() == unsigned(capacity)) {
                _lru.pop_back();
                _cache.erase(_lru.back());
            }
        }
        // update
        _lru.push_front(this->problem);
        _cache[this->problem] = {obj, _lru.begin()};

        //open file
        file.open(obj.class_name + key, ios::out | ios::binary);
        if (!file.is_open()) {
            cout << "Error in opening file\n";
        }
        //write to the file
        file.write((char *) &obj, sizeof(obj));
        file.close();
    }

    T get(string key) {
        T object;
        T obj;
        auto keyLocation2 = _cache.find(key);

        //if the key is  in the cach
        if (keyLocation2 != _cache.end()) {
            //update _lrs
            insert(key, _cache.find(key)->second.first);
            object = _cache.find(key)->second.first;
        }
            //if the key is not in the cach

        else {
            file.open(T::class_name + key, ios::in | ios::binary);
            if (!file.is_open()) {
                cout << "Error in opening file" << T::class_name + key << "\n";
            } else {
                file.read((char *) &obj, sizeof(obj));
                file.close();
                object = obj;
                insert(key, obj);
            }
        }
        return object;
    }

    void foreach(void (*func)(T &)) {
        for (string str :_lru) {
            func(_cache[str].first);
        }
    }

};

#endif //EX4_FILECACHEMANAGER_H
