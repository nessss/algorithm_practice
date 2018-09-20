#include <iostream>
#include <vector>
#include <random>

template <class T>
void print_vector( std::vector<T> *vec )
{
    std::cout << "{ ";
    for( auto it = vec->begin(); it != vec->end(); ++it )
    {
        std::cout << *it;
        if( (it + 1) != vec->end() )
        {
            std::cout << ",";
        }
        std::cout << " ";
    }
    std::cout << "}" << std::endl;
}

int best_fit( std::vector<float> *weights )
{
    std::vector<float> bins;
    bins.push_back( 0.0 );

    bool found_bin;
    auto best_bin = bins.begin();

    for( auto weight_it = weights->begin(); weight_it != weights->end(); ++weight_it )
    {
        found_bin = false;
        best_bin = bins.begin();
        int bins_checked = 0;
        for( auto bin_it = bins.begin(); bin_it != bins.end(); ++bin_it )
        {
            if( *bin_it + *weight_it <= 1.0 )
            {
                if( !found_bin || ( *bin_it + *weight_it ) >= ( *best_bin + *weight_it ) )
                {
                    // bin is more full than previous best fit
                    best_bin = bin_it;
                    found_bin = true;
                }
                else
                {
                    std::cout << "bin is not best" << std::endl;
                }
            }
            ++bins_checked;
        }
        std::cout << "checked " << bins_checked << " bins" << std::endl;
        if( found_bin )
        {
            *best_bin = *best_bin + *weight_it;
        }
        else
        {
            // didn't find a bin, create a new one
            bins.push_back( *weight_it );
        }
        print_vector( &bins );
    }

    print_vector( &bins );

    return bins.size();
}

int worst_fit( std::vector<float> *weights )
{
    std::vector<float> bins;
    bins.push_back( 0.0 );

    bool found_bin;
    auto best_bin = bins.begin();

    for( auto weight_it = weights->begin(); weight_it != weights->end(); ++weight_it )
    {
        found_bin = false;
        best_bin = bins.begin();
        for( auto bin_it = bins.begin(); bin_it != bins.end(); ++bin_it )
        {
            if( *bin_it + *weight_it <= 1.0 )
            {
                if( !found_bin || *bin_it <= *best_bin )
                {
                    // bin is less full than best bin
                    best_bin = bin_it;
                    found_bin = true;
                }
            }
        }
        if( found_bin )
        {
            *best_bin = *best_bin + *weight_it;
        }
        else
        {
            // didn't find a bin, create a new one
            bins.push_back( *weight_it );
        }
        print_vector( &bins );
    }

    print_vector( &bins );

    return bins.size();
}

int main( int argv, char *argc[] )
{
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_real_distribution<> dist( 0.0, 1.0 );

    std::vector<float> weights;

    for( int i = 0; i < 20; ++i )
    {
        weights.push_back( dist( gen ) );
    }

    print_vector( &weights );

    int n_bins = best_fit( &weights );

    std::cout << "packed into " << n_bins << " using best-fit heuristic" << std::endl;

    n_bins = worst_fit( &weights );

    std::cout << "packed into " << n_bins << " using worst-fit heuristic" << std::endl;
}
