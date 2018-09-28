#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>
#include "pp.h"

template <typename T>
int find_mode( std::vector<T> &vec)
{
    std::unordered_multiset<T> counts;
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        counts.insert( *it );
    }

    int max = -1;
    int last = 0;
    int max_count = 0;
    int count = 0;
    bool first = true;

    for( auto it = counts.begin(); it != counts.end(); ++it )
    {
        if( first )
        {
            first = false;
        }
        else if( *it == last ) continue;

        count = counts.count( *it );
        if( count > max_count )
        {
            max_count = count;
            max = *it;
        }

        last = *it;
    }

    return max;
}

int main()
{
    std::vector<int> input_sequence;

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> dist( 0, 9 );

    for( int i = 0; i < 40; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    pprint( input_sequence.begin(), input_sequence.end(), "input sequence" );

    int mode = find_mode<int>( input_sequence );

    std::cout << "mode: " << mode << std::endl;

    std::sort( input_sequence.begin(), input_sequence.end() );

    pprint( input_sequence.begin(), input_sequence.end() );
}
