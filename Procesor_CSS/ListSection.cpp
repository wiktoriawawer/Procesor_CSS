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
        lastnode = section->next;
        lastnode->prev = section;
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
    else
        section->Pop(position);
    
}
void ListSection::Pop(int position,char* atrybut) {
    Section* section(FindSection(&position));        
    section->Pop(position,atrybut);

}
bool  ListSection:: ElementExist(int n, char* commendPart3) {
    int a = n;
    Section* section(FindSection(&a));
    ListElements* list = section->blocks[a- 1].atrybuts;
    if (list->FindPosition(commendPart3) != -1)return true;
    else return false;
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

