#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <random>
#include <iterator>

template <class T>
void print_vector( std::vector<T> *vec )
{
    std::cout << "{ ";
    for( auto it = vec->begin(); it != vec->end(); ++it )
    {
        std::cout << *it;
        if( it + 1 != vec->end() )
        {
            std::cout << ",";
        }
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

template <typename Iterator>
void print_range( Iterator begin, Iterator end )
{
    std::cout << "{ ";
    for( auto it = begin; it != end; ++it )
    {
        std::cout << *it;
        if( it + 1 != end )
        {
            std::cout << ",";
        }
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

class Structure1
{
    private:
        std::vector< std::vector<int> > min_table;
    public:
        Structure1( std::vector<int> *data )
        {
            min_table.resize( data->size() );
            int i = 0;
            int j = 1;
            for( auto i_it = data->begin(); i_it != data->end(); ++i_it )
            {
                j = 1;
                min_table[i].resize( data->size() );
                for( auto j_it = i_it; j_it != data->end(); ++j_it )
                {
                    min_table[i][i + j] = *std::min_element( i_it, j_it );
                    ++j;
                }
                ++i;
            }
        }

        int min_in_range( int i, int j )
        {
            if( i > j )
            {
                return min_table[j][i];
            }
            return min_table[i][j];
        }
};

class Structure2
{
    private:
        std::vector<int> data;
    public:
        Structure2( std::vector<int> *data )
        {
            this->data = *data;
        }

        int min_in_range( int i, int j )
        {
            return *std::min_element( data.begin() + i, data.begin() + j );
        }
};

int main( int argv, char *argc[] )
{
    std::random_device rd;
    std::mt19937 gen( rd() );

    std::vector<int> data;
    for( int i = 0; i < 40; ++i )
    {
        data.push_back( i );
    }

    std::shuffle( data.begin(), data.end(), gen );

    print_vector( &data );

    Structure1 s1( &data );

    std::cout << "Structure1:" << std::endl;
    auto it = data.begin();
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 0, 5 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 5, 10 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 10, 15 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 15, 20 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 20, 25 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 25, 30 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s1.min_in_range( 30, 35 ) << std::endl;

    Structure2 s2( &data );

    std::cout << "Structure2:" << std::endl;
    it = data.begin();
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 0, 5 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 5, 10 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 10, 15 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 15, 20 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 20, 25 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 25, 30 ) << std::endl;
    print_range( it, it + 5 );
    it += 5;
    std::cout << s2.min_in_range( 30, 35 ) << std::endl;

}
