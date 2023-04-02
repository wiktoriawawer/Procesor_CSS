#include "Element.h"

Element::Element(char* text) {
    this->text = text;
    next = NULL;
}
Element::Element(char* text, Element* next) {
    this->text = text;
    this->next = next;
}