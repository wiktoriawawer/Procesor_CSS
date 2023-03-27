
#include <stdio.h>
#include <iostream>
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
    Element* firstnode;
    void AddNext(char* text) {
        if (firstnode == NULL) {
            firstnode = new Element(text);
        }
        Element* element = firstnode;
        while (element->next != NULL) {
            element = element->next;
        }
        element->next = new Element(text);
    }
    void Delete(char* text) {


    }
    void Find(char* text) {
        Element* element = firstnode;
        while (element == NULL) {
            if (element->text == text) {
                cout << "znaleziono " << text;
            }
        }
    }
    int GetListLen() {

    }
    Element* GetElement(int position) {

    }
    int CountElement(char* valueofelement) {

    }

};

class Block {
    ListElements* selektors;
    ListElements* atrybuts;
        
};
class ListSection {
    Block Blocks[8];
    int counter; 
    ListSection* prev;
    ListSection* next;

};
void ReadToList(char* text, char separator) {

}
int main()
{   
    bool read = true; 
    char x;
    char text[120];
    int i = 0;
    while (read) {
        cin >> x;
        if (x == '{') {
            cout << "Koniec";
            cout << text;

        }
        text[i] = x;//spacje i enter sie nie wczytuje !
        i++;
        
    }

}

