#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <vector>

template <typename T>
class max_heap
{
    public:
        max_heap();
        ~max_heap();
        void reserve( const unsigned int capacity );
        const unsigned int capacity() const;
        const unsigned int size() const;
        void insert( T new_data );
        bool erase( T data_to_delete );
        T max() const;
        T at( const unsigned int idx );
    private:
        T* data;
        unsigned int current_capacity;
        unsigned int current_size;

        unsigned int parent( const unsigned int n );
        unsigned int left_child( const unsigned int n );
        unsigned int right_child( const unsigned int n );
        void bubble_up( const unsigned int n );
        void bubble_down( const unsigned int n );
        void swap( const unsigned int lhs, const unsigned int rhs );
};

template <typename T>
max_heap<T>::max_heap()
{
    current_capacity = 8;
    current_size = 0;
    data = new T[current_capacity];
}

template <typename T>
max_heap<T>::~max_heap()
{
    delete[] data;
}

template <typename T>
void max_heap<T>::reserve( const unsigned int capacity )
{
    T* tmp = new T[capacity];
    for( unsigned int i = 0; i < current_capacity; ++i )
    {
        tmp[i] = data[i];
    }
    delete[] data;
    data = tmp;
}

template <typename T>
const unsigned int max_heap<T>::capacity() const
{
    return current_capacity;
}

template <typename T>
const unsigned int max_heap<T>::size() const
{
    return current_size;
}

template <typename T>
void max_heap<T>::insert( T new_data )
{
    if( ++current_size > current_capacity )
    {
        reserve( current_capacity * 2 );
    }
    data[current_size - 1] = new_data;
    bubble_up( current_size - 1 );
}

template <typename T>
bool max_heap<T>::erase( T data_to_delete )
{
    for( unsigned int i = 0; i < current_size; ++i )
    {
        if( data[i] == data_to_delete )
        {
            data[i] = data[current_size - 1];
            bubble_down( i );
            --current_size;
            return true;
        }
    }
    return false;
}

template <typename T>
T max_heap<T>::max() const
{
    return data[0];
}

template <typename T>
T max_heap<T>::at( const unsigned int idx )
{
    return data[idx];
}

template <typename T>
unsigned int max_heap<T>::parent( const unsigned int n )
{
    if( n == 1 ) return 0;
    return n/2;
}

template <typename T>
unsigned int max_heap<T>::left_child( const unsigned int n )
{
    return n * 2;
}

template <typename T>
unsigned int max_heap<T>::right_child( const unsigned int n )
{
    return ( n * 2 ) + 1;
}

template <typename T>
void max_heap<T>::bubble_up( const unsigned int n )
{
    if( n == 0 ) return;
    if( data[n] > data[parent( n )] )
    {
        swap( n, parent( n ) );
        bubble_up( parent( n ) );
    }
}

template <typename T>
void max_heap<T>::bubble_down( const unsigned int n )
{
    if( left_child( n ) > current_size && right_child( n ) > current_size ) return;

    if( data[n] < data[right_child( n )] )
    {
        swap( n, right_child( n ) );
        bubble_down( right_child( n ) );
        return;
    }

    if( data[n] < data[left_child( n )] )
    {
        swap( n, left_child( n ) );
        bubble_down( left_child( n ) );
    }
}

template <typename T>
void max_heap<T>::swap( const unsigned int lhs, const unsigned int rhs )
{
    T tmp = data[lhs];
    data[lhs] = data[rhs];
    data[rhs] = tmp;
}

#endif // __HEAP_H
