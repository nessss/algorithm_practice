#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "pp.h"

using namespace std;

void swap( vector<int> &vec, int i, int j )
{
    int tmp = vec[i];
    vec[i] = vec[j];
    vec[j] = tmp;
}

void swap( vector<int>::iterator i, vector<int>::iterator j )
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

void swap( vector<int>::reverse_iterator i, vector<int>::reverse_iterator j )
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

void negativesort( vector<int> &vec )
{
    int comparisons = 0;
    bool sorted = true;
    do
    {
        sorted = true;
        for( auto it = vec.begin(); it + 1 != vec.end(); ++it )
        {
            if( *it >= 0 && *(it + 1) < 0 )
            {
                swap( it, it +1 );
                sorted = false;
            }
            ++comparisons;
        }

        if( sorted ) break;

        sorted = true;

        for( auto it = vec.rbegin(); it + 1 != vec.rend(); ++it )
        {
            if( *it < 0 && *(it + 1) >= 0 )
            {
                swap( it, it + 1 );
                sorted = false;
            }
            ++comparisons;
        }
    } while( !sorted );

    cout << "sort of " << vec.size() << " elements completed in " << comparisons << " comparisons" << endl;
}

void test( int max_value, mt19937 gen )
{
    vector<int> input_sequence;

    for( int i = max_value * -1; i <= max_value; ++i )
    {
        input_sequence.push_back( i );
    }

    shuffle( input_sequence.begin(), input_sequence.end(), gen );
    //pprint( input_sequence.begin(), input_sequence.end(), "input sequence" );

    negativesort( input_sequence );

    //pprint( input_sequence.begin(), input_sequence.end(), "sorted sequence" );
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );

    test( 10, gen );
    test( 100, gen );
    test( 1000, gen );
    test( 10000, gen );
}
