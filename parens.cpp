#include <iostream>

int balanced( const char *str )
{
    int opens = 0;
    int idx = 0;
    int last_open_idx = 0;
    bool found_paren = false;
    while( *str != '\0' )
    {
        if( *str == '(' )
        {
            ++opens;
            found_paren = true;
            last_open_idx = idx;
        }
        else if( *str == ')' )
        {
            --opens;
            if( opens < 0 ) return idx;
            found_paren = true;
        }
        ++idx;
        ++str;
    }
    if( found_paren == false ) return -2;
    if( opens > 0 ) return last_open_idx;
    return -1;
}

void test( const char *str )
{
    int result = balanced( str );
    std::cout << "\"" << str << "\"";
    if( result == -1 )
    {
        std::cout << " has balanced parentheses." << std::endl;
    }
    else
    {
        if( result == -2 )
        {
            std::cout << " does not have parentheses." << std::endl;
        }
        else
        {
            std::cout << " has unbalanced parentheses. Index: " << result << std::endl;
        }
    }
}

int main( int argv, char *argc[] )
{
    const char *test_string_1 = "((())())()";
    const char *test_string_2 = ")()(";
    const char *test_string_3 = "())";

    test( test_string_1 );
    test( test_string_2 );
    test( test_string_3 );
}
