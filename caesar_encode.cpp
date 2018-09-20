#include <iostream>
#include <string>
#include <fstream>

const char lowerrange = 'z' - 'a';
const char upperrange = 'Z' - 'A';

char encode_char( const char & c, int rotation )
{
    char result = c;

    if( c >= 'a' && c <= 'z' )
    {
        result -= 'a';
        result += rotation;
        result %= lowerrange;
        result += 'a';
    }
    else if ( c >= 'A' && c <= 'Z' )
    {
        result -= 'A';
        result += rotation;
        result %= upperrange;
        result += 'A';
    }

    return result;
}

std::string encode( std::string cleartext, int rotation )
{
    std::string ciphertext = "";

    for( auto c = cleartext.begin(); c != cleartext.end(); ++c )
    {
        ciphertext += encode_char( *c, rotation );
    }

    return ciphertext;
}

int main( int argc, char *argv[] )
{
    if( argc < 4 )
    {
        std::cerr << "not enough arguments; usage; caeser_encode [path_to_cleartext] [rotation] [path_to_output_file]" << std::endl;
        return 1;
    }
    std::fstream cleartext_file( argv[1] );
    if( !cleartext_file.is_open() )
    {
        std::cerr << "couldn't open file for reading: " << argv[1] << std::endl;
        return 1;
    }

    std::fstream ciphertext_file;
    ciphertext_file.open( argv[3], std::fstream::out );
    if( !ciphertext_file.is_open() )
    {
        std::cerr << "couldn't open file for writing: " << argv[3] << std::endl;
        return 1;
    }

    int rotation = std::stoi( argv[2] );
    if( rotation < 1 || rotation > 25 )
    {
        std::cerr << "provide a rotation from 1 to 25" << std::endl;
        return 1;
    }

    std::string ciphertext = "";

    std::string line = "";
    while( getline( cleartext_file, line ) )
    {
        ciphertext_file << encode( line, rotation ) << std::endl;
    }

    std::cout << ciphertext << std::endl;

    return 0;
}
