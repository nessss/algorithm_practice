#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>

template <typename T>
void print_vector( std::vector<T> &vec )
{
    std::cout << "{ ";
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;
}

std::vector<long> naive_algorithm( std::vector<long> &X )
{
    std::vector<long> result;

    long product;

    int operations = 0;

    for( auto i_it = X.begin(); i_it != X.end(); ++i_it )
    {
        product = 1;
        for( auto j_it = X.begin(); j_it != X.end(); ++j_it )
        {
            if( i_it != j_it )
            {
                product *= *j_it;
                ++operations;
            }
        }
        result.push_back( product );
    }

    std::cout << "algorithm completed in " << operations << " operations with naive algorithm" << std::endl;
    return result;
}

/*
inline size_t key( int i, int j )
{
    return (size_t) i << 32 | (unsigned int) j;
}
*/

std::vector<long> better_algorithm( std::vector<long> &X )
{
    std::vector<long> result;
    std::vector<long> pair_products;

    int operations = 0;

    for( int i = 0; i < X.size(); ++i )
    {
        pair_products.push_back( X[i] * X[(i + 1) % X.size()] );
        //std::cout << pair_products.back() << std::endl;
        ++operations;
    }

    long product;

    for( int i = 0; i < X.size(); ++i )
    {
        product = 1;
        for( int j = 0; j < (int)( X.size() * 0.5 ); ++j )
        {
            int key = ( i + 1 + ( 2 * j ) ) % X.size();
            if( key == ( i - 1 + X.size() ) % X.size() )
            {
                product *= X[ key ];
                std::cout << key << "*, ";
            }
            else
            {
                product *= pair_products[ key ];
                std::cout << key << ", ";
            }
            ++operations;
        }
        std::cout << "\b\b " << std::endl;
        result.push_back( product );
    }

    std::cout << "algorithm completed in " << operations << " operations with better algorithm" << std::endl;
    return result;
}

int main()
{
    std::default_random_engine generator;
    std::uniform_int_distribution<long> distribution( 1, 10 );

    std::vector<long> X;

    for( int i = 0; i < 30; ++i )
    {
        X.push_back( distribution( generator ) );
    }

    print_vector( X );

    std::vector<long> M = naive_algorithm( X );

    print_vector( M );

    std::vector<long> M2 = better_algorithm( X );

    print_vector( M2 );
}
