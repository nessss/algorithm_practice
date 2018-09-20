#include <vector>
#include <iostream>

template <class T>
void print_vector( std::vector<T> array )
{
    std::cout << "{ ";
    for( int i = 0; i < array.size(); ++i )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "}" << std::endl;
}

int main( int argc, char *argv[] )
{
    std::vector<int> vector1 = { 0, 1, 2, 3, 4, 5 };

    std::vector<int> duplicate_vector( vector1.begin(), vector1.end() );

    print_vector( vector1 );
    print_vector( duplicate_vector );

    auto slice_begin = vector1.begin();
    std::advance( slice_begin, 2 );

    auto slice_end = vector1.end();
    std::advance( slice_end, -2 );

    std::vector<int> slice( slice_begin, slice_end );
    print_vector( slice );
}
