#include "Block.h"

Block:: Block() {
        selectors = NULL;
        atrybuts = NULL;
        atrybutsvalue = NULL;
    }
Block::Block(ListElements sel, ListElements atry, ListElements value) {
        selectors = new ListElements(sel);
        atrybuts = new ListElements(atry);
        atrybutsvalue = new ListElements(value);
}



