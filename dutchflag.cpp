#include <iostream>
#include <vector>
#include <deque>
#include <random>
#include <string>
#include "pp.h"

using namespace std;

void colorprint( vector<int> &vec, string label )
{
    cout << label << ": { ";
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        switch( *it )
        {
            case 0:
                cout << "red, ";
                break;
            case 1:
                cout << "white, ";
                break;
            case 2:
                cout << "blue, ";
                break;
        }
    }
    cout << "\b\b }" << endl;
}

void swap( vector<int> &vec, int lhs, int rhs )
{
    int tmp = vec[lhs];
    vec[lhs] = vec[rhs];
    vec[rhs] = tmp;
}

void flagsort( vector<int> &vec )
{
    deque<int> red_white_indices;
    for( unsigned int i = 0; i < vec.size(); ++i )
    {
        if( vec[i] == 2 )
        {
            if( !red_white_indices.empty() )
            {
                cout << "swapping " << i << " and " << red_white_indices.front() << endl;
                swap( vec, i, red_white_indices.front() );
                red_white_indices.pop_front();
                red_white_indices.push_back( i );
            }
        }
        else
        {
            red_white_indices.push_back( i );
        }
    }

    colorprint( vec, "blues sorted" );

    deque<int> red_indices;

    for( unsigned int i = vec.size() - red_white_indices.size(); i < vec.size(); ++i )
    {
        if( vec[i] == 1 )
        {
            if( red_indices.size() > 0 )
            {
                swap( vec, i, red_indices.front() );
                red_indices.pop_front();
                red_indices.push_back( i );
            }
        }
        else
        {
            red_indices.push_back( i );
        }
    }
}

int main()
{
    random_device rd;
    mt19937 gen( rd() );
    uniform_int_distribution<int> dist( 0, 2);

    vector<int> input_sequence;

    for( int i = 0; i < 50; ++i )
    {
        input_sequence.push_back( dist( gen ) );
    }

    colorprint( input_sequence, "input sequence" );

    flagsort( input_sequence );

    colorprint( input_sequence, "sorted" );
}
