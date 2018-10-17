#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "pp.h"

using namespace std;
using namespace std::chrono;

vector<int> duplicatesort( vector<int> &vec )
{
    map<int, int> counts;

    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        ++counts[*it];
    }

    vector<int> result;

    for( auto it = counts.begin(); it != counts.end(); ++it )
    {
        while( (*it).second > 0 )
        {
            result.push_back( (*it).first );
            --(*it).second;
        }
    }

    return result;
}

void test( int n, mt19937 gen, bool print = false )
{
    uniform_int_distribution<int> dist( 0, log2( n ) );
    vector<int> input_sequence;
    input_sequence.reserve( n );

    for( int i = 0; i < n; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    if( print ) pprint( input_sequence.begin(), input_sequence.end(), "input" );

    auto begin = high_resolution_clock::now();
    vector<int> sorted = duplicatesort( input_sequence );
    auto end = high_resolution_clock::now();

    if( print ) pprint( sorted.begin(), sorted.end(), "sorted" );

    sort( input_sequence.begin(), input_sequence.end() );
    if( sorted != input_sequence ) cout << "sort failed" << endl;
    else
    {
        int micros = duration_cast<microseconds>( end - begin ).count();
        cout << "sort succeeded in " << micros << " microseconds for " << n << " elements" << endl;
        cout << "time per element: " << (float)micros / n << " microseconds" << endl;
        cout << "n*log(log(n)): " << n * log2( log2( (float)n ) ) << endl;
    }
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );
    test( 50, gen, true );
    test( 500, gen );
    test( 5000, gen );
    test( 50000, gen );
    test( 500000, gen );
    test( 5000000, gen );
    test( 50000000, gen );
}
