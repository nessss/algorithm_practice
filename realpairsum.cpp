#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

bool find_pair_sum_sorted( std::vector<float> &vec, float x, std::pair<float, float> &result )
{
    for( auto it = vec.begin(); it != vec.end() - 1; ++it )
    {
        if( *it + *(it + 1) == x )
        {
            result = std::make_pair( *it, *(it + 1) );
            return true;
        }
        else if( *it + *(it + 1) > x ) return false;
    }
    return false;
}

bool find_pair_sum_unsorted( std::vector<float> &vec, float x, std::pair<float, float> &result )
{
    std::vector<float> sorted( vec.begin(), vec.end() );
    std::sort( sorted.begin(), sorted.end() );
    return find_pair_sum_sorted( sorted, x, result );
}

int main()
{
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_real_distribution<float> input_dist( 0.0, 10.0 );

    std::vector<float> input_set;

    for( int i = 0; i < 1000; ++i )
    {
        input_set.push_back( input_dist( gen ) );
    }

    std::uniform_real_distribution<float> test_dist( 0.1, 20.0 );

    std::pair<float, float> result;
    float x;

    std::cout << "---------- unsorted ----------" << std::endl;

    for( int i = 0; i < 20; ++i )
    {
        x = test_dist( gen );
        if( find_pair_sum_unsorted( input_set, x, result ) )
        {
            std::cout << "found pair which sums to " << x << ": " << result.first << ", " << result.second << std::endl;
        }
        else
        {
            std::cout << "didn't find pair which sums to " << x << std::endl;
        }
    }

    std::cout << "----------- sorted -----------" << std::endl;

    std::sort( input_set.begin(), input_set.end() );

    for( int i = 0; i < 20; ++i )
    {
        x = test_dist( gen );
        if( find_pair_sum_sorted( input_set, x, result ) )
        {
            std::cout << "found pair which sums to " << x << ": " << result.first << ", " << result.second << std::endl;
        }
        else
        {
            std::cout << "didn't find pair which sums to " << x << std::endl;
        }
    }
}
