#pragma once
#include "Section.h"
class ListSection {
public:
    Section* firstnode;
    Section* lastnode;
    ListSection();
    void Push(Block block);
    Section* FindSection(int* position);
    void Pop(int position);
    void Pop(int position, char* atrybut);
    void TestWypisz();
    void Wypisz();
    bool  ElementExist(int n, char* commendPart3);
 
    int SecionAmount();
    
};
