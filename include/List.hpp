#pragma once

#include "Entity.hpp"
#include "Ranged.hpp"
#include "Meelee.hpp"

class List {

protected:
    
    struct meeleeList {
        Meelee meelee;
        meeleeList* next;
    };

    struct rangedList {
        Ranged ranged;
        rangedList* next;
    };

    meeleeList* meeleeHead;
    rangedList* rangedHead;

public:

    List();
};