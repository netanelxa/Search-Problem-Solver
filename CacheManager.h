//
// Created by netanel on 14/01/2020.
//

#ifndef EX4_CACHEMANAGER_H
#define EX4_CACHEMANAGER_H
/**
*CacheManager header.
 */
template<class P, class S>
class CacheManager {
public:
    virtual void insert(P p,S s) = 0;

    virtual S get(P p) = 0;
};


#endif //EX4_CACHEMANAGER_H
