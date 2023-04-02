#pragma once
#include "ListElements.h"
class Block {
public:
    ListElements* selectors;
    ListElements* atrybuts;
    ListElements* atrybutsvalue;
    Block();
    Block(ListElements a, ListElements b, ListElements c);
    bool IsEmpty();
    
};
