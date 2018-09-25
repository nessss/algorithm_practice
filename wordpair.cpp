#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>

void process_file( std::unordered_multiset<std::string> &set, std::fstream &file )
{
    std::vector<std::string> words;
    std::string word = "";

    char c;
    while( file.get( c ) )
    {
        switch( c )
        {
            case ' ':
            case '\t':
            case '\n':
                if( word != "" )
                {
                    words.push_back( word );
                    word = "";
                }
                break;
            default:
                if( c >= 'A' && c <= 'z' )
                {
                    word = word + c;
                }
        }
    }

    for( auto it = words.begin(); it != words.end(); ++it )
    {
        if( it + 1 != words.end() )
        {
            set.insert( *it + " " + *(it + 1) );
        }
    }
}

std::pair<std::string, std::string> find_most_frequent_pair(
        std::unordered_multiset<std::string> &set )
{
    std::string frequent_pair = "";
    std::string last_pair = "";
    int max_count = 0;
    int count = 0;

    for( auto it = set.begin(); it != set.end(); ++it )
    {
        if( *it == last_pair ) continue;

        count = set.count( *it );
        if( count > max_count )
        {
            max_count = count;
            frequent_pair = *it;
        }

        last_pair = *it;
    }

    if( frequent_pair != "" )
    {
        std::string first = "", second = "";
        bool second_word = false;
        for( auto c = frequent_pair.begin(); c != frequent_pair.end(); ++c )
        {
            switch( *c )
            {
                case ' ':
                    second_word = true;
                    break;
                default:
                    if( second_word )
                    {
                        second += *c;
                    }
                    else first += *c;
            }
        }
        return std::make_pair( first, second );
        
    }
    else return std::make_pair( "", "" );
}

int main()
{
    std::fstream text_file( "./doves.txt" );
    if( !text_file.is_open() )
    {
        std::cerr << "couldn't open doves.txt for reading" << std::endl;
    }

    std::unordered_multiset<std::string> pairs;

    std::string line = "";

    process_file( pairs, text_file );

    auto pair = find_most_frequent_pair( pairs );
    std::cout << "most frequent pair is " << pair.first << ", " << pair.second << std::endl;
    std::cout << "occurances: " << pairs.count( pair.first + " " + pair.second ) << std::endl;
}
