#include <iostream>
#include <fstream>
#include <map>

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
        ciphertext += encode_char( *c, 25 - rotation );
    }

    return ciphertext;
}

int main( int argc, char *argv[] )
{
    if( argc < 2 )
    {
        std::cerr << "provide path to ciphertext" << std::endl;
        return 1;
    }

    std::ifstream ciphertext_file( argv[1] );
    if( !ciphertext_file.is_open() )
    {
        std::cerr << "couldn't open file for reading: " << argv[1] << std::endl;
    }

    std::map<char, int> char_counts;
    for( char c = 'a'; c <= 'z'; ++c )
    {
        char_counts[c] = 0;
    }

    std::string line = "";
    std::string ciphertext = "";
    while( getline( ciphertext_file, line ) )
    {
        ciphertext += line;
        for( auto it = line.begin(); it != line.end(); ++it )
        {
            if( isalpha( *it ) )
            {
                if( isupper( *it ) )
                {
                    ++char_counts[ tolower( *it ) ];
                }
                else
                {
                    ++char_counts[*it];
                }
            }
        }
    }

    char most_frequent_char;
    int most_frequent_count = 0;
    for( auto it = char_counts.begin(); it != char_counts.end(); ++it )
    {
        std::cout << it->first << ": " << it->second << std::endl;
        if( it->second > most_frequent_count )
        {
            most_frequent_char = it->first;
            most_frequent_count = it->second;
        }
    }

    std::cout << "most frequent char in ciphertext: " << most_frequent_char << std::endl;
    std::cout << "count: " << most_frequent_count << std::endl;
    std::cout << "suspected rotation: " << ( most_frequent_char - 'e' ) << std::endl;

    std::cout << encode( ciphertext, most_frequent_char - 'e' ) << std::endl;

}
