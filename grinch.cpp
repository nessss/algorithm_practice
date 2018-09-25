#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <chrono>

template <typename T>
void print_vector( std::vector<T> &vec )
{
    std::cout << "{ ";
    for( auto it = vec.begin(); it != vec.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;
}

template <typename T>
void print_set( std::multiset<T> &set )
{
    std::cout << "{ ";
    for( auto it = set.begin(); it != set.end(); ++it )
    {
        std::cout << *it << ", ";
    }
    std::cout << "\b\b }" << std::endl;
}

int main()
{
    typedef std::chrono::high_resolution_clock myclock;
    std::mt19937 generator;
    generator.seed( myclock::now().time_since_epoch().count() );
    const int max_score = 100;
    std::uniform_int_distribution<int> distribution( 1, max_score );

    std::vector<int> players;

    for( int i = 0; i < 50; ++i )
    {
        players.push_back( distribution( generator ) );
    }

    std::cout << "unsorted players:" << std::endl;
    print_vector( players );

    std::multiset<int> good_team, bad_team;
    int operations = 0;
    int initial_sort_operations = 0;

    for( auto it = players.begin(); it != players.end(); ++it )
    {
        if( *it > max_score / 2 )
        {
            good_team.insert( *it );
        }
        else
        {
            bad_team.insert( *it );
        }
        ++operations;
        ++initial_sort_operations;
    }

    std::cout << "good team before balancing:" << std::endl;
    print_set( good_team );

    std::cout << "bad team before balancing:" << std::endl;
    print_set( bad_team );

    int balance_operations = 0;
    auto bad_it = bad_team.rbegin();
    while( bad_team.size() > good_team.size() )
    {
        bad_it = bad_team.rbegin();
        good_team.insert( *bad_it );
        bad_team.erase( *bad_it );
        ++operations;
        ++balance_operations;
    }

    auto good_it = good_team.begin();
    while( good_team.size() > bad_team.size() )
    {
        good_it = good_team.begin();
        bad_team.insert( *good_it );
        good_team.erase( *good_it );
        ++operations;
        ++balance_operations;
    }

    int swap_operations = 0;
    while( *( good_team.begin() ) < *( bad_team.rbegin() ) )
    {
        int good_player = *( bad_team.rbegin() );
        int bad_player = *( good_team.begin() );

        good_team.insert( good_player );
        bad_team.insert( bad_player );

        good_team.erase( bad_player );
        bad_team.erase( good_player );
        ++operations;
        ++swap_operations;
    }

    std::cout << "good team:" << std::endl;
    print_set( good_team );

    std::cout << std::endl;

    std::cout << "bad team:" << std::endl;
    print_set( bad_team );

    std::cout << std::endl;

    std::cout << "completed in " << operations << " operations" << std::endl;
    std::cout << "inital sort took " << initial_sort_operations << " operations" << std::endl;
    std::cout << "balancing took " << balance_operations << " operations" << std::endl;
    std::cout << "swapping took " << swap_operations << " operations" << std::endl;
}
