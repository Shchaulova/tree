#include <iostream>

#include "tree.h"

using namespace std;

int main()

{

    Container* c = new Tree();



    for(int i = 1; i < 10; i++)

        c->insert(i*i);



    printf("List after creation:\n");

    c->print();



    if(c->exists(25))

        cout << "Search for value 25: found" << endl;



    if(!c->exists(111))

        cout << "Search for value 111: not found" << endl;



    c->remove(25);

    cout << "List after deletion of the element:" << endl;

    c->print();



    delete c;

    return 0;

}