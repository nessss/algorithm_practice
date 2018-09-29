#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "pp.h"

using namespace std;

vector<int> find_union_sorted( const vector<int> &a, const vector<int> &b )
{
    vector<int> result;

    auto a_it = a.begin();
    auto b_it = b.begin();

    while( a_it != a.end() && b_it != b.end() )
    {
        if( *a_it == *b_it )
        {
            result.push_back( *a_it );
            ++a_it;
            ++b_it;
        }
        else if( *a_it < *b_it ) ++a_it;
        else ++b_it;
    }

    return result;
}

vector<int> find_union_unsorted( const vector<int> &a, const vector<int> &b )
{
    vector<int> a_sorted( a.begin(), a.end() );
    vector<int> b_sorted( b.begin(), b.end() );

    sort( a_sorted.begin(), a_sorted.end() );
    sort( b_sorted.begin(), b_sorted.end() );

    return find_union_sorted( a_sorted, b_sorted );
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<int> dist( 0, 100 );

    vector<int> a, b;

    for( int i = 0; i < 50; ++i )
    {
        a.push_back( dist( gen ) );
        b.push_back( dist( gen ) );
    }

    pprint( a.begin(), a.end(), "A" );
    pprint( b.begin(), b.end(), "B" );

    vector<int> unsorted_union = find_union_unsorted( a, b );

    pprint( unsorted_union.begin(), unsorted_union.end(), "unsorted" );

    sort( a.begin(), a.end() );
    sort( b.begin(), b.end() );
    vector<int> sorted_union = find_union_sorted( a, b );

    pprint( sorted_union.begin(), sorted_union.end(), "sorted" );
}
