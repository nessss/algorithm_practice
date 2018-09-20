#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <ctype.h>

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
    if( argc < 2 )
    {
        std::cerr << "provide path to ciphertext" << std::endl;
        return 1;
    }

    std::fstream ciphertext_file( argv[1] );
    if( !ciphertext_file.is_open() )
    {
        std::cerr << "couldn't open file for reading: " << argv[1] << std::endl;
        return 1;
    }

    const char* dictionary_path = "/usr/share/dict/words";
    std::ifstream dictionary_file( dictionary_path );
    if( !dictionary_file.is_open() )
    {
        std::cerr << "couldn't open dictionary file for reading: " << dictionary_path << std::endl;
        return 1;
    }

    std::unordered_set<std::string> dictionary_words;

    std::string dictionary_line = "";
    while( getline( dictionary_file, dictionary_line ) )
    {
        dictionary_words.insert( dictionary_line );
    }

    std::vector<std::string> cipher_words;
    cipher_words.reserve( 4000 );
    std::string cipher_line = "";
    std::string cipher_word = "";

    while( getline( ciphertext_file, cipher_line ) )
    {
        for( auto c = cipher_line.begin(); c != cipher_line.end(); ++c )
        {
            if( isalpha( *c ) || *c == '\'' )
            {
                cipher_word += *c;
            }
            else if( cipher_word != "" )
            {
                cipher_words.push_back( cipher_word );
                cipher_word = "";
            }
        }
        if( cipher_word != "" )
        {
            cipher_words.push_back( cipher_word );
            cipher_word = "";
        }
    }

    std::cout << "number of words in ciphertext: " << cipher_words.size() << std::endl;

    std::vector<std::string> decipher_attempt;
    std::vector<std::string> best_attempt;
    int dict_matches;
    int best_matches = 0;
    int best_rotation = 0;

    for( int i = 1; i < 25; ++i )
    {
        dict_matches = 0;
        decipher_attempt.clear();
        decipher_attempt.reserve( cipher_words.size() );
        for( auto it = cipher_words.begin(); it != cipher_words.end(); ++it )
        {
            decipher_attempt.push_back( encode( *it, i ) );
        }

        for( auto it = decipher_attempt.begin(); it != decipher_attempt.end(); ++it )
        {
            if( dictionary_words.count( *it ) > 0 ) ++dict_matches;
        }

        if( dict_matches > best_matches )
        {
            best_matches = dict_matches;
            best_rotation = i;
            best_attempt = decipher_attempt;
        }
    }

    std::cout << "best rotation: " << best_rotation << std::endl;
    std::cout << "number of matches: " << best_matches << std::endl;

    std::cout << "{ ";
    for( auto it = best_attempt.begin(); it != best_attempt.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;

    return 0;
}
