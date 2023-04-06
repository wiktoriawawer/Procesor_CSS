#include <stdio.h>
#include <iostream>
#include "Element.h"
#include "ListElements.h"
#include "ListSection.h"
using namespace std;
#define T 8
#define MAXLENGTH 1200
#define MAXCOMMANDLENGTH 120

//wczytuje linie komend
bool ReadLine(char text[120]);

//Konwersja tablicy char na int
int ConvertToInt(char* text);

//obsługa komendy usuwania 
void  CommandDelete(char* commendPart1, char* commendPart3, ListSection* listSection);

// obsługa komendy zliczania ilosci elementoe w sekcji 
void  CommandAmountOf(char* commendPart1, char commendPart2, ListSection* listSection);

// wypiuje wartosc atrybutu dla podanego numeru sekcji
void CommandAtrybutsValue(int position, char* name, ListSection* listSection);

// wypisuje j-ty selektor dla sekcji na -position- miejscu 
void CommandSelector(int position, int j, ListSection* listSection);

// wywoływanie odpowiednich funkcji dla podanej komendy
void Command(char* commendPart1, char commendPart2, char* commendPart3, ListSection* listSection);

// obsluguje wczytywanie komendy i przekazuje ja podzielona do Command 
bool ApplyComand(ListSection* listSection);

// sprawdza czy char jest białym znakiem 
bool CheckChar(char x);

int main()
{
    ListSection listaglowna1;
    ListElements atrybuts;
    ListElements atrybutsvalue;
    ListElements selectors;
    selectors.firstnode = NULL;
    atrybuts.firstnode = NULL;
    atrybutsvalue.firstnode = NULL;
    bool  readselectors = true, readatributs = false;
    char x;
    char* dane;
    dane = NULL;
    char text[MAXLENGTH];
    int i = 0;
    while ((x = getchar()) != EOF) {
        if (i == 0 && x == ' ')
            continue;
        if (x == '\n')
            continue;
        if (x == '\t') {
            continue;
        }

        if (x == '\v') continue;
        if (x == '\f') continue;
        if (x == '\r') continue;
        if (x < ' ' || x > '~')continue;
        if (x == '@') {
            continue;
        }
       
        text[i] = x;
        i++;
        //sprawdzenie czy wystapily ???? aby wejsc do sekcji komend
        if (x == '?' && i >= 4) {
            if (text[i - 2] == '?' && text[i - 3] == '?' && text[i - 4] == '?') {
                cout << "";
                ApplyComand(&listaglowna1);
                i = 0;
                readselectors = true;
                readatributs = false;
                continue;
            }
        }
        // sprawdzamy czu jestesmy w trybie czytania selektorow
        if (readselectors) {
            //usuniecie ostatnich spaciji 
            if (x == ',' ) 
                if (text[i - 1] == ' ') i--;
            if (x == '{') 
                if (text[i - 2] == ' ') i--;
            //wczytanie danych do listy 
            if (x == '{' || x == ',') {                
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
                readselectors = false;
                readatributs = true;
                continue;
            }
        }//sprawdzenie czy jestesmy w trybie czytania  atrybutow 
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
            readatributs = false;
            readselectors = false;

        }
        else {//obsluga wczytywania wartosci atrybutow 
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
                readselectors = false;
            }if (x == '}') {
                if (text[i - 1] == ' ')i--;
                if (i > 1) {
                    dane = (char*)malloc(sizeof(char) * (i));
                    for (int j = 0; j < i; j++) {
                        dane[j] = text[j];
                    }
                    dane[i - 1] = '\0';
                    atrybutsvalue.Push(dane);

                }
                i = 0;
                readselectors = true;

                readatributs = false;
                //przekazanie list i dodanie ich do głównej listy 
                listaglowna1.Push(Block((ListElements)selectors, (ListElements)atrybuts, (ListElements)atrybutsvalue));
                //ustawienie wskaznikow na listy na null
                selectors.firstnode = NULL;
                atrybuts.firstnode = NULL;
                atrybutsvalue.firstnode = NULL;
            
            }
        }
    }
}

int ConvertToInt(char* text) {
    int ret = 0;
    int i = 0;
    while (true) {
        if (text[i] == ',') break;
        if (text[i] == '\n') break;
        if (text[i] == '\0') break;
        if (text[i] < ' ' || text[i] > '~')continue;
        ret = ret * 10 + ((int)text[i] - (int)'0');
        i++;
    }
    return ret;
}



