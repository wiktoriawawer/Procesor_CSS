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
    this->prev = prev;
    this->next = NULL;
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
    if (list->firstnode == NULL)
        this->Pop(position);

    //cout << "--juz+-";
}
int Section::CountElement(char* name, char type) {
    int count=0;
    for (int i = 0; i < counter; i++) {
        if (type == 'A') {
            int n = blocks[i].atrybuts->CountElement(name);
            if (n > 0) {
                //sprawdzic czy wystepuje juz w selectors dodac lub nie ale chyba ten push sie nie przyda 
                //selectors->Push(blocks[i].selectors->firstnode);
            }
            count+=n;
        }
        else if (type == 'S') {
            count += blocks[i].selectors->CountElement(name);
        }         
    }
    return count;
}
int Section::CountElement(char* name, char type, ListElements* selectors) {
    int count = 0;
    for (int i = 0; i < counter; i++) {
        if (type == 'A') {
            int n = blocks[i].atrybuts->CountElement(name);
            if (n > 0) {
                //sprawdzic czy wystepuje juz w selectors dodac lub nie ale chyba ten push sie nie przyda 
                Element* current = blocks[i].selectors->firstnode;
                while (current!=NULL) {
                    int positionselector = selectors->FindPosition(current->text);
                    if (positionselector != -1) {
                        n--;
                    }
                    else {
                        selectors->Push(current->text);
                    }
                    current = current->next; 
                }
                count++;
            }

        }
        else if (type == 'S') {
            count += blocks[i].selectors->CountElement(name);
        }
    }
    return count;
}

//return last number of blocks if it is Section else -1 
int Section::IsInBlock(char* selectorName) {
    for (int i = counter-1; i >=0; i--) {
        if (blocks[i].selectors->CountElement(selectorName) > 0)
            return i;
    }
    return -1;
}

