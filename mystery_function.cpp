#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

int mystery( int n )
{
    int result = 0;
    for( int i = 1; i < ( n - 1 ); ++i )
    {
        for( int j = i + 1; j < n; ++j )
        {
            for( int k = 1; k < j; ++k )
            {
                ++result;
            }
        }
    }

    return result;
}

int pesky( int n )
{
    int result = 0;
    for( int i = 1; i < n; ++i )
    {
        for( int j = 1; j < i; ++j )
        {
            for( int k = j; k < i + j; ++k )
            {
                ++result;
            }
        }
    }
    return result;
}

int prestiferous( int n )
{
    int result = 0;
    for( int i = 1; i < n; ++i )
    {
        for( int j = 1; j < i; ++j )
        {
            for( int k = j; k < i + j; ++k )
            {
                for( int l = 1; l < i + j - k; ++l )
                {
                    ++result;
                }
            }
        }
    }
    return result;
}

int conundrum( int n )
{
    int result = 0;
    for( int i = 1; i < n; ++i )
    {
        for( int j = i + 1; j < n; ++j )
        {
            for( int k = i + 1; k < n; ++k )
            {
                ++result;
            }
        }
    }
    return result;
}

float polynomial( float x, std::vector<float> coefficients )
{
    float result = 0.0;
    float power = 0;
    for( auto it = coefficients.begin(); it != coefficients.end(); ++it )
    {
        float term = pow( x , power ) * (*it);
        result += term;
        std::cout << "pow( ( x, "<< power << " ) * " << *it << ": " << term << std::endl;
        power += 1.0;
    }
    return result;
}

float eval_poly( float x, std::vector<float> coefficients )
{
    float p = coefficients[0];
    float xpower = 1.0;
    int mults = 0;
    int adds = 0;
    for( int i = 1; i < coefficients.size(); ++i )
    {
        xpower = x * xpower;
        p = p + coefficients[i] * xpower;
        mults += 2;
        adds += 1;
    }

    std::cout << "multiplications\t" << mults << std::endl;
    std::cout << "additions:\t" << adds << std::endl;

    return p;
}

float horner( float x, std::vector<float> coefficients )
{
    float result = 0;
    for( int i = coefficients.size() - 1; i >= 0; --i )
    {
        result = ( result * x ) + coefficients[i];
    }
    return result;
}

int main( int argv, char *argc[] )
{
    int result;

    std::vector<float> coefficients = {
        -0.5046,
        2.0092,
        -1.4866,
        0.3333
    };

    /*
    std::ofstream point_set_file;
    point_set_file.open( "point_set.txt" );

    for( int i = 0; i < 24; ++i )
    {
        result = conundrum( i );
        std::cout << "conundrum( " << i << " ) -> " << result << std::endl;

        point_set_file << i << "\t" << result << "\t" << i << std::endl;

        std::cout << polynomial( i, coefficients ) << std::endl;
    }

    point_set_file.close();
    */

    for( int i = 0; i < 24; ++i )
    {
        float my_result = polynomial( float( i ), coefficients );
        float book_result = eval_poly( float( i ), coefficients );
        float horner_result = horner( float( i ), coefficients );

        std::cout << "my result:\t" << my_result << std::endl;
        std::cout << "book result:\t" << book_result << std::endl;
        std::cout << "horner result:\t" << horner_result << std::endl;
    }
}
