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
 
    int SecionAmount();
    Block* BlockPosition(int position);
};
