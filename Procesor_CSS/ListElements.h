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
    void Push(Element* firstnode);
    void Pop(char* text);
    void Pop(int position);
    void Pop();
    //Funkcja zwraca pozycje elementu w liscie zaczynaj¹c od 1 - w przypadku braku zwaraca -1 
    int  FindPosition(char* text);
    int GetListLen(); //zwraca dlugosc listy 
    Element* GetElement(int position); //zwraca wskaznik na element o podanje pozycjii 
    void Write();
    int CountElement(char* name); //Zwraca iloœc elementow w liscie o danej nazwie 
};
bool Compare(char* text1, char* text2);