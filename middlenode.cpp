#include <iostream>
#include <forward_list>

template <typename T>
T middle_node( std::forward_list<T>& list )
{
    bool increment = false;
    auto middle = list.begin();
    for( auto it = list.begin(); it != list.end(); ++it )
    {
        if( increment ) ++middle;
        increment = !increment;
    }

    return *middle;
}

int main()
{
    std::forward_list<int> list;

    for( int i = 0; i < 11; ++i )
    {
        list.push_front( i );
    }

    std::cout << "{ ";
    for( auto it = list.begin(); it != list.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;

    std::cout << middle_node( list ) << std::endl;
}
