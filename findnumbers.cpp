#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <algorithm>

std::pair<int, int> max_difference( std::vector<int> &vec )
{
    int max = 0, min = 100;
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        if( *it > max ) max = *it;
        if( *it < min ) min = *it;
    }

    return std::make_pair( max, min );
}

std::pair<int, int> max_difference_sorted( std::vector<int> &vec )
{
    return std::make_pair( vec.back(), vec.front() );
}

std::pair<int, int> min_difference_sorted( std::vector<int> &vec )
{
    if( vec.size() < 2 ) return std::make_pair( -1, -1 );

    int *x = NULL, *y = NULL;
    for( auto it = vec.begin(); it + 1 != vec.end(); ++it )
    {
        if( x == NULL )
        {
            x = new int( *it );
            y = new int( *(it + 1) );
            continue;
        }
        if( abs( *it - *(it + 1) ) < abs( *x - *y ) )
        {
            *x = *it;
            *y = *(it + 1);
        }
        if( abs( *x - *y ) == 0 ) break;
    }

    std::pair<int, int> result;
    if( *x > *y )
    {
        result = std::make_pair( *x, *y );
        delete x;
        delete y;
    }
    else
    {
        result = std::make_pair( *y, *x );
        delete x;
        delete y;
    }

    return result;
}

std::pair<int, int> min_difference( std::vector<int> &vec )
{
    std::vector<int> sorted( vec.begin(), vec.end() );
    std::sort( sorted.begin(), sorted.end() );

    return min_difference_sorted( sorted );
}

template <typename T>
void print_vector( std::vector<T> &vec, std::string label = "" )
{
    if( label != "" ) std::cout << label << ": ";
    std::cout << "{ ";
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;
}

void test_algorithms( int vector_size )
{
    std::mt19937 generator;
    generator.seed( 
            std::chrono::high_resolution_clock::now().time_since_epoch().count() );
    std::uniform_int_distribution<int> distribution( 1, 100 );

    std::vector<int> S_a, S_b, S_c, S_d;

    auto setup_begin = std::chrono::high_resolution_clock::now();
    for( int i = 0; i < vector_size; ++i )
    {
        S_a.push_back( distribution( generator ) );
        S_b.push_back( distribution( generator ) );
        S_c.push_back( distribution( generator ) );
        S_d.push_back( distribution( generator ) );

        std::sort( S_b.begin(), S_b.end() );
        std::sort( S_d.begin(), S_d.end() );
    }
    auto setup_end = std::chrono::high_resolution_clock::now();

    auto begin = std::chrono::high_resolution_clock::now();

    //print_vector( S_a, "S_a" );
    auto a_begin = std::chrono::high_resolution_clock::now();
    auto max_difference_pair = max_difference( S_a );
    auto a_end = std::chrono::high_resolution_clock::now();

    //print_vector( S_b, "S_b" );
    auto b_begin = std::chrono::high_resolution_clock::now();
    auto max_difference_sorted_pair = max_difference_sorted( S_b );
    auto b_end = std::chrono::high_resolution_clock::now();

    //print_vector( S_c, "S_c" );
    auto c_begin = std::chrono::high_resolution_clock::now();
    auto min_difference_pair = min_difference( S_a );
    auto c_end = std::chrono::high_resolution_clock::now();

    //print_vector( S_d, "S_d" );
    auto d_begin = std::chrono::high_resolution_clock::now();
    auto min_difference_sorted_pair = min_difference_sorted( S_a );
    auto d_end = std::chrono::high_resolution_clock::now();

    auto end = std::chrono::high_resolution_clock::now();

    auto print_begin = std::chrono::high_resolution_clock::now();
    std::cout << "array construction took : " << std::chrono::duration_cast<std::chrono::microseconds>( setup_end - setup_begin ).count() << " microseconds" << std::endl;
    std::cout << "pair which maximizes x-y in S_a: " << max_difference_pair.first << ", " << max_difference_pair.second << std::endl;
    std::cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>( a_end - a_begin ).count() << " microseconds" << std::endl;
    std::cout << "pair which maximizes x-y in S_b: " << max_difference_sorted_pair.first << ", " << max_difference_sorted_pair.second << std::endl;
    std::cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>( b_end - b_begin ).count() << " microseconds" << std::endl;
    std::cout << "pair which minimizes x-y in S_c: " << min_difference_pair.first << ", " << min_difference_pair.second << std::endl;
    std::cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>( c_end - c_begin ).count() << " microseconds" << std::endl;
    std::cout << "pair which minimizes x-y in S_d: " << min_difference_sorted_pair.first << ", " << min_difference_sorted_pair.second << std::endl;
    std::cout << "took " << std::chrono::duration_cast<std::chrono::microseconds>( d_end - d_begin ).count() << " microseconds" << std::endl;

    std::cout << "total time: " << std::chrono::duration_cast<std::chrono::microseconds>( end - begin ).count() << " microseconds" << std::endl;
    auto print_end = std::chrono::high_resolution_clock::now();

    std::cout << "printing results took: " << std::chrono::duration_cast<std::chrono::microseconds>( print_end - print_begin ).count() << " microseconds" << std::endl;
}

int main()
{
    test_algorithms( 100 );
    std::cout << "--------------------" << std::endl;
    test_algorithms( 1000 );
    std::cout << "--------------------" << std::endl;
    test_algorithms( 10000 );
}
