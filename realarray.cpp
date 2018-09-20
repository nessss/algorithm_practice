#include <iostream>
#include <vector>
#include <random>

template <typename Iterator>
void print_range( Iterator begin, Iterator end )
{
    std::cout << "{ ";
    for( auto it = begin; it != end; ++it )
    {
        std::cout << *it;
        if( it + 1 != end )
        {
            std::cout << ",";
        }
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

float add( std::vector<float> *vec, int i, float y )
{
    (*vec)[i] += y;
    return (*vec)[i];
}

float partial_sum( std::vector<float> *vec, int i )
{
    float result = 0.0;
    for( int j = 0; j < i; ++j )
    {
        result += (*vec)[i];
    }
    return result;
}

int main( int argv, char *argc[] )
{
    std::random_device rd;
    std::mt19937 gen( rd() );

    std::vector<float> data;

    for( int i = 0; i < 20; ++i )
    {
        data.push_back( (float) i / 2.0 );
    }

    std::shuffle( data.begin(), data.end(), gen );

    print_range( data.begin(), data.end() );

    std::cout << add( &data, 3, 2.3 ) << std::endl;

    print_range( data.begin(), data.end() );

    std::cout << partial_sum( &data, 5 );
}
