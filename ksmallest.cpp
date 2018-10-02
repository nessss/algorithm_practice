#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <chrono>
#include "pp.h"

using namespace std;

set<int> find_k_smallest( vector<int> &vec, unsigned int k )
{
    set<int> result;
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        if( result.empty() || result.size() < k )
        {
            result.insert( *it );
            continue;
        }
        if( *it <= *(result.rbegin()) )
        {
            result.insert( *it );
            if( result.size() >= k )
            {
                result.erase( *(result.rbegin()) );
            }
        }
    }

    return result;
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<int> dist( 0, 50 );

    vector<int> input_sequence;

    for( int i = 0; i < 50; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    pprint( input_sequence.begin(), input_sequence.end(), "input sequence" );

    auto begin = chrono::high_resolution_clock::now();
    set<int> ksmallest = find_k_smallest( input_sequence, 8 );
    auto end = chrono::high_resolution_clock::now();

    pprint( ksmallest.begin(), ksmallest.end(), "k smallest elements" );
    cout << "took " << chrono::duration_cast<chrono::microseconds>( end - begin ).count() << " microseconds for " << input_sequence.size() << " elements" << std::endl;

    for( int i = 0; i < 450; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    begin = chrono::high_resolution_clock::now();
    ksmallest = find_k_smallest( input_sequence, 8 );
    end = chrono::high_resolution_clock::now();

    pprint( ksmallest.begin(), ksmallest.end(), "k smallest elements" );
    cout << "took " << chrono::duration_cast<chrono::microseconds>( end - begin ).count() << " microseconds for " << input_sequence.size() << " elements" << std::endl;

    for( int i = 0; i < 4500; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    begin = chrono::high_resolution_clock::now();
    ksmallest = find_k_smallest( input_sequence, 8 );
    end = chrono::high_resolution_clock::now();

    pprint( ksmallest.begin(), ksmallest.end(), "k smallest elements" );
    cout << "took " << chrono::duration_cast<chrono::microseconds>( end - begin ).count() << " microseconds for " << input_sequence.size() << " elements" << std::endl;

    for( int i = 0; i < 45000; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    begin = chrono::high_resolution_clock::now();
    ksmallest = find_k_smallest( input_sequence, 8 );
    end = chrono::high_resolution_clock::now();

    pprint( ksmallest.begin(), ksmallest.end(), "k smallest elements" );
    cout << "took " << chrono::duration_cast<chrono::microseconds>( end - begin ).count() << " microseconds for " << input_sequence.size() << " elements" << std::endl;

}
