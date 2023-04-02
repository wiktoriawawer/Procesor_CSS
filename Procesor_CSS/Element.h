#pragma once
#include <stdio.h>
class Element {
public:
    char* text;
    Element* next;
    Element(char* text);
    Element(char* text, Element* next);
};
