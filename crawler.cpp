#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>

std::string strip_hostname( std::string url )
{
    auto dot_pos = url.find( '.' );
    if( dot_pos == std::string::npos ) return url;
    auto second_dot_pos = url.find( '.', dot_pos + 1 );
    if( second_dot_pos == std::string::npos ) return url;

    return std::string ( url.begin() + dot_pos + 1, url.end() );
}

std::pair<std::string, std::string> split_url( std::string url )
{
    std::string domain, file;

    bool in_domain = true;
    for( auto it = url.begin(); it != url.end(); ++it )
    {
        if( in_domain )
        {
            if( *it != '/' )
            {
                domain += *it;
            }
            else
            {
                if( domain == "https:/" )
                {
                    continue;
                }
                else if( domain == "https://" )
                {
                    domain = "";
                    continue;
                }
                in_domain = false;
            }
        }
        else
        {
            file += *it;
        }
    }

    return std::pair<std::string, std::string>( strip_hostname( domain ), file );
}

// return true if the site has not been visited, false otherwise
bool visit( std::map<std::string, std::unordered_set<std::string>> &urls, std::string url )
{
    auto components = split_url( url );
    std::string domain = components.first;
    std::string file = components.second;

    if( urls.count( domain ) == 0 )
    {
        std::unordered_set<std::string> new_domain;
        new_domain.insert( file );
        urls[ domain ] = new_domain;
        return true;
    }
    else
    {
        auto result = urls[ domain ].insert( file );
        return result.second;
    }
}

int main()
{
    std::map<std::string, std::unordered_set<std::string>> urls;

    std::vector<std::string> input = {
        "www.pubup.com/a",
        "www.pubup.com/b",
        "www.pubup.com/c",
        "www.pubup.com/d",
        "www.pubup.com/e",
        "www.pubup.com/f",
        "www.pubup.com/g",
        "www.mugum.com/a",
        "www.mugum.com/b",
        "www.mugum.com/c",
        "www.mugum.com/d",
        "www.mugum.com/e",
        "www.mugum.com/f",
        "www.mugum.com/g",
        "www.foobar.com/a",
        "www.foobar.com/b",
        "www.foobar.com/c",
        "www.foobar.com/d",
        "www.foobar.com/e",
        "www.foobar.com/f",
        "www.foobar.com/g",
        "www.pubup.com/b",
        "www.mugum.com/a",
        "www.foobar.com/c",
        "pubup.com/f",
        "pubup.com/g"
    };

    for( auto it = input.begin(); it != input.end(); ++it )
    {
        if( visit( urls, *it ) )
        {
            std::cout << *it << " has not been visited; visiting now" << std::endl;
        }
        else
        {
            std::cout << *it << " has been visited; not visiting" << std::endl;
        }
    }
}
