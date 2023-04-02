
#include <stdio.h>
#include <stdlib.h>
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
    Element* Find(char* text) {
        Element* element = firstnode;
        while (element == NULL) {
            if (element->text == text) {
                cout << "znaleziono " << text;
                return element;
            }
            element = element->next;
        }
        cout << " nie znaleziono " << text;
        return NULL;
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
    void Pop(int position) {
        delete &blocks[position - 1];
        
        for (int i = position - 1; i < counter-1; i++) {
            blocks[i] = blocks[i+1];
        }
        counter--;
        cout << "juz";
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
   
    Section* FindSection(int *position) {
        Section* current = firstnode;
        int ret = 0;
        while (current != NULL) {
            
            if (ret + current->counter < *position) {
               
                ret += current->counter;
                current = current->next;
            }
            else break;          
        }

        return current;
    }
    void Pop(int position) {
        Section* section(FindSection(&position));
        section->Pop(position);
        cout << "usuwanie " << position << "sekcji";
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
    int SecionAmount() {
        Section* current = firstnode;
        int ret = 0;
        int j = 1;
        while (current != NULL) {
            ret += current->counter;            
            current = current->next;
        }
        return ret;
    }
};
bool IsCommand(char* text) {
    bool komendy = true;
    for (int j = 0; j < 4; j++) {
        if (text[j] != '?') komendy = false;
    }
    return komendy;

}
int ConvertToInt(char* text) {
    int ret = 0;
    int i = 0;
    while (true) {
        if (text[i] == ',') break;
        if (text[i] == '\n') break;
        if (text[i] == '\0') break;
        ret = ret * 10 + ((int)text[i]-(int)'0');
        i++;
    }
    return ret;
}
int ReadingNumber(char firstchar) {
    char text[6];
    int i = 0;
    char x = firstchar;
    if (!isdigit(firstchar)) return -1;
    while (isdigit(x)) {
        text[i] = x;
        i++;
        x = getchar();
    }       
    return  1;//1ConvertToInt(text, i);
    
}
void  CommandSelectors(char* commendPart1, char* commendPart3, ListSection listSection) {

}
void  CommandAtrybuts(char* commendPart1, char* commendPart3, ListSection listSection) {

}

void  CommandDelete(char* commendPart1, char* commendPart3, ListSection listSection) {
    int n = ConvertToInt(commendPart1);
    if (commendPart3[0] == '*') {
        listSection.Pop(n);
    }
    else {
        //listSection.Pop(n, commendPart3);
        
    }

}

void  CommandAtrybutsValue(char* commendPart1, char* commendPart3, ListSection listSection) {

}



void ReadLine(char text[120]) {
    char x;
    int i = 0;
    while (true) {
        x = getchar();
        if (x == '\n' && i != 0)break;
        if (x == '\n' && i == 0)continue;
        text[i] = x;
        i++;
    }
    text[i] = '\0';
    i++;
    cout << "----";
    for (int j = 0; j < i; j++) {
        cout << text[j];
    }
    cout << "----";
}

void ApplyComand(ListSection listSection) {
    char x;
    char text[120]; 
    while (true) {
        ReadLine(text);
        if (text[3] == '*') {
            cout << "koniec komend";
            break;

        }
        if (text[0] == '?') {
            cout << "liczba sekcji CSS";
            cout << " == " << listSection.SecionAmount();
            continue;
        }
        char commendPart1[40];
        char commendPart2;
        char commendPart3[40];
        int i = 0;
        for ( i ; i < 120; i++) {
            
            if (text[i] == ',') {
                commendPart1[i] = '\0';
                break;
            }
            commendPart1[i] = text[i];
        }
        commendPart2 = text[i + 1];
        int j = 0;
        i = i + 3;
        for (i; i < 120; i++) {
            if( (text[i] == ',') || (text[i] == '\0') ){
                commendPart3[j] = '\0';
                break;
            }
            commendPart3[j] = text[i];
            j++;
        }
        //Command(commendPart1, commendPart2, commendPart3); 
        if (commendPart2 == 'S') {
            CommandSelectors(commendPart1, commendPart3, listSection);
        }
        else  if (commendPart2 == 'D') {
            CommandDelete(commendPart1, commendPart3, listSection);
        }
        else if (commendPart2 == 'E') {
            CommandAtrybutsValue(commendPart1, commendPart3, listSection);
        }
        else if (commendPart2 == 'A') {
            CommandAtrybuts(commendPart1, commendPart3, listSection);

        }
        else cout << "Blędna komenda ";

        /*
         int n;
        if (isdigit(text[0])) {
            n = ConvertToInt(text);
            cout << "liczba:" << n << endl;
            cout <<"text:"<< text;
        }
        else {
        
        
        }
        char commend;
        for (i=0;i < 100; i++) {
            if (text[i] == ',') {
                commend = text[i+1];
                break;
            }           
        }
        cout << "komenda:" << commend << endl;
        int m;
        if (isdigit(text[i +3])) {
            m = ConvertToInt(&text[i+3]);
            cout << "liczba:" << m << endl;
        }
        */
       
        
        
      
        

    }

}

int main()
{   
  
    char t1[10];
    for (int i = 0; i < 10; i++) {
        t1[i] = '0'+i;
    }
    cout << t1;
    char* a = t1;
    char* b = t1;
    b = &a[2];
   // a = &t1[2];
    cout << a;
    cout << b;

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
        if (x == '?' && i == 4) {
            if (IsCommand(text)) {
                i = 0;
                cout << "wczytuje komende";
                ApplyComand(listaglowna1);
            }
            
        }
      
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

        if (x == '!') {
            cout << "koniec";           
            read = false;
        }
        
    }
    
   
    

}

