#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>

void print_vector( std::vector<int> *vec )
{
    std::cout << "{ ";
    for( auto it = vec->begin(); it != vec->end(); ++it )
    {
        std::cout << *it;
        if( std::next( it ) != vec->end() )
        {
            std::cout << ",";
        }
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

std::vector<int> solution_1( std::vector<int> horses )
{
    std::vector<int> result( 3 );

    std::vector<int> race( 5 );
    std::copy( horses.begin(), horses.begin() + 5, race.begin() );
    horses.erase( horses.begin(), horses.begin() + 5 );

    std::sort( race.begin(), race.end() );

    int races = 1;

    while( horses.size() > 1 )
    {
        std::copy( horses.begin(), horses.begin() + 2, race.begin() + 3 );
        horses.erase( horses.begin(), horses.begin() + 2 );

        print_vector( &race );

        std::sort( race.begin(), race.end() );
        print_vector( &race );
        ++races;
    }

    std::copy( race.begin(), race.begin() + 3, result.begin() );

    std::cout << "solution found in " << races << " races" << std::endl;

    return result;
}

std::vector<int> solution_2( std::vector<int> horses )
{
    std::vector<int> race( 5 );
    std::vector<int> fast_horses;

    std::copy( horses.begin(), horses.begin() + 5, race.begin() );
    horses.erase( horses.begin(), horses.begin() + 5 );

    std::sort( race.begin(), race.end() );

    fast_horses.insert( fast_horses.end(), race.begin(), race.begin() + 3 );

    int races = 1;

    int third_fastest;
    while( horses.size() > 0 )
    {
        third_fastest = race[2];
        race.erase( race.begin(), race.begin() + 2 );
        race.erase( race.begin() + 1, race.end() );

        while( race.size() < 5 && horses.size() > 0 )
        {
            race.insert( race.end(), horses.back() );
            horses.pop_back();
        }

        std::sort( race.begin(), race.end() );
        ++races;

        for( auto it = race.begin(); it != race.end(); ++it )
        {
            if( *it == third_fastest )
            {
                fast_horses.insert( fast_horses.begin(), race.begin(), it );
                std::unique( fast_horses.begin(), fast_horses.end() );
            }
        }
    }

    race.clear();

    while( fast_horses.size() > 0 )
    {
        while( race.size() < 5 && fast_horses.size() > 0 )
        {
            race.insert( race.end(), fast_horses.back() );
            fast_horses.pop_back();
        }

        std::sort( race.begin(), race.end() );
        race.erase( race.begin() + 3, race.end() );
        ++races;
    }

    std::cout << "solution found in " << races << " races" << std::endl;

    return race;
}

std::vector<int> solution_3( std::vector<int> horses )
{
    int races = 0;
    while( horses.size() > 5 )
    {
        std::sort( horses.begin(), horses.begin() + 5 );
        horses.erase( horses.begin() + 3, horses.begin() + 5 );

        std::random_shuffle( horses.begin(), horses.end() );
        ++races;
    }

    std::sort( horses.begin(), horses.end() );
    ++races;

    std::cout << "solution found in " << races << " races" << std::endl;

    return std::vector<int> ( horses.begin(), horses.begin() + 3 );
}

int main( int argv, char *argc[] )
{
    std::random_device rd;
    std::mt19937 g( rd() );

    std::vector<int> horses( 25 );

    int speed = 1;

    for( auto it = horses.begin(); it != horses.end(); ++it )
    {
        *it = speed++;
    }

    std::shuffle( horses.begin(), horses.end(), g );

    print_vector( &horses );

    std::vector<int> result = solution_1( horses );

    std::cout << "solution 1 result: ";
    print_vector( &result );

    result = solution_2( horses );

    std::cout << "solution 2 result: ";
    print_vector( &result );

    std::sort( horses.begin(), horses.end() );

    result = solution_2( horses );

    std::cout << "solution 2 on sorted horses result: ";
    print_vector( &result );

    std::sort( horses.rbegin(), horses.rend() );

    result = solution_2( horses );

    std::cout << "solution 2 on reverse sorted horses result: ";
    print_vector( &result );

    std::shuffle( horses.begin(), horses.end(), g );

    result = solution_3( horses );

    std::cout << "solution 3 result: ";
    print_vector( &result );
}