void  CommandDelete(char* commendPart1, char* commendPart3, ListSection* listSection) {
    if (listSection->firstnode == NULL)
        return;
    //odczytanie numeru sekcji
    int n = ConvertToInt(commendPart1);

    //sprawdzenie czy jestemy w opcji usuwania calej sekcji
    if (commendPart3[0] == '*') {
        //sprawdznie czy numer sekcji jest prawidłowy 
        if (n <= listSection->SecionAmount()) {
            listSection->Pop(n);
            cout << n << ",D,*";
            cout << " == deleted" << endl;
        }
    }
    else {
        //sprawdznie czy numer sekcji jest prawidłowy 
        if (n <= listSection->SecionAmount()) {
            //sprawdzenie czy istanieje epeleny o danej nazwie 
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
        //szukanie sekcji o n-tym numerze 
        Section* section(listSection->FindSection(&n));
        if (section == NULL) return;
        //obsługa licznie atrybutów w n-tej sekcji 
        if (commendPart2 == 'A') {
            cout << commendNumber << ",A,? ";
            cout << "== " << section->blocks[n - 1].atrybuts->GetListLen() << endl;
            return;
        }//obsługa licznia sekektorów w n-tej sekcji 
        else if (commendPart2 == 'S') {
            cout << commendNumber << ",S,? ";
            cout << "== " << section->blocks[n - 1].selectors->GetListLen() << endl;
            return;
        }

    }//obsługa liczenia atrybutów o podanej nazwie -commandPart1
    //n,S,? , n,A,?
    else {
        Section* current = listSection->firstnode;
        ListElements* selectors = new ListElements();
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

//1,A,n
void CommandAtrybutsValue(int position, char* name, ListSection* listSection) {
    int n = position;
    Section* section(listSection->FindSection(&n));
    int m = section->blocks[n - 1].atrybuts->FindPosition(name);
    if (m == -1) return;
    cout << position << ",A," << name;
    cout << " == ";
    cout << section->blocks[n - 1].atrybutsvalue->GetElement(m)->text << endl;
}
//i,S,j
void CommandSelector(int position, int j, ListSection* listSection) {
    int n = position;
    Section* section(listSection->FindSection(&n));
    if (section == NULL)
        return;

    if (section->blocks[n - 1].selectors->GetElement(j) == nullptr)
        return;

    if (j > section->blocks[n - 1].selectors->GetListLen())
        return;

    cout << position << ",S," << j;
    cout << " == " << section->blocks[n - 1].selectors->GetElement(j)->text << endl;
}
void Command(char* commendPart1, char commendPart2, char* commendPart3, ListSection* listSection) {
    //wywolanie funkcji od licznia elemwntow 
    if (commendPart3[0] == '?') {
        CommandAmountOf(commendPart1, commendPart2, listSection);
        return;
    }
    //wywołanie funkcji do usuwania 
    if (commendPart2 == 'D') {
        CommandDelete(commendPart1, commendPart3, listSection);
        return;
    }
    //obsługa komendy - wypisz wartosc atrybutu dla i-tej sekcji o nazwie -commandPart3 
    if (commendPart2 == 'E') {
        Section* current = listSection->lastnode;
        int position = -1;
        while (current != NULL) {
            position = current->IsInBlock(commendPart1);
            if (position != -1) {
                int atrybutsPosition = current->blocks[position].atrybuts->FindPosition(commendPart3);
                if (atrybutsPosition != -1) {
                    cout << commendPart1 << ",E," << commendPart3 << " == ";
                    cout << current->blocks[position].atrybutsvalue->GetElement(atrybutsPosition)->text << endl;
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
        //i,A,n
        CommandAtrybutsValue(n, commendPart3, listSection);
        return;
    }
    if (commendPart2 == 'S') {
        int j = ConvertToInt(commendPart3);
        //i,S,j
        CommandSelector(n, j, listSection);
        return;
    }
}

bool ReadLine(char text[MAXCOMMANDLENGTH]) {
    char x;
    int i = 0;
    while ((x = getchar()) != EOF) {
       
        if (x == '\n' && i != 0) 
            break;
        if (x == '\n' && i == 0) 
            break;
        if (x == '\t')
            continue;
        if (x == '\v')
            continue;
        if (x == '\f')
            continue;
        if (x == '\r')
            continue;
        if (x < ' ' || x > '~')
            continue;
        text[i] = x;
        i++;
    }
    if (i == 0 && x == EOF) return false;
    text[i] = '\0';
    i++;
    return true;
}

bool ApplyComand(ListSection* listSection) {
    char x;
    char text[MAXCOMMANDLENGTH];
    while (true) {
        if (!ReadLine(text)) return false;
        if (text[0] == '*') {
            break;
        }
        if (text[0] == '@') continue;
        if (text[3] == '*') {
            break;
        }
        //obsługa komendy ? - wypisanie liczby blokow css
        if (text[0] == '?' && text[1] == '\0') {
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
        if (text[0] == '\0')continue;
        //podzial wcztanej komendy na 3 czesci 
        //commendPart1 - do pierwszego przecinka 

        char commendPart1[MAXCOMMANDLENGTH];
        //char okreslacjacy typ komendy  S,A,D,E
        char commendPart2;
        // cała reszta po 3-cim przecinku 
        char commendPart3[MAXCOMMANDLENGTH];
        int i = 0;
        for (i; i < MAXCOMMANDLENGTH; i++) {
            if (text[i] == ',') {
                commendPart1[i] = '\0';
                break;
            }
            commendPart1[i] = text[i];
        }
        commendPart2 = text[i + 1];
        int j = 0;
        i = i + 3;//pominiecie przecinkow 
        for (i; i < MAXCOMMANDLENGTH; i++) {
            if ((text[i] == ',') || (text[i] == '\0')) {
                commendPart3[j] = '\0';
                break;
            }
            commendPart3[j] = text[i];
            j++;
        }
        if (i > MAXCOMMANDLENGTH)break;
        //wywolanie funkcji juz z podzialem komendy na 3 czesci
        Command(commendPart1, commendPart2, commendPart3, listSection);
    }
    return true;
}
//sprawdza czy char x jest dopuszczalnym charem 
bool CheckChar(char x) {
    if (x == '\t')
        return false;
    if (x == '\v')
        return false;
    if (x == '\f')
        return false;
    if (x == '\r')
        return false;
    if (x < ' ' || x > '~')
        return false;
    return true;
}
