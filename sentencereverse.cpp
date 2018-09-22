#include <iostream>
#include <string>

int main( int argc, char *argv[] )
{
    if( argc != 2 )
    {
        std::cerr << "usage: ./sentencereverse \"sentence to reverse\"" << std::endl;
    }

    std::string input = argv[1];

    std::cout << "input:" << std::endl << input << std::endl;

    std::string output = "";

    std::string word = "";
    for( auto c = input.begin(); c != input.end(); ++c )
    {
        switch( *c )
        {
            case ' ':
            case '\t':
            case '\n':
                if( word != "" )
                {
                    output = word + " " + output;
                    word = "";
                }
                break;
            default:
                word = word + *c;
                break;
        }
    }

    if( word != "" )
    {
        output = word + " " + output;
    }

    std::cout << "output:" << std::endl << output;
    return 0;
}
