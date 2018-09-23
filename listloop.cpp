#include <iostream>

template <typename T>
class list_node
{
    public:
        list_node( T data ) : data( data ), next( NULL ) {}
        list_node( T data, list_node<T> *next ) : data( data ), next( next) {}
        T data;
        list_node<T> *next;
};

template <typename T>
class linked_list
{
    public:
        linked_list() : head( NULL ) {}
        list_node<T> *head;

        void push_front( T data );
        void push_back( T data );

        std::pair<list_node<T>*, list_node<T>*> find_loop();
    private:
        bool points_back( list_node<T> *first, list_node<T> *second );
};

template <typename T>
void linked_list<T>::push_front( T data )
{
    head = new list_node<T>( data, head );
}

template <typename T>
void linked_list<T>::push_back( T data )
{
    if( head == NULL ) return push_front( data );

    list_node<T> *new_node = new list_node<T>( data );

    list_node<T> *node = head;
    while( node->next != NULL ) node = node->next;

    node->next = new_node;
}

template <typename T>
std::pair<list_node<T>*, list_node<T>*> linked_list<T>::find_loop()
{
    std::pair<list_node<T>*, list_node<T>*> result( NULL, NULL );
    list_node<T> *first = head;
    list_node<T> *second = head->next;

    if( second == NULL ) return result;

    if( second->next == NULL ) return result;
    second = second->next;

    while( true )
    {
        if( first == NULL || second == NULL ) return result;

        if( first->next == second )
        {
            second = second->next;
            continue;
        }

        if( second->next = first )
        {
        }
    }

    return result;
}

template <typename T>
bool linked_list<T>::points_back( list_node<T> *first, list_node<T> *second )
{
    if( second == first ) return false;
    if( second->next == first ) return true;
    if( second->next == NULL ) return false;
    return points_back( first->next, second );
}

int main()
{
    linked_list<int> list;

    for( int i = 0; i < 20; ++i ) list.push_front( i );

    list_node<int> *node = list.head;

    while( node->next != NULL ) node = node->next;

    // create loop
    node->next = list.head;

    auto loop_result = list.find_loop();
    if( loop_result.first != NULL )
        std::cout << "list has loop; node with data " << loop_result.second->data << " points back to node with data " << loop_result.first->data << std::endl;
    else
        std::cout << "list has no loop" << std::endl;
}
