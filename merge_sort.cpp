#include <queue>
#include <vector>
#include <iostream>

void merge( std::vector<int> array, int low, int middle, int high )
{
    int i;
    std::queue<int> buffer1, buffer2;

    std::cout << "buffer1: { ";
    for( i = low; i <= middle; ++i )
    {
        buffer1.push( array[i] );
        std::cout << buffer1.back() << " ";
    }
    std::cout << "}" << std::endl;

    std::cout << "buffer2: { ";
    for( i = middle + 1; i <= high; ++i )
    {
        buffer2.push( array[i] );
        std::cout << buffer2.back() << " ";
    }
    std::cout << "}" << std::endl;

    i = low;
    while( buffer1.size() > 0 || buffer2.size() > 0 )
    {
        if( buffer1.size() == 0 )
        {
            std::cout << "buffer 1 empty, adding buffer 2" << std::endl;
            while( buffer2.size() > 0 )
            {
                array[i++] = buffer2.front();
                buffer2.pop();
            }
            break;
        }
        else if( buffer2.size() == 0 )
        {
            std::cout << "buffer 2 empty, adding buffer 1" << std::endl;
            while( buffer1.size() > 0 )
            {
                array[i++] = buffer1.front();
                buffer1.pop();
            }
            break;
        }

        if( buffer1.front() < buffer2.front() )
        {
            std::cout << "buffer1.front() {" << buffer1.front() << "} < buffer2.front() {" << buffer2.front() <<"}" << std::endl;
            array[i++] = buffer1.front();
            buffer1.pop();
        }
        else
        {
            std::cout << "buffer1.front() {" << buffer1.front() << "} >= buffer2.front() {" << buffer2.front() <<"}" << std::endl;
            array[i++] = buffer2.front();
            buffer2.pop();
        }
    }
}

void merge_sort( std::vector<int> array, int low, int high )
{
    int i, middle;

    std::cout << "sorting from index " << low << " to index " << high << std::endl;

    if( low < high )
    {
        middle = ( low + high ) / 2;
        merge_sort( array, low, middle );
        merge_sort( array, middle + 1, high );
        merge( array, low, middle, high );
    }
}

void test()
{
    std::vector<int> test1 = { 5, 3, 4, 1, 8, 12 };

    std::cout << "Before sorting: ";

    for( int i = 0; i < 6; ++i )
    {
        std::cout << test1[i] << " ";
    }
    std::cout << std::endl;

    merge_sort( test1, 0, 5 );

    std::cout << "After sorting: ";

    for( int i = 0; i < 6; ++i )
    {
        std::cout << test1[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> test2 = { 23, 5, 2, 8, 6, 1 };

    std::cout << "Before sorting: ";

    for( int i = 0; i < 6; ++i )
    {
        std::cout << test2[i] << " ";
    }
    std::cout << std::endl;

    merge_sort( test2, 0, 5 );

    std::cout << "After sorting: ";

    for( int i = 0; i < 6; ++i )
    {
        std::cout << test2[i] << " ";
    }

    std::cout << std::endl;
}

void print_array( std::vector<int> array )
{
    std::cout << "{ ";
    for( int i = 0; i < array.size(); ++i )
    {
        std::cout << array[i] << " ";
    }
    std::cout << "}" << std::endl;
}

void test_merge()
{
    std::vector<int> test3 = { 5, 6, 7, 1, 2, 3 };

    print_array( test3 );

    merge( test3, 0, 2, 5 );

    print_array( test3 );
}

int main( int argc, char *argv[] )
{
    test_merge();
}
