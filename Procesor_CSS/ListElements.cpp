#include "ListElements.h"

ListElements::ListElements() {
    firstnode = NULL;
}

void ListElements:: Push(char* text) {
    if (firstnode == NULL) {
        firstnode = new Element(text);
        return;
    }
    Element* element = firstnode;
    while (element->next != NULL) {
        element = element->next;
    }
    element->next = new Element(text);
}
void ListElements::Push(Element* firstnode)
{
    Element* current = firstnode;
    while (current != NULL) {
        this->Push(current->text);
        current = current->next;
    }
}
void ListElements:: Pop(char* text) {
    if (firstnode == NULL) return;
    if (firstnode->next == NULL)
        firstnode = NULL;
    Element* element = firstnode;
    if (Compare(firstnode->text, text)) {
        firstnode = firstnode->next;
        return;
    }
    while (!Compare(element->next->text, text)) {
        element = element->next;
    }
    Element* toDelete = element->next;
    element->next = element->next->next;
    delete(toDelete);
}
void ListElements::Pop(int position) {
    //Element* element = GetElement(position);
    //this->Pop(element->text);
    if (firstnode == NULL) return;
    if (firstnode->next == NULL)
        firstnode = NULL;
    Element* element = firstnode;
    //if (element == nullptr) return;
    int currentPosition = 1;
    while (element != NULL) {
        if (currentPosition == position) {
            //cout << "znaleziono ";
            this->Pop(element->text);
            return;
        }
        element = element->next;
        currentPosition++;
    }
    //cout << " nie znaleziono ";
  

}

void ListElements:: Pop() {
    if (firstnode == NULL) return;
    if (firstnode->next == NULL)
        firstnode = NULL;
    Element* element = firstnode;
    if (element == nullptr) return;
    while (element->next->next != NULL) {
        element = element->next;
    }
    delete(element->next->next);
    element->next = NULL;

}

int ListElements::FindPosition(char* text) {
    Element* element = firstnode;
    int position = 1;
    while (element != NULL) {
        if (Compare(element->text,text)) {

            return position;
        }
        element = element->next;
        position++;
    }
    //cout << " nie znaleziono ";
    return -1;
}
int ListElements::GetListLen() {
    if (this == NULL)return -1;
    Element* element = firstnode;
    int currentPosition = 0;
    while (element != NULL) {
        if (element->text[0] != '\0')
            currentPosition++;
        element = element->next;
    }    
    return currentPosition;
}
Element* ListElements:: GetElement(int position) {
    Element* element = firstnode;
    int currentPosition = 1;
    while (element != NULL) {
        if (currentPosition == position) {
            //cout << "znaleziono ";
            return element;
        }
        element = element->next;
        currentPosition++;
    }
    return NULL;
}

void ListElements:: Write() {
    int i = 1;
    if (firstnode == nullptr) return;
    Element* element = firstnode;
    while (element != NULL) {
        cout << "  " << i << " -|" << element->text<<"|";
        i++;
        element = element->next;
    }
    cout << endl;
}
int ListElements::CountElement(char* name) {
    if (this == NULL)return 0;
    if (this == nullptr)return 0;
    Element* element = firstnode;
    int count = 0;
    while (element != NULL) {
        if (Compare(element->text, name)) {
            count++;
        }
        element = element->next;
    }
    return count;
}
bool Compare(char* text1, char* text2) {
    int n = 1000000;
    for (int i = 0; i < n; i++) {
        if (text1[i] == '\0' && text2[i] == '\0')return true;
        if (text1[i] != text2[i])return false;
    }
    return false;
}
