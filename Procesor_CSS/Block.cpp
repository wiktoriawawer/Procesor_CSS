#include "Block.h"

Block:: Block() {
        selectors = NULL;
    }
Block::Block(ListElements a, ListElements b, ListElements c) {
        selectors = new ListElements(a);
        atrybuts = new ListElements(b);
        atrybutsvalue = new ListElements(c);
}
bool Block::IsEmpty() {
    if (atrybuts->firstnode == NULL) {
        //cout << "lista pusta";
        return true;
    }
    else return false;
}
int  Block::FindElement (char* selectorName,char* atrybutName) {
    Element* current = this->selectors->firstnode;
    while (current != NULL) {
        if (Compare(current->text, selectorName)) {

        }
    }
    if (atrybuts->firstnode == NULL) {
        //cout << "lista pusta";
        return true;
    }
    else return false;
}


