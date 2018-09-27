#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "pp.h"

std::vector<std::pair<int, int>> partition( std::vector<int> &vec )
{
    std::vector<int> sorted( vec.begin(), vec.end() );
    std::sort( sorted.begin(), sorted.end() );

    std::vector<std::pair<int, int>> result;

    while( !sorted.empty() )
    {
        result.push_back( std::make_pair( sorted.front(), sorted.back() ) );
        sorted.erase( sorted.begin() );
        sorted.erase( sorted.end() - 1 );
    }

    return result;
}

int main( int argc, char *argv[] )
{
    int n = 4;
    if( argc > 1  )
    {
        int arg_n = std::stoi( argv[1] );
        if( arg_n > 0 ) n = arg_n;
    }

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> distribution( 1, 20 );

    std::vector<int> input_vector;

    for( int i = 0; i < 2 * n; ++i )
    {
        input_vector.push_back( distribution( gen ) );
    }

    pprint( input_vector.begin(), input_vector.end(), "input vector" );

    std::vector<std::pair<int, int>> pairs = partition( input_vector );

    //pprint( pairs.begin(), pairs.end(), "partitioned pairs" );

    std::cout << "partitioned pairs: { ";
    for( auto it = pairs.begin(); it != pairs.end(); ++it )
    {
        std::cout << "(" << (*it).first << ", " << (*it).second << "), ";
    }
    std::cout << "\b\b }" << std::endl;
}
