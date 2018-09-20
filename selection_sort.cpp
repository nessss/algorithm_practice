#include <iostream>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>

template <class T>
void print_vector( std::vector<T> *vec )
{
    std::cout << "{ ";
    for( auto it = vec->begin(); it != vec->end(); ++it )
    {
        std::cout << *it;
        if( it + 1 != vec->end() ) std::cout << ",";
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

template <class T>
void selection_sort( std::vector<T> *vec )
{
    for( auto i_it = vec->begin(); i_it != vec->end(); ++i_it )
    {
        auto min = std::min_element( i_it, vec->end() );
        if( min != i_it ) std::swap( *min, *i_it );
    }
}

void test_selection_sort()
{
    std::cout << "Test case: selection sort" << std::endl;
    std::random_device rd;
    std::mt19937 g( rd() );

    std::vector<int> int_vector( 30 );
    int i = 0;
    for( auto it = int_vector.begin(); it != int_vector.end(); ++it )
    {
        *it = i++;
    }
    std::cout << "Constructed vector:\t";
    print_vector( &int_vector );

    std::shuffle( int_vector.begin(), int_vector.end(), g );
    std::vector<int> control( int_vector.begin(), int_vector.end() );

    std::cout << "Shuffled vector:\t";
    print_vector( &int_vector );

    std::cout << "Control vector:\t\t";
    print_vector( &control );

    selection_sort( &int_vector );
    std::sort( control.begin(), control.end() );

    std::cout << "selection_sort vector:\t";
    print_vector( &int_vector );

    std::cout << "std::sort vector:\t";
    print_vector( &control );

    if( int_vector != control )
    {
        auto mismatch = std::mismatch( int_vector.begin(), int_vector.end(), control.begin() ); 
        std::cout << "FAIL: sort did not work correctly" << std::endl;
        std::cout << "mismatch: " << *(mismatch.first) << ", " << *(mismatch.second) << std::endl;
    }
    else
    {
        std::cout << "Pass: sort worked correctly" << std::endl;
    }
}

int main( int argv, char *argc[] )
{
    test_selection_sort();
}
