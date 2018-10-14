#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include "pp.h"

using namespace std;
using namespace std::chrono;

vector<int> mysort( vector<int> &vec, int k )
{
    vector<int> counts( k );

    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        ++counts[(*it) - 1];
    }

    vector<int> result;
    int idx = 0;

    for( unsigned int i = 0; i < vec.size(); ++i )
    {
        if( counts[idx] > 0 )
        {
            result.push_back( idx + 1 );
            --counts[idx];
        }
        else
        {
            while( counts[idx] == 0 ) ++idx;
            result.push_back( idx + 1 );
            --counts[idx];
        }
    }

    return result;
}

vector<int> mysort2( vector<int> &vec )
{
    map<int, int> counts;

    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        ++counts[*it];
    }

    vector<int> result;
    result.reserve( vec.size() );

    for( auto it = counts.begin(); it != counts.end(); ++it )
    {
        while( (*it).second > 0 )
        {
            result.push_back( (*it).first );
            ((*it).second)--;
        }
    }

    return result;
}

void test( int n, int k, mt19937 gen )
{
    uniform_int_distribution<int> dist( 1, k );

    vector<int> input_sequence;

    for( int i = 0; i < n; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    auto begin = high_resolution_clock::now();
    vector<int> sorted = mysort( input_sequence, k );
    auto end = high_resolution_clock::now();

    cout << "took " << duration_cast<microseconds>( end - begin ).count() << " microseconds for " << n << " elements in the range 1, " << k << " when k is known" << endl;

    begin = high_resolution_clock::now();
    sorted = mysort2( input_sequence );
    end = high_resolution_clock::now();

    cout << "took " << duration_cast<microseconds>( end - begin ).count() << " microseconds for " << n << " elements in the range 1, " << k << " when k is unknown" << endl;
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );

    test( 500, 5, gen );
    test( 500, 10, gen );
    test( 500, 50, gen );
    test( 500, 100, gen );
    test( 500, 500, gen );
}
