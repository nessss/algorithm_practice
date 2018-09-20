#include <iostream>
#include <string>
#include "linkedlist.h"
#include "doublylinkedlist.h"

int main( int argv, char *argc[] )
{
    LinkedList<std::string> list;

    list.InsertSorted( "foo" );
    list.InsertSorted( "bar" );
    list.InsertSorted( "pubup" );
    list.InsertSorted( "mugum" );

    list.PrintList();

    list.InsertSorted( "aaa" );
    list.PrintList();

    list.InsertSorted( "zzz" );
    list.PrintList();

    list.InsertSorted( "lemgthy" );
    list.PrintList();

    list.InsertSorted( "lomg" );
    list.PrintList();

    list.Clear();

    return 0;
}
