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
