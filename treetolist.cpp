#include <iostream>
#include <set>
#include <forward_list>

int main()
{
    std::set<int> int_set;

    for( int i = 500; i < 550; ++i )
    {
        int_set.insert( i );
    }

    for( int i = 200; i < 250; ++i )
    {
        int_set.insert( i );
    }

    std::forward_list<int> int_list;

    while( !int_set.empty() )
    {
        auto it = int_set.rbegin(); // rbegin() is equivalent to max for std::set
        int_list.push_front( *it );
        int_set.erase( *it );
    }

    std::cout << "{ ";
    for( auto it = int_list.begin(); it != int_list.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;
}
