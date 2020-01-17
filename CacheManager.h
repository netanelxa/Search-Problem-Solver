//
// Created by netanel on 14/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H

template<class P, class S>
class CacheManager {
public:
    virtual S insert(P p) = 0;

    virtual S get(P p) = 0;
};


#endif //EX4_CACHEMANAGER_H
