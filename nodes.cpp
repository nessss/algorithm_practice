#include <iostream>
#include <vector>
#include <random>

class Node
{
    public:
        int data[3];
};

bool element_present( int element, std::vector<Node> *nodes )
{
    for( auto it = nodes->begin(); it != nodes->end(); ++it )
    {
        for( int i = 0; i < 3; ++i )
        {
            if( it->data[i] == element ) return true;
        }
    }

    return false;
}

int main( int argv, char *argc[] )
{
    std::random_device rd;
    std::mt19937 g( rd() );

    std::vector<int> data( 1000 );
    int i = 0;
    for( auto it = data.begin(); it != data.end(); ++it )
    {
        *it = i++;
    }

    for( int j = 0; j < 200; ++j )
    {
        std::vector<Node> nodes( 1000 );

        i = 0;
        for( auto it = nodes.begin(); it != nodes.end(); ++it )
        {
            it->data[0] = data[i];
            it->data[1] = data[(i + 1) % data.size()];
            it->data[2] = data[(i + 2) % data.size()];
            ++i;
        }

        for( i = 0; i < 3; ++i )
        {
            std::uniform_int_distribution<int> distribution( 0, nodes.size() - 1 );
            int erased_idx = distribution( g );
            nodes.erase( nodes.begin() + erased_idx );
        }

        std::vector<int> missing_elements;

        for( i = 0; i < 1000; ++i )
        {
            if( !element_present( i, &nodes ) )
            {
                missing_elements.push_back( i );
            }
        }

        if( missing_elements.empty() )
        {
            std::cout << "no missing elements" << std::endl;
        }
        else
        {
            std::cout << "missing elements:" << std::endl << "{ ";
            for( auto it = missing_elements.begin(); it != missing_elements.end(); ++it )
            {
                std::cout << *it;
                if( it + 1 != missing_elements.end() )
                {
                    std::cout << ",";
                }
                std::cout << " ";
            }
            std::cout << "}" << std::endl;
        }
    }
}
