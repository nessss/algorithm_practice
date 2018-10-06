#include <iostream>
#include <vector>
#include <random>
#include "heap.h"
#include "pp.h"

using namespace std;

template <typename T>
void print_info( max_heap<T> &heap )
{

    cout << "max: " << heap.max() << endl;
    cout << "size: " << heap.size() << endl;
    cout << "capacity: " << heap.capacity() << endl;
    cout << "contents: " << endl << "{" << endl;
    for( unsigned int i = 0; i < heap.size(); ++i )
    {
        cout << '\t' << heap.at( i );
        if( ( i + 1 ) != heap.size() ) cout << ", " << endl;
        else cout << endl;
    }
    cout << "}" << endl;
}

int main()
{
    max_heap<int> heap;

    heap.insert( 3 );

    print_info( heap );

    heap.insert( 5 );

    heap.insert( 2 );

    print_info( heap );

    //return 0;

    //heap.erase( 5 );

    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<int> dist( 0, 1000 );

    for( int i = 0; i < 5; ++i )
    {
        heap.insert( dist( gen ) );
        print_info( heap );
    }
}
