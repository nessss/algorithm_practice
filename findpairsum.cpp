#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "pp.h"

std::pair<int, int> find_summing_pair( std::vector<int> &S1, std::vector<int> &S2, int x )
{
    for( auto it_1 = S1.cbegin(); it_1 != S1.cend(); ++it_1 )
    {
        if( *it_1 > x ) continue;
        for( auto it_2 = S2.cbegin(); it_2 != S2.cend(); ++it_2 )
        {
            if( *it_1 + *it_2 == x ) return std::make_pair( *it_1, *it_2 );
        }
    }

    return std::make_pair( -1, -1 );
}

int main()
{
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> input_dist( 1, 200 );

    std::vector<int> S1, S2;

    for( int i = 0; i < 500; ++i )
    {
        S1.push_back( input_dist( gen ) );
        S2.push_back( input_dist( gen ) );
    }

    //pprint( S1.begin(), S1.end(), "S1" );
    //pprint( S2.begin(), S2.end(), "S2" );

    std::uniform_int_distribution<int> test_dist( 1, 400 );
    std::chrono::time_point<std::chrono::high_resolution_clock> begin, end;
    int x;

    for( int i = 0; i < 10; ++i )
    {
        begin = std::chrono::high_resolution_clock::now();
        x = test_dist( gen );
        auto pair = find_summing_pair( S1, S2, x );
        end = std::chrono::high_resolution_clock::now();

        if( pair.first != -1 )
        {
            std::cout << "found pair which sums to " << x << ": " << pair.first << ", " << pair.second << std::endl;
        }
        else
        {
            std::cout << "didn't find pair which sums to " << x << std::endl;
        }

        std::cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>( end - begin ).count() << " microseconds" << std::endl;
    }
}
