#ifndef __PP_H
#define __PP_H
#include <iostream>
#include <string>

template <class ForwardIterator>
void pprint( ForwardIterator begin, ForwardIterator end, std::string label = ""  )
{
    if( label != "" ) std::cout << label << ": ";
    std::cout << "{ ";
    if( begin == end )
    {
        std::cout << "}" << std::endl;
        return;
    }
    for( auto it = begin; it != end; ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;
}

#endif // __PP_H
