#include <iostream>

template <typename T>
class list
{
    public:
        list() : next( NULL ) {}
        T data;
        list* next;
        void push_front( T data );
        void push_back( T data );
        void reverse_recursion();
        void reverse();

    private:
        void reverse_recur( list* prev );
};

template <typename T>
void list<T>::push_front( T data )
{
    std::cout << "adding node with data " << data << " to front" << std::endl;
    list<T>* current_next = next;
    list<T>* new_next = new list<T>;
    new_next->data = this->data;
    new_next->next = current_next;
    this->data = data;
    next = new_next;
}

template <typename T>
void list<T>::push_back( T data )
{
    list<T>* new_node = new list<T>;
    new_node->data = data;
    list<T>* tail = this;
    while( tail->next != NULL )
    {
        tail = tail->next;
    }
    tail->next = new_node;
}

template <typename T>
void list<T>::reverse_recursion()
{
}

template <typename T>
T list<T>::reverse_recur( list<T>* prev )
{
}

template <typename T>
void list<T>::reverse()
{
    list<T>* node, next_node, next_next_node;
    node = this;
    next_node = next;
    if( next != null ) next_next_node = next->next;
    else next_next_node = NULL;

    while( next_next_node != NULL )
    {
        next_node->next = node;

        node = next_node;
        next_node = next_next_node;
        
        next_next_node = next_next_node->next;
    }

    if( next_node != NULL )
    {
        next_node->next = node;
    }
}

int main()
{
    list<int> int_list;
    int_list.data = 0;

    for( int i = 1; i < 24; ++i )
    {
        int_list.push_front( i );
    }

    list<int>* node = &int_list;
    std::cout << "{ ";
    while( node != NULL )
    {
        std::cout << node->data << ", ";
        node = node->next;
    }
    std::cout << "\b\b }" << std::endl;
}
