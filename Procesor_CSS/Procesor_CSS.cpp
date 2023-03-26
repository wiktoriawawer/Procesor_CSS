
#include <stdio.h>
#include <iostream>
using namespace std;

class Element {
    char* tekst; 
    Element* next;
};
class ListElements {
    Element* firstnode;
    void AddNext(char* tekst) {

    }
    void Delete(char* tekst) {

    }
    void Find(char* tekst) {

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
    char tekst[120];
    int i = 0;
    while (read) {
        cin >> x;
        if (x == '{') {
            cout << "Koniec";
            cout << tekst;

        }
        tekst[i] = x;//spacje i enter sie nie wczytuje !
        i++;
        
    }

}

