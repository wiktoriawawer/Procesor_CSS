#pragma once
#include "Block.h"
#define T 8
using namespace std; 
class Section {
public:
    Block blocks[T];
    int counter;
    Section* prev;
    Section* next;
    Section();
    Section(Block block);
    Section(Block block, Section* prev);
    void Push(Block block);
    void Pop(int position);
    void Pop(int position, char* atrybut);
    int CountElement(char* name, char type,ListElements* selectors);
    int CountElement(char* name, char type);
    int IsInBlock(char* selectorName);
};

