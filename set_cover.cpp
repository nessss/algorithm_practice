#include <iostream>
#include <set>
#include <iterator>
#include <vector>

/* print the contents of a set in a nice readable format */
void print_set( std::set<int> s )
{
    std::cout << "{ ";
    for( auto it = s.begin(); it != s.end(); ++it )
    {
        std::cout << *it;
        if( std::next( it ) != s.end() ) std::cout << ",";
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

/* return the number of elements in the intersection of s and u */
int num_matching_elements( std::set<int> s, std::set<int> u )
{
    std::vector<int> intersection( u.size() );
    std::vector<int>::iterator it;

    it = std::set_intersection( s.begin(), s.end(), u.begin(), u.end(), intersection.begin() );

    intersection.resize( it - intersection.begin() );

    return intersection.size();
}

/* return true if subsets in s completely cover u */
bool covers( std::set<std::set<int>> s, std::set<int> u )
{
    std::set<int> uncovered( u.begin(), u.end() );

    for( auto s_it = s.begin(); s_it != s.end(); ++s_it )
    {
        for( auto subset_it = s_it->begin(); subset_it != s_it->end(); ++subset_it )
        {
            uncovered.erase( *subset_it );
        }
    }

    return uncovered.empty();
}

std::set<std::set<int>> greedy_set_cover( std::set<std::set<int>> s, int n )
{
    std::set<std::set<int>> result;

    std::set<int> u;
    for( int i = 1; i <= n; ++i )
    {
        u.insert( i );
    }

    print_set( u );

    std::set<int> greedy_choice;

    while( !covers( result, u ) )
    {

        for( auto it = s.begin(); it != s.end(); ++it )
        {
            if( num_matching_elements( *it, u ) > num_matching_elements( greedy_choice, u ) )
            {
                greedy_choice = *it;
            }
        }

        if( greedy_choice.empty() ) break;

        std::cout << "Greedy choice:" << std::endl;
        print_set( greedy_choice );

        result.insert( greedy_choice );
        for( auto it = greedy_choice.begin(); it != greedy_choice.end(); ++it )
        {
            u.erase( *it );
        }

        s.erase( greedy_choice );
        greedy_choice.clear();
    }

    return result;
}

void greedy_counterexample()
{
    std::cout << "Counterexample to greedy set cover algorithm:" << std::endl;
    std::set<std::set<int>> subsets;
    std::set<int> s_1 = { 1, 2, 3, 4 };
    std::set<int> s_2 = { 1, 4, 5 };
    std::set<int> s_3 = { 1, 3, 6 };
    std::set<int> s_4 = { 2, 4, 5 };

    subsets.insert( s_1 );
    subsets.insert( s_2 );
    subsets.insert( s_3 );
    subsets.insert( s_4 );

    std::set<std::set<int>> result = greedy_set_cover( subsets, 6 );

    std::cout << "Sets covering U:" << std::endl;
    for( auto it = result.begin(); it != result.end(); ++it )
    {
        print_set( *it );
    }

    std::set<std::set<int>> best_cover = { s_3, s_4 };

    std::cout << "Best solution:" << std::endl;

    for( auto it = best_cover.begin(); it != best_cover.end(); ++it )
    {
        print_set( *it );
    }
}

void test_covers()
{
    std::cout << "Testing covers" << std::endl;

    std::set<std::set<int>> covering_subsets;
    std::set<int> s_1 = { 1, 3, 5 };
    std::set<int> s_2 = { 2, 4 };
    covering_subsets.insert( s_1 );
    covering_subsets.insert( s_2 );

    std::set<int> u = { 1, 2, 3, 4, 5 };

    if( !covers( covering_subsets, u ) )
    {
        std::cout << "covers not returning true as expected" << std::endl;
    }
    else
    {
        std::cout << "covers returning true as expected" << std::endl;
    }

    std::set<std::set<int>> noncovering_subsets;

    std::set<int> s_3 = { 1, 3, 4 };
    std::set<int> s_4 = { 2, 4 };
    noncovering_subsets.insert( s_3 );
    noncovering_subsets.insert( s_4 );

    if( covers( noncovering_subsets, u ) )
    {
        std::cout << "covers not returning false as expected" << std::endl;
    }
    else
    {
        std::cout << "covers returning false as expected" << std::endl;
    }
}

int main( int argv, char *argc[] )
{
    //test_covers();
    greedy_counterexample();
}
