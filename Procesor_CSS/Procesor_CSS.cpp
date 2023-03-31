
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
            cout << "  " <<i << " -" << element->text;
            i++;
            element = element->next;
        }
        cout << endl;
    }
};

class Block {
public:
    ListElements* selectors;
    ListElements* atrybuts;
    ListElements* atrybutsvalue;
    Block() {
        selectors= NULL;
    }
    Block(ListElements a, ListElements b, ListElements c) {
        selectors = new ListElements(a);
        atrybuts = new ListElements(b);
        atrybutsvalue = new ListElements(c);
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
    Section(Block block) {
        counter = 1;
        prev = NULL;
        next = NULL;
        blocks[counter - 1] = block;
    }
    Section(Block block,Section* prev) {
        counter = 1;
        prev = prev;
        next = NULL;
        blocks[counter - 1] = block;
    }

    void Push(Block block) {
        counter++;
        int i = counter - 1;
        blocks[counter - 1] = block;
    }
};
class ListSection {
public:
    Section* firstnode;
    ListSection() {
        firstnode = NULL;
    }
    void Push(Block block) {
        if (firstnode == NULL) {
            firstnode = new Section( block);
            return;
        }
        Section* section =firstnode;
        while (section->next != NULL) {
            section = section->next;
        }
        if (section->counter < T) {
            section->Push(block);
            return;
        }else {
            section->next = new Section(block, section);
        }
            
            
    }
    void Push(Block* block) {
        Section* section = firstnode;
        while (section->counter != T) {
            section = section->next;
        }
        section->Push(*block);

    }
    void Wypisz() {
        Section* current = firstnode;
        int j = 1;
        while (current != NULL) {
            cout <<"    "<< j << " wezel" << endl;
            for (int i = 0; i < firstnode->counter; i++) {
                cout <<"   "<< i + 1 << " blok" << endl;
                firstnode->blocks[i].selectors->Write();
                firstnode->blocks[i].atrybuts->Write();
                firstnode->blocks[i].atrybutsvalue->Write();
            }
            j++;
            current = current->next;
        }
        
        
    }
};
int main()
{
    ListSection listaglowna1;

    ListElements atrybuts;
    ListElements atrybutsvalue;
    ListElements selectors;
    selectors.firstnode = NULL;
    atrybuts.firstnode = NULL;
    atrybutsvalue.firstnode = NULL;
        
   
    bool read = true,readselectors=true, readatributs=false,readartibutsvalue=false; 
    char x;
    char* dane;
    dane = NULL;
    char text[120];
    int i = 0;
    
    while (read) {
        x=getchar();
        if (i == 0 && x == ' ')continue;
        if (x == '\n' ||x=='\t') continue;     
        if (x == '@') {
            listaglowna1.Wypisz();
            selectors.Write();
            atrybuts.Write();
        }
        text[i] = x;
        i++;
        if (readselectors) {
            if (x == ',') {
                dane = (char*)malloc(sizeof(char) * (i));
                for (int j = 0; j < i; j++) {
                    dane[j] = text[j];
                }
                dane[i - 1] = '\0';
                selectors.Push(dane);
                i = 0;            
                
            }if (x == '{') {
                dane = (char*)malloc(sizeof(char) * (i));
                for (int j = 0; j < i; j++) {
                    dane[j] = text[j];
                }
                dane[i - 1] = '\0';
                selectors.Push(dane);
                i = 0;
                readselectors = false;
                readatributs = true;
                readartibutsvalue = false;
                continue;
            }
        
        }
        else if (x == ':' && readatributs) {
            dane = (char*)malloc(sizeof(char) * (i));
            for (int j = 0; j < i; j++) {
                dane[j] = text[j];
            }
            dane[i - 1] = '\0';
            atrybuts.Push(dane);
            i = 0;
            readartibutsvalue = true;
            readatributs = false;
            readselectors = false;
        
        }else {

            if (x == ';') {
                dane = (char*)malloc(sizeof(char) * (i));
                for (int j = 0; j < i; j++) {
                    dane[j] = text[j];
                }
                dane[i - 1] = '\0';
                atrybutsvalue.Push(dane);
                i = 0;
                readatributs = true;
                readartibutsvalue = false;
                readselectors = false;
            }if (x == '}'){
                if (i >1) {
                    dane = (char*)malloc(sizeof(char) * (i));
                    for (int j = 0; j < i; j++) {
                        dane[j] = text[j];
                    }
                    dane[i - 1] = '\0';
                    atrybutsvalue.Push(dane);
                    
                } 
                i = 0;
                readselectors = true;
                readartibutsvalue = false;
                readatributs = false;
                Block nowyblock((ListElements) selectors, (ListElements) atrybuts, (ListElements) atrybutsvalue);
                listaglowna1.Push(nowyblock);
                listaglowna1.Wypisz();
                selectors.firstnode = NULL;
                atrybuts.firstnode = NULL;
                atrybutsvalue.firstnode = NULL;
            }
            
        
        }

        if (x == '?') {
            cout << "koniec";           
            read = false;
        }
        
    }
    
   
    

}

