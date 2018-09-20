#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

/* print the contents of a vector in a nice readable format */
void print_vector( std::vector<int> s )
{
    std::cout << "{ ";
    for( auto it = s.begin(); it != s.end(); ++it )
    {
        std::cout << *it;
        if( std::next(it) != s.end() ) std::cout << ",";
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

/* return the sum of all elements of a vector<int> */
int vector_sum( std::vector<int> s )
{
    int result = 0;
    for( auto it = s.begin(); it != s.end(); ++it )
    {
        result += *it;
    }

    return result;
}

/* return a vector filled with the closest solution to the knapsack
 * problem using a best-fit strategy, i.e. if the smallest unused
 * value in s won't bring the total above t, add it. */
std::vector<int> best_fit_knapsack( std::vector<int> s, int t )
{
    std::vector<int> result;

    /* we could use std::min from <algorithm> each pass to find the
     * smallest element, but intuitively it would seem sorting it first
     * would be more efficient, and since we're not working with pointers
     * the original vector should be untouched. */
    std::sort( s.begin(), s.end() );

    for( auto it = s.begin(); it != s.end(); ++it )
    {
        if( vector_sum( result ) + *it <= t )
        {
            result.push_back( *it );
        }
    }
    return result;
}

/* return a vector filled with the closest solution to the knapsack
 * problem using a first-fit strategy, i.e. iterate through S in order,
 * and add each element if it fits. */
std::vector<int> first_fit_knapsack( std::vector<int> s, int t )
{
    std::vector<int> result;

    for( auto it = s.begin(); it != s.end(); ++it )
    {
        if( vector_sum( result ) + *it <= t )
        {
            result.push_back( *it );
        }
    }
    return result;
}

/* return a vector filled with the closest solution to the knapsack
 * problem using a greedy strategy, i.e. find the largest value in S
 * that hasn't already been added and that won't bring the total over T
 * and add it until there are no elements left that won't bring the total
 * over T. */
std::vector<int> greedy_knapsack( std::vector<int> s, int t )
{
    std::vector<int> result;

    /* sort in reverse order to get largest-to-smallest order */
    std::sort( s.rbegin(), s.rend() );

    for( auto it = s.begin(); it != s.end(); ++it )
    {
        if( vector_sum( result ) + *it <= t )
        {
            result.push_back( *it );
        }
    }
    return result;
}

void first_fit_counterexample()
{
    std::cout << "Counterexample to the first-fit strategy of solving the knapsack problem:" << std::endl;
    std::vector<int> s = { 8, 3, 5, 1 };
    int t = 6;

    std::cout << "S = ";
    print_vector( s );

    std::cout << "T = " << t << std::endl;

    std::vector<int> first_fit_result = first_fit_knapsack( s, t );

    std::cout << "First-fit best solution: ";
    print_vector( first_fit_result );
    std::cout << "Total: " << vector_sum( first_fit_result ) << std::endl;

    std::vector<int> solution = { 1, 5 };
    std::cout << "Actual best solution: ";
    print_vector( solution );
    std::cout << "Total: " << vector_sum( solution ) << std::endl;
    std::cout << "----------------------" << std::endl;
}

void best_fit_counterexample()
{
    std::cout << "Counterexample to the best-fit strategy of solving the knapsack problem:" << std::endl;
    std::vector<int> s = { 1, 3, 5, 8 };
    int t = 6;

    std::cout << "S = ";
    print_vector( s );

    std::cout << "T = " << t << std::endl;

    std::vector<int> best_fit_result = best_fit_knapsack( s, t );

    std::cout << "Best-fit best solution: ";
    print_vector( best_fit_result );
    std::cout << "Total: " << vector_sum( best_fit_result ) << std::endl;

    std::vector<int> solution = { 1, 5 };
    std::cout << "Actual best solution: ";
    print_vector( solution );
    std::cout << "Total: " << vector_sum( solution ) << std::endl;
    std::cout << "----------------------" << std::endl;
}

void greedy_counterexample()
{
    std::cout << "Counterexample to the greedy strategy of solving the knapsack problem:" << std::endl;
    std::vector<int> s = { 4, 8, 7, 2 };
    int t = 9;

    std::cout << "S = ";
    print_vector( s );

    std::cout << "T = " << t << std::endl;

    std::vector<int> greedy_result = greedy_knapsack( s, t );

    std::cout << "Greedy best solution: ";
    print_vector( greedy_result );
    std::cout << "Total: " << vector_sum( greedy_result ) << std::endl;

    std::vector<int> solution = { 7, 2 };
    std::cout << "Actual best solution: ";
    print_vector( solution );
    std::cout << "Total: " << vector_sum( solution ) << std::endl;
    std::cout << "----------------------" << std::endl;
}


int main( int argv, char *argc[] )
{
    first_fit_counterexample();
    best_fit_counterexample();
    greedy_counterexample();
}
