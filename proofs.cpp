#include <iostream>

int multiply( int y, int z, int c )
{
    if( z == 0 ) return 0;
    return multiply( c * y, ( z / c ), c ) + ( y * ( z % c ) );
}

void test_multiply()
{
    int c, result;
    result = 0;
    for( c = 2; c < 50; ++c )
    {
        int result = multiply( 3, 4, c );
        if( result == 3 * 4 )
        {
            std::cout << "algorithm is correct for c = " << c << std::endl << std::endl;
        }
        else
        {
            std::cout << "algorithm is incorrect for c = " << c << std::endl;
            std::cout << "result: " << result << std::endl << std::endl;
        }
    }
}

int main( int argv, char *argc[] )
{
    test_multiply();
}
