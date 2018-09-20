#include <iostream>
#include <stdexcept>
#include <random>

int integer_division( int x, int y )
{
    int result = 0;

    /* return early on trivial cases */
    if( x == 0 ) return 0;
    if( y == 0 ) throw std::overflow_error( "Divide by zero exception" );

    /* handle negative numbers appropriately */
    bool negative = false;

    if( x < 0 )
    {
        negative = !negative;
        x = x - x - x;
    }
    if( y < 0 )
    {
        negative = !negative;
        y = y - y - y;
    }

    /* do the division */
    while( x - y >= 0 )
    {
        x -= y;
        result++;
    }

    /* make result negative if appropriate */
    if( negative )
    {
        result = result - result - result;
    }

    return result;
}

bool test_case_integer_division( int x, int y )
{
    if( integer_division( x, y ) != x / y )
    {
        std::cout << "FAIL: integer_division( " << x << ", " << y << " ) != " << x / y << std::endl;
        std::cout << "actual result: " << integer_division( x, y ) << std::endl;
        return false;
    }
    else
    {
        std::cout << "PASS: integer_division( " << x << ", " << y << " ) == " << x / y << std::endl;
        return true;
    }
}

void test_integer_division()
{
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> dis( 1, 10000 );

    int tests = 20;
    int failed_cases = 0;

    std::cout << "--------------------" << std::endl;
    std::cout << "Test case: integer_division( int x, int y )" << std::endl << std::endl;

    for( int i = 0; i < tests; ++i )
    {
        if( !test_case_integer_division( dis( gen ), dis( gen ) ) ) ++failed_cases;
    }

    bool threw_exception = false;
    try
    {
        test_case_integer_division( 5, 0 );
    }
    catch( std::overflow_error e )
    {
        std::cout << "PASS: exception thrown for divide by zero" << std::endl;
        threw_exception = true;
    }
    if( !threw_exception ) ++failed_cases;

    if( failed_cases == 0 )
    {
        std::cout << std::endl << "Passed all tests for integer_division( int x, int y )" << std::endl;
    }
    else
    {
        std::cout << "Failed " << failed_cases << " tests for integer_division( int x, int y )" << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

int main( int argv, char *argc[] )
{
    test_integer_division();
}
