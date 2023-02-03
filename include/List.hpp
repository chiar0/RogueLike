#pragma once

#include "Entity.hpp"
#include "Ranged.hpp"
#include "Meelee.hpp"

class List {

protected:
    
    struct meeleeList {
        Meelee meelee;
        meeleeList* next;
        meeleeList(Meelee m) : meelee(m), next(NULL) {}
    };

    struct rangedList {
        Ranged ranged;
        rangedList* next;
        rangedList(Ranged r) : ranged(r), next(NULL) {}
    };

    meeleeList* meeleeHead;
    rangedList* rangedHead;

public:

    List();

    // getters
    meeleeList* getMeeleeHead();
    rangedList* getRangedHead();

    // list functions
    void initMeelee();
    void initRanged();
    void addMeelee(Meelee meelee);
    void addRanged(Ranged ranged);
    void removeMeelee(int id);
    void removeRanged(int id);
};