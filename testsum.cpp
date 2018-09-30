#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <algorithm>
#include <bitset>
#include <cmath>
#include "pp.h"

using namespace std;

int sum_range( deque<int> deq )
{
    int result = 0;
    for( auto it = deq.begin(); it != deq.end(); ++it )
    {
        result += *it;
    }
    return result;
}

template <int size>
bool has_subset_sum( const int t, const int k, const vector<int> &s )
{
    deque<int> sorted( s.begin(), s.end() );
    sort( sorted.rbegin(), sorted.rend() );

    /*
    // remove elements too large to be a part of the sum
    while( sorted.front() > t ) sorted.pop_front();

    // if we removed too many elements to have k elements left, return false
    if( sorted.size() < k ) return false;
    */

    int k_largest_sum = sum_range( deque<int>( sorted.begin(), sorted.begin() + k ) );

    // if the sum of the k largest elements in s are smaller than t,
    // there's no way we can find a subset that sums to t
    if( k_largest_sum < t ) return false;
    else if( k_largest_sum == t ) return true;

    int k_smallest_sum = sum_range( deque<int>( sorted.rbegin(), sorted.rbegin() + k ) );

    // if the sum of the k smallest elements in s are larger than t,
    // there's no way we can find a subset that sums to t
    if( k_smallest_sum > t ) return false;
    else if( k_smallest_sum == t ) return true;

    // here's where it gets complicated...

    // generate all permutations of k bits in an n-sized bit field
    vector<bitset<size>> combinations;
    for( int i = 0; i < exp2( sorted.size() ); ++i )
    {
        bitset<size> bits( i );
        if( bits.count() == k )
        {
            combinations.push_back( bits );
            int sum = 0;
            vector<int> members;
            for( int i = 0; i < size; ++i )
            {
                if( bits[i] )
                {
                    sum += sorted[i];
                    members.push_back( sorted[i] );
                }
            }
            if( sum == t )
            {
                pprint( members.begin(), members.end(), "k" );
                return true;
            }
        }
    }

    return false;
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<int> dist( 1, 100 );

    vector<int> s;

    for( int i = 0; i < 20; ++i )
    {
        s.push_back( dist( gen ) );
    }

    pprint( s.begin(), s.end(), "S" );

    bool found_t;
    for( int t = 1; t < 100; ++t )
    {
        for( int k = 1; k < s.size(); ++k )
        {
            found_t = has_subset_sum<20>( t, k, s );
            if( found_t )
                cout << "S has a subset of size " << k << " equal to " << t << endl;
            //else
                //cout << "S does not have a subset of size " << k << " equal to " << t << endl;
        }
    }
}
