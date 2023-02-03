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
    void addMeelee(Meelee meelee);
    void addRanged(Ranged ranged);
    void removeMeelee(int x, int y);
    void removeRanged(int x, int y);
};