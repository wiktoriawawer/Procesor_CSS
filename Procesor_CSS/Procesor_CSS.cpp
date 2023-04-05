
#include <stdio.h>
#include <iostream>
#include "Element.h"
#include "ListElements.h"
#include "ListSection.h"
using namespace std;
#define T 8
bool ReadLine(char text[120]);
int ilosccss=1;
int ilosckomend=0;

bool debug = false;
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
        if (text[i] < ' ' || text[i] > '~')continue;
        ret = ret * 10 + ((int)text[i]-(int)'0');
        i++;
    }
    return ret;
}


void  CommandDelete(char* commendPart1, char* commendPart3, ListSection* listSection) {
    if (listSection->firstnode == NULL) return;
    int n = ConvertToInt(commendPart1);
    if (commendPart3[0] == '*') {
        if (n <= listSection->SecionAmount()) {
            listSection->Pop(n);
            cout << n << ",D,*";
            cout << " == deleted" << endl;
        }
    }
    else {     
        if (n <= listSection->SecionAmount()) {
            if (listSection->ElementExist(n, commendPart3)) {
                listSection->Pop(n, commendPart3);
                cout << n << ",D," << commendPart3;
                cout << " == deleted" << endl;
            }
            
        }
    }
}

void  CommandAmountOf(char* commendPart1, char commendPart2, ListSection* listSection) {
    int n;
    int commendNumber;
    if (isdigit(commendPart1[0])) {
        n = ConvertToInt(commendPart1);
        commendNumber = n;
        Section* section(listSection->FindSection(&n));
        if (section == NULL) return;
        if (commendPart2 == 'A') {
            cout << commendNumber << ",A,? ";
            cout << "== "<<section->blocks[n - 1].atrybuts->GetListLen() << endl;
            return;
        }            
        else if (commendPart2 == 'S') {
            cout << commendNumber << ",S,? ";
            cout << "== " << section->blocks[n - 1].selectors->GetListLen() << endl;
            return;
        }
            
    }
    else {
        Section* current = listSection->firstnode;
        ListElements* selectors=new ListElements();
        int count = 0;
        while (current != NULL) {
            int n = current->CountElement(commendPart1, commendPart2, selectors);

            count += n;
            current = current->next;
        }
        cout << commendPart1 << "," << commendPart2 << ",? ";
        cout << "== " << count << endl;
    }
}
void CommandAtrybutsValue(int position, char* name, ListSection* listSection) {
    int n = position;
    Section* section(listSection->FindSection(&n));
    int m = section->blocks[n - 1].atrybuts->FindPosition(name);
    if (m == -1) return;
    cout << position << ",A," << name;
    cout << " == ";
    cout << section->blocks[n - 1].atrybutsvalue->GetElement(m)->text << endl;
}
void CommandSelector(int position,int j, ListSection* listSection) {
    int n = position;
    Section* section(listSection->FindSection(&n));
    if (section == NULL)return;
    if (section->blocks[n - 1].selectors->GetElement(j) == nullptr) return;
    cout << position << ",S," << j;
    cout <<" == " <<section->blocks[n - 1].selectors->GetElement(j)->text << endl;
}
void Command(char* commendPart1, char commendPart2, char* commendPart3, ListSection *listSection) {
    if (commendPart3[0] == '?') {
         CommandAmountOf(commendPart1,commendPart2,listSection );
         return;
    }
    if (commendPart2 == 'D') {
         CommandDelete(commendPart1, commendPart3, listSection);
         return;
    }
    if (commendPart2 == 'E') {
        Section* current = listSection->lastnode;
        int position = -1;
        while (current != NULL) {
            position = current->IsInBlock(commendPart1);
            if (position != -1) {
                int atrybutsPosition=current->blocks[position].atrybuts->FindPosition(commendPart3);
                if (atrybutsPosition != -1) {
                    cout << commendPart1 << ",E," << commendPart3 << " == ";
                    cout << current->blocks[position].atrybutsvalue->GetElement(atrybutsPosition)->text << endl;
                    debug = true;
                    return;
                }                
            }            
            current = current->prev;
        }
        return;
    }
    if (!isdigit(commendPart1[0]))return; 
    int n = ConvertToInt(commendPart1);
    if (commendPart2 == 'A') {
         CommandAtrybutsValue(n, commendPart3,listSection);
         return;
    }
    if (commendPart2 == 'S') {
        int j = ConvertToInt(commendPart3);
        CommandSelector(n, j, listSection);
        return;
    }
}

