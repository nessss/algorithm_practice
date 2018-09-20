#include <vector>
#include <iostream>

void print_vector( std::vector<int> array )
{
    std::cout << "{ ";
    for( int i = 0; i < array.size(); ++i )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "}" << std::endl;
}

void insertion_sort( std::vector<int> *items )
{
    int i, j, temp;

    for( i = 0; i < items->size(); ++i )
    {
        for( j = i + 1; j < items->size(); ++j )
        {
            std::cout << "comparing items[i] {" << (*items)[i] << "} and items[j] {" << (*items)[j] << "}" << std::endl;
            if( ( j != i ) && ( (*items)[j] < (*items)[i] ) )
            {
                std::cout << "swapping" << std::endl;
                temp = (*items)[i];
                (*items)[i] = (*items)[j];
                (*items)[j] = temp;
            }
            print_vector( *items );
        }
    }
}

void insertion_sort2( std::vector<int> *items )
{
    std::vector<int> temp;

    for( auto it = items->begin(); it != items->end(); ++it )
    {
        if( temp.empty() )
        {
            temp.push_back( *it );
            continue;
        }

        for( auto temp_it = temp.begin(); temp_it != temp.end(); ++temp_it )
        {
            if( *it < *temp_it )
            {
                temp.insert( temp_it, *it );
                break;
            }
        }
    }

    *items = temp;
}

int main( int argc, char *argv[] )
{
    std::vector<int> test_vector = { 8, 5, 4, 7, 1, 2 };
    print_vector( test_vector );

    insertion_sort2( &test_vector );
    print_vector( test_vector );
}
