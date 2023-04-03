#include "ListSection.h"


ListSection::ListSection() {
        firstnode = NULL;
        lastnode = NULL;
}
void ListSection::Push(Block block) {
    if (firstnode == NULL) {
        firstnode = new Section(block);
        lastnode = firstnode;
        return;
    }
    Section* section = firstnode;
    while (section->next != NULL) {
        section = section->next;
    }
    if (section->counter < T) {
        section->Push(block);
        return;
    }
    else {
        section->next = new Section(block, section);
        lastnode = section;
    }

}

Section* ListSection::FindSection(int* position) {
    Section* current = firstnode;
    //int ret = 0;
    while (current != NULL) {
        if (current->counter < *position) {
            *position -= current->counter;
            current = current->next;
        }
        else break;
    }
    return current;
}
void ListSection::Pop(int position) {
    Section* section(FindSection(&position));
    if (section->counter == 1) {
        if (this->firstnode == section)
            this->firstnode = section->next;
        if (section->prev != NULL)
            section->prev->next = section->next;
        if (section->next != NULL)
            section->next->prev = section->prev;
        free(section);
        return;
    }
    section->Pop(position);
    
}
void ListSection::Pop(int position,char* atrybut) {
    Section* section(FindSection(&position));
    /*
    if (section->counter == 1) {
        if (this->firstnode == section)
            this->firstnode = section->next;
        if (section->prev != NULL)
            section->prev->next = section->next;
        if (section->next != NULL)
            section->next->prev = section->prev;
        free(section);
        return;
    }
    */
        
    section->Pop(position,atrybut);
    //cout << "usuwanie " << position << "atrybutu ";
}

void ListSection::TestWypisz() {
    Section* current = firstnode;
    int j = 1;
    while (current != NULL) {
        cout << "    " << j << " wezel" << endl;
        for (int i = 0; i < current->counter; i++) {
            cout << "   " << i + 1 << " blok" << endl;
            //current->blocks[i].selectors->Write();
            //current->blocks[i].atrybuts->Write();
            //current->blocks[i].atrybutsvalue->Write();
        }
        j++;
        current = current->next;
    }
}
void ListSection::Wypisz() {
    Section* current = firstnode;
    int j = 1;
    while (current != NULL) {
        cout << "    " << j << " wezel" << endl;
        for (int i = 0; i < current->counter; i++) {
            cout << "   " << i + 1 << " blok" << endl;
            current->blocks[i].selectors->Write();
            current->blocks[i].atrybuts->Write();
            current->blocks[i].atrybutsvalue->Write();
        }
        j++;
        current = current->next;
    }
}
int ListSection::SecionAmount() {
    Section* current = firstnode;
    int ret = 0;
        
    if (current == NULL) return 0;
    while (current != NULL) {
        ret += current->counter;
        current = current->next;
    }
    return ret;
}
Block* ListSection::BlockPosition(int position) {
    Section* section(FindSection(&position));
    return &(section->blocks[position]);
}

