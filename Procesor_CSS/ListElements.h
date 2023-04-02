#pragma once
#include "Element.h"
#include <stdio.h>
#include <iostream>
using namespace std;

class ListElements
{
public:
    Element* firstnode;
    ListElements();

    void Push(char* text);
    void Pop(char* text);
    void Pop(int position);
    void Pop();
    Element* Find(char* text);
    int  FindPosition(char* text);
    int GetListLen();
    Element* GetElement(int position);
    void Write();
    int CountElement(char* name);

};
bool Compare(char* text1, char* text2);