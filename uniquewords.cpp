#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include "linkedlist.h"
#include "doublylinkedlist.h"
#include "hashmap.h"

int main( int argc, char *argv[] )
{
    /*
    if( argc < 2 )
    {
        std::cerr << "supply a path to a text file" << std::endl;
        return 1;
    }
    */

    HashMap<std::string, std::string> words;
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
                        if( !words.present( word ) )
                        {
                            words.put( word, word );
                        }
                        word = "";
                    }
                }
            }
        }

        words.PrintData();
        std::cout << "unique words: " << words.Size() << std::endl;
        std::cout << "doubly linked list size: " << words.Bytes() << " bytes" << std::endl;
        words.Clear();
        text_file.close();
    }
    else
    {
        std::cerr << "couldn't open file for reading: " << argv[1] << std::endl;
        return 1;
    }

    return 0;
}
