#include <iostream>
#include <set>

template <class T>
void print_set( std::set<T> *s )
{
    std::cout << "{ ";
    for( auto it = s->begin(); it != s->end(); ++it )
    {
        std::cout << *it;
        if( std::next( it ) != s->end() )
        {
            std::cout << ",";
        }
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

std::set<int> generate_ramanujan_numbers( int n )
{
    std::set<int> result;
    int num;
    for( int a = 1; a < n; ++a )
    {
        for( int b = 1; b < n; ++b )
        {
            for( int c = 1; c < n; ++c )
            {
                for( int d = 1; d < n; ++d )
                {
                    num = ( a * a * a ) + ( b * b * b );
                    if(
                            num == ( c * c * c ) + ( d * d * d )  &&
                            a != c &&
                            a != d &&
                            result.count( num ) == 0 )
                    {
                        std::cout << "found Ramanujan number: " << num;
                        std::cout << " = " << a << "^3 + " << b << "^3 = ";
                        std::cout << c << "^3 + " << d << "^3" << std::endl;
                        result.insert( num );
                    }
                }
            }
        }
    }
    return result;
}

int main( int argv, char *argc[] )
{
    std::set<int> ramanujan_numbers = generate_ramanujan_numbers( 20 );
}
