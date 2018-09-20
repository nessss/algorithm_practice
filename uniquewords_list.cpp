#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <ctime>
#include <list>

int main( int argc, char *argv[] )
{
    /*
    if( argc < 2 )
    {
        std::cerr << "supply a path to a text file" << std::endl;
        return 1;
    }
    */

    int start_time = clock();

    std::list<std::string> words;
    std::string word;

    //const std::string file_path = argv[1];
    const std::string file_path = "doves.txt";
    std::ifstream text_file( file_path );

    if( text_file.is_open() )
    {
        std::string line;
        while( getline( text_file, line ) )
        {
            for( auto c = line.begin(); c != line.end(); ++c )
            {
                if( isalpha( *c ) || *c == '\'' )
                {
                    word += *c;
                }
                else
                {
                    if( word.size() > 0 )
                    {
                        bool found_word = false;
                        auto it = words.begin();
                        while( it != words.end() )
                        {
                            if( *it == word )
                            {
                                found_word = true;
                                word = "";
                                break;
                            }
                            ++it;
                        }
                        if( !found_word )
                        {
                            words.push_front( word );
                            word = "";
                        }
                    }
                }
            }
        }

        std::cout << "{ ";
        for( auto it = words.begin(); it != words.end(); ++it )
        {
            std::cout << *it << ", ";
        }
        std::cout << "\b\b }" << std::endl;

        std::cout << "unique words: " << words.size() << std::endl;
        std::cout << "set size in bytes: " << sizeof words << " bytes" << std::endl;
        text_file.close();
    }
    else
    {
        std::cerr << "couldn't open file for reading: " << argv[1] << std::endl;
        return 1;
    }

    int stop_time = clock();

    float elapsed_time = (float)(stop_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "elapsed time: " << elapsed_time << "s" << std::endl;

    return 0;
}
