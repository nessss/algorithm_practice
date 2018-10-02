#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>
#include "pp.h"

using namespace std; 

unordered_set<int> find_very_frequent( vector<int> &vec )
{
    unordered_set<int> result;
    unordered_multiset<int> counts;
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        counts.insert( *it );
        if( counts.count( *it ) > ( vec.size() / 2 ) )
        {
            result.insert( *it );
        }
    }

    return result;
}

unordered_set<int> find_frequent( vector<int> &vec )
{
    unordered_set<int> result;
    unordered_multiset<int> counts;
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        counts.insert( *it );
        if( counts.count( *it ) > ( vec.size() / 4 ) )
        {
            result.insert( *it );
        }
    }

    return result;
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<int> base_dist( 0, 9 );
    uniform_int_distribution<int> frequent_dist( 0, 3 );
    uniform_int_distribution<int> very_frequent_dist( 0, 1 );
    vector<int> input_sequence;

    for( int i = 0; i < 50; ++i )
    {
        input_sequence.push_back( base_dist( gen ) );
        input_sequence.push_back( frequent_dist( gen ) );
        input_sequence.push_back( frequent_dist( gen ) );
        input_sequence.push_back( very_frequent_dist( gen ) );
        input_sequence.push_back( very_frequent_dist( gen ) );
        input_sequence.push_back( 0 );
        input_sequence.push_back( 0 );
        input_sequence.push_back( 0 );
        input_sequence.push_back( 0 );
    }

    pprint( input_sequence.begin(), input_sequence.end(), "input sequence" );

    unordered_set<int> very_frequent = find_very_frequent( input_sequence );
    pprint( very_frequent.begin(), very_frequent.end(), "very frequent elements" );

    unordered_set<int> frequent = find_frequent( input_sequence );
    pprint( frequent.begin(), frequent.end(), "frequent elements" );
}
