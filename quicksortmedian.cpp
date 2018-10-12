#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include "pp.h"

using namespace std;

random_device rd;
mt19937 gen( rd() );

float avg( int a, int b )
{
    return ( (float)a + (float)b ) / 2.0;
}

// return the index of the median of a sorted vector, as
// well as a bool to indicate whether it should be averaged
// with the next element, for even-sized vectors
pair<int, bool> median_idx( int vector_size )
{
    if( vector_size % 2 == 0 )
    {
        return make_pair( (vector_size / 2) - 1, true );
    }

    return make_pair( ( vector_size / 2 ), false );
}

pair<int, bool> median_idx( vector<int> &vec )
{
    return median_idx( vec.size() );
}

template <typename T>
int find_median( vector<T> &vec, int target_idx = -1 )
{
    if( target_idx == -1 ) target_idx = median_idx( vec ).first;
    if( vec.size() == 1 ) return vec[0];

    T pivot = vec[ vec.size() / 2 ];

    vector<T> smaller;
    vector<T> larger;

    bool found_pivot = false;

    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        if( *it == pivot )
        {
            if( found_pivot )
            {
                larger.push_back( *it );
            }
            else
            {
                found_pivot = true;
            }
            continue;
        }
        if( *it > pivot )
        {
            larger.push_back( *it );
        }
        else
        {
            smaller.push_back( *it );
        }
    }

    int pivot_idx = smaller.size();
    if( pivot_idx == target_idx ) return pivot;

    if( pivot_idx > target_idx )
    {
        return find_median( smaller, target_idx );
    }
    else
    {
        return find_median( larger, target_idx - pivot_idx - 1);
    }
}

void test( int sequence_size, bool print_vectors = false )
{
    uniform_int_distribution<int> input_dist( 0, 1000 );
    vector<int> input_sequence;

    for( int i = 0; i < sequence_size; ++i )
    {
        input_sequence.push_back( input_dist( gen ) );
    }

    cout << "index of median in sorted vector of size " << input_sequence.size() << ": " << median_idx( input_sequence ).first << endl;

    auto begin = chrono::high_resolution_clock::now();
    int median = find_median( input_sequence );
    cout << endl;
    auto end = chrono::high_resolution_clock::now();

    cout << "median element: " << median << endl;
    sort( input_sequence.begin(), input_sequence.end() );
    if( print_vectors ) pprint( input_sequence.begin(), input_sequence.end(), "sorted" );
    cout << "actual median element: " << input_sequence[median_idx(input_sequence).first] << endl;
    int micros = chrono::duration_cast<chrono::microseconds>( end - begin).count();
    cout << "took " << micros << " microseconds for " << input_sequence.size() << " elements" << endl;
    cout << "time per element: " << (float)micros / input_sequence.size() << " microseconds" << endl;

}

int main()
{
    test( 11, true );

    test( 101 );
    test( 1001 );
    test( 10001 );
    test( 100001 );
    test( 1000001 );
    test( 10000001 );

    return 0;
}
