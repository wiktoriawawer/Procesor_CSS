#include "Section.h"

  
Section::Section() {
    counter = 0;
    prev = NULL;
    next = NULL;
}
Section:: Section(Block block) {
    counter = 1;
    prev = NULL;
    next = NULL;
    blocks[counter - 1] = block;
}
Section::Section(Block block, Section* prev) {
    counter = 1;
    prev = prev;
    next = NULL;
    blocks[counter - 1] = block;
}

void Section::Push(Block block) {
    counter++;
    int i = counter - 1;
    blocks[counter - 1] = block;
}
void Section::Pop(int position) {
    for (int i = position; i < counter; i++) {
        blocks[i - 1] = blocks[i];
    }
    counter--;

    //cout << "--juz";
}
void Section::Pop(int position,char* atrybut) {
    ListElements* list = blocks[position-1].atrybuts;
    ListElements* valuesList = blocks[position - 1].atrybutsvalue;
    
    int atrybutPosition = list->FindPosition(atrybut);
    list->Pop(atrybutPosition);
    valuesList->Pop(atrybutPosition);

    //cout << "--juz+-";
}
int Section::CountElement(char* name, char type) {
    int count=0;
    for (int i = 0; i < counter; i++) {
        if (type == 'A') {
            count+=blocks[i].atrybuts->CountElement(name);
        }
        else if (type == 'S') {
            count += blocks[i].selectors->CountElement(name);
        }         
    }
    return count;
    

}

