
#include <stdio.h>
#include <iostream>
#define T 8
using namespace std;

class Element {
public:
    char* text; 
    Element* next;
    Element(char* text) {
        this->text = text;
        next = NULL;
    }
    Element(char* text,Element* next) {
        this->text = text;
        this->next = next;
    }
};
class ListElements {
public:
    Element* firstnode;
    ListElements() {
        firstnode = NULL;
    }
    void Push(char* text) {
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
    void Pop(char* text) {
        if (firstnode == NULL) return;
        if (firstnode->next == NULL)
            firstnode = NULL;
        Element* element = firstnode;
        while (element->next->text != text) {
            element = element->next;
        }
        
        element->next= element->next->next;
        delete(element->next->next);
    }
    void Pop() {
        if (firstnode == NULL) return;
        if (firstnode->next == NULL)
            firstnode = NULL;
        Element* element = firstnode;
        while (element->next->next != NULL) {
            element = element->next;
        }
        delete(element->next->next);
        element->next = NULL;

    }
    void Find(char* text) {
        Element* element = firstnode;
        while (element == NULL) {
            if (element->text == text) {
                cout << "znaleziono " << text;
            }
            element = element->next;
        }
        cout << " nie znaleziono " << text;
    }
    int GetListLen() {

    }
    Element* GetElement(int position) {

    }
    int CountElement(char* valueofelement) {

    }
    void Write() {
        int i = 1;
        Element* element = firstnode;
        while (element != NULL) {
            cout << i << "  - " << element->text << endl;
            i++;
            element = element->next;
        }
    }
};

class Block {
public:
    ListElements* selectors;
    ListElements* atrybuts;
    Block() {
        selectors= NULL;

    }
    Block(ListElements* a) {
        selectors = a;
    }
}; 
class Section {
public:
    Block blocks[T];
    int counter; 
    Section* prev;
    Section* next;
    Section() {
        counter = 0;
        prev = NULL;
        next = NULL;
    }
    void Push(Block block) {
        counter++;
        int i = counter - 1;
        blocks[counter - 1] = block;
    }
};
class ListSection {
    Section* firstnode;
    void Push(Block block) {
        Section* section =firstnode;
        while (section->counter != T) {
            section = section->next;
        }
        section->Push(block);
            
    }
};

int main()
{
    
    ListElements atrybuts;
    ListElements lista;
    lista.firstnode = NULL;
    char* test;
    test = (char*)"testing";

    lista.Push(test);
    lista.Push(test);
    lista.Push(test);
    lista.Push(test);
    lista.Push(test);
    lista.Push(test);
    lista.Write();
    lista.Pop();
    lista.Pop();
    lista.Write();
        
   
    bool read = true; 
    char x;
    char* dane;
    dane = NULL;
    char text[120];
    int i = 0;
    while (read) {
        cin >> x;
        text[i] = x;
        i++;
        if (x == ',') {
            cout << "Koniec 1 elementu ";
            cout << i << endl;
            dane = (char*)malloc(sizeof(char)*(i));
            for (int j = 0; j < i; j++) {
                dane[j] = text[j];
            }
            dane[i - 1] = '\0';
            lista.Push(dane);
            lista.Write();
            i = 0;
        }if (x == '{') {
            cout << "koniec";
            Block xx1(&lista);
            read = false;
        }
    }
   
    

}

