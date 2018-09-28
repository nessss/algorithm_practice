#include <iostream>
#include <random>
#include <vector>

enum Color
{
    infrared,
    red,
    orange,
    yellow,
    green,
    blue,
    indigo,
    violet,
    ultraviolet
};

std::string color_names[] =
{
    "infrared",
    "red",
    "orange",
    "yellow",
    "green",
    "blue",
    "indigo",
    "violet",
    "ultraviolet"
};

std::ostream& operator<<( std::ostream& out, Color color )
{
    if( color >= infrared && color <= ultraviolet )
    {
        return out << color_names[(int)color];
    }

    return out << "[out of range]";
}

//template <enum Color>
using color_pair = std::pair<int, Color>;

#define MAX_COLOR ultraviolet

std::vector<color_pair> color_sort( std::vector<color_pair> &vec )
{
    std::vector<std::vector<color_pair>> colors( 9 ); 
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        switch( (*it).second )
        {
            case infrared:
                colors[0].push_back( *it );
                break;
            case red:
                colors[1].push_back( *it );
                break;
            case orange:
                colors[2].push_back( *it );
                break;
            case yellow:
                colors[3].push_back( *it );
                break;
            case green:
                colors[4].push_back( *it );
                break;
            case blue:
                colors[5].push_back( *it );
                break;
            case indigo:
                colors[6].push_back( *it );
                break;
            case violet:
                colors[7].push_back( *it );
                break;
            case ultraviolet:
                colors[8].push_back( *it );
                break;
        }
    }

    std::vector<color_pair> result;
    for( auto color_it = colors.begin(); color_it != colors.end(); ++color_it )
    {
        for( auto pair_it = (*color_it).begin(); pair_it != (*color_it).end(); ++pair_it )
        {
            result.push_back( *pair_it);
        }
    }

    return result;
}

int main()
{
    int n = 15;

    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<int> dist( (int)infrared, (int)ultraviolet );

    std::vector<color_pair> input_pairs;

    for( int i = 1; i < n + 1; ++i )
    {
        input_pairs.push_back( std::make_pair( i, (Color) dist( gen ) ) );
    }

    std::cout << "input pairs:" << std::endl << "{" << std::endl;
    for( auto it = input_pairs.begin(); it != input_pairs.end(); ++it )
    {
        std::cout << "\t(" << (*it).first << ", " << (*it).second << ")," << std::endl;
    }
    std::cout << "\b\b" << std::endl << "}" << std::endl;

    std::vector<color_pair> result = color_sort( input_pairs );

    std::cout << "sorted pairs:" << std::endl << "{" << std::endl;
    for( auto it = result.begin(); it != result.end(); ++it )
    {
        std::cout << "\t(" << (*it).first << ", " << (*it).second << ")," << std::endl;
    }
    std::cout << "\b\b" << std::endl << "}" << std::endl;
}
