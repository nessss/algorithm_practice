#include <iostream>
#include <chrono>

template <typename T>
class list_node
{
    public:
        list_node( T data ) : data( data ), next( NULL ) {}
        T data;
        list_node<T>* next;

        void push_back( T data );
};

template <typename T>
void list_node<T>::push_back( T data )
{
    if( next == NULL )
    {
        next = new list_node<T>( data );
        return;
    }

    next->push_back( data );
}

template <typename T>
class list
{
    public:
        list() : head( NULL ) {}
        list_node<T>* head;
        void push_front( T data );
        void push_back( T data );
        list_node<T>* reverse_recursion( list_node<T>* prev = NULL );
        void reverse();
};

template <typename T>
void list<T>::push_front( T data )
{

    list_node<T>* old_head = head;
    head = new list_node<T>( data );
    head->next = old_head;
}

template <typename T>
void list<T>::push_back( T data )
{
    if( head == NULL )
    {
        head = new list_node<T>( data );
        return;
    }
    head->push_back( data );
}

template <typename T>
list_node<T>* list<T>::reverse_recursion( list_node<T>* prev )
{
    if( prev == NULL )
    {
        list_node<T>* old_head = head;
        head = reverse_recursion( head );
        old_head->next = NULL;
        return head;
    }
    else
    {
        if( prev->next != NULL )
        {
            list_node<T>* return_value = reverse_recursion( prev->next );
            prev->next->next = prev;
            return return_value;
        }
        else
        {
            return prev;
        }
    }
}

template <typename T>
void list<T>::reverse()
{
    list_node<T> *node, *next_node, *nextnext_node, *old_head;
    node = head;
    next_node = node->next;
    old_head = head;

    if( next_node->next == NULL )
    {
        // list has only two elements
        head = next_node;
        next_node->next = node;
        node->next = NULL;
    }
    nextnext_node = next_node->next;

    while( nextnext_node->next != NULL )
    {
        next_node->next = node;
        node = next_node;
        next_node = nextnext_node;
        nextnext_node = nextnext_node->next;
    }

    next_node->next = node;
    nextnext_node->next = next_node;

    head = nextnext_node;
    old_head->next = NULL;
}

int main()
{
    list<int> int_list;

    auto setup_start = std::chrono::high_resolution_clock::now();

    for( int i = 0; i < 2400; ++i )
    {
        int_list.push_front( i );
    }

    auto setup_end = std::chrono::high_resolution_clock::now();

    auto setup_duration = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>( setup_end - setup_start );

    std::cout << "filling list took " << setup_duration.count() << " microseconds" << std::endl;

    /*
    list_node<int>* node = int_list.head;
    std::cout << "{ ";
    while( node != NULL )
    {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << "\b\b }" << std::endl;
    */

    auto recursion_start = std::chrono::high_resolution_clock::now();

    int_list.reverse_recursion();

    auto recursion_end = std::chrono::high_resolution_clock::now();

    auto recursion_duration = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>( recursion_end - recursion_start );

    std::cout << "reverse with recursion took " << recursion_duration.count() << " microseconds" << std::endl;

    /*
    node = int_list.head;
    std::cout << "{ ";
    while( node != NULL )
    {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << "\b\b }" << std::endl;
    */

    auto reverse_start = std::chrono::high_resolution_clock::now();

    int_list.reverse();

    auto reverse_end = std::chrono::high_resolution_clock::now();

    auto reverse_duration = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>( reverse_end - reverse_start );

    std::cout << "reverse without recursion took " << recursion_duration.count() << " microseconds" << std::endl;

    /*
    node = int_list.head;
    std::cout << "{ ";
    while( node != NULL )
    {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << "\b\b }" << std::endl;
    */
}