bool ReadLine(char text[120]) {
    char x;
    int i = 0;
    while ((x = getchar())!=EOF) {
        if (x == '\n' && i != 0)break;
        if (x == '\n' && i == 0) {
            text[0] = '@';
            i++;
            break;
        }
        if (x == '\t')continue;
        if (x == '\v')continue;
        if (x == '\f')continue;
        if (x == '\r')continue;
        if (x < ' ' || x > '~')continue;
        text[i] = x;
        i++;
    }
    if (x == EOF) return false;
    text[i] = '\0';
    i++;
    return true;
}

bool ApplyComand(ListSection* listSection) {
    char x;
    char text[120]; 
    while (true) {
        if (!ReadLine(text)) return false;
        if (text[0] == '*') {
            ilosccss++;
            break;
        }
        if (text[0] == '@') continue;
        if (text[0] == '\0') continue;
        if (text[3] == '*') {
            break;
        }
        if (text[0] == '?'&& text[1]=='\0') {
            if (listSection->firstnode == NULL) {
                cout << "? == 0" << endl;
                continue;
            }
            cout << "? == " << listSection->SecionAmount() << endl;
            continue;
        }
        if (text[3] == '?' && text[0] == '?') {
            continue;
        }
        
        char commendPart1[40];
        char commendPart2;
        char commendPart3[40];
        int i = 0;
        for (i; i < 120; i++) {
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
            if ((text[i] == ',') || (text[i] == '\0')) {
                commendPart3[j] = '\0';
                break;
            }
            commendPart3[j] = text[i];
            j++;
        }
        if (i > 120)break;
        Command(commendPart1, commendPart2, commendPart3, listSection); 
    }
    return true;
}

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
    char text[120000];
    int i = 0;
    while ((x = getchar()) != EOF) {
        
        if (i == 0 && x == ' ')continue;
        if (x == '\n' || x=='\t') continue;  
        if (x == '\v') continue;
        if (x == '\f') continue;
        if (x == '\r') continue;
        if (x < ' ' || x > '~')continue;
        if (x == '@') {
            //break;
            listaglowna1.Wypisz();
            selectors.Write();
            atrybuts.Write();
            continue;
        }
        text[i] = x; 
        i++;
        if (x == '?' && i >= 4) {
            if (text[i - 2] == '?' && text[i - 3] == '?' && text[i - 4] == '?') {
                ilosckomend++;
                ApplyComand(&listaglowna1);
                i = 0;
                continue;
            }
        }
        if (readselectors) {
            if (x == ',') {
                if (text[i - 1] == ' ') i--;
                dane = (char*)malloc(sizeof(char) * (i));
                for (int j = 0; j < i; j++) {
                    dane[j] = text[j];
                }
                dane[i - 1] = '\0';
                if (selectors.FindPosition(dane) == -1) {
                    selectors.Push(dane);
                }
                i = 0;            
            }if (x == '{') {
                if (text[i - 2] == ' ') i-- ;
                dane = (char*)malloc(sizeof(char) * (i));
                for (int j = 0; j < i; j++) {
                    dane[j] = text[j];
                }
                dane[i - 1] = '\0';
                if (selectors.FindPosition(dane) == -1) {
                    selectors.Push(dane);
                }
                i = 0;
                readselectors = false;
                readatributs = true;
                readartibutsvalue = false;
                continue;
            }
        }
        else if (x == ':' && readatributs) {
            if (text[i - 1] == ' ')i--;
            dane = (char*)malloc(sizeof(char) * (i));
            for (int j = 0; j < i; j++) {
                dane[j] = text[j];
            }
            dane[i - 1] = '\0';
            int positionOfDane = atrybuts.FindPosition(dane);
            if (positionOfDane != -1) {
                atrybuts.Pop(dane);
                atrybutsvalue.Pop(atrybutsvalue.GetElement(positionOfDane)->text);
            }
            atrybuts.Push(dane);
            i = 0;
            readartibutsvalue = true;
            readatributs = false;
            readselectors = false;
        
        }else {
            if (x == ';') {
                if (text[i - 1] == ' ')i--;
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
                if (text[i - 1] == ' ')i--;
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
                listaglowna1.Push( Block((ListElements)selectors, (ListElements)atrybuts, (ListElements)atrybutsvalue));
                //listaglowna1.Wypisz();
                selectors.firstnode = NULL;
                atrybuts.firstnode = NULL;
                atrybutsvalue.firstnode = NULL;
            }
        }        
    } 
    //cout << ilosccss << "," << ilosckomend;

}

