


#include <iostream>
using namespace std;
class ListSelektors {

};
class ListAtrybuts {

};
class Block {
    ListSelektors selectors;
    ListAtrybuts atrybuts;
};
class ListSection {
    Block Blocks[8];
    ListSection* prev;
    ListSection* next;

};
int main()
{
    cout << "Hello World!\n";
}

