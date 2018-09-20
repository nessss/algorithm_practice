#include <iostream>

template <class T>
class DoublyLinkedListNode
{
    public:
        T data;
        DoublyLinkedListNode<T> *prev;
        DoublyLinkedListNode<T> *next;

        DoublyLinkedListNode<T>();
        DoublyLinkedListNode<T>( T data );
        DoublyLinkedListNode<T>( T data, DoublyLinkedListNode *prev, DoublyLinkedListNode *next );
};

template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode()
{
    this->prev = NULL;
    this->next = NULL;
}

template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode( T data )
{
    this->prev = NULL;
    this->next = NULL;
    this->data = data;
}

template <class T>
DoublyLinkedListNode<T>::DoublyLinkedListNode( T data, DoublyLinkedListNode *prev, DoublyLinkedListNode *next )
{
    this->prev = prev;
    this->next = next;
    this->data = data;

    if( prev != NULL ) prev->next = this;
    if( next != NULL ) next->prev = this;
}

template <class T>
class DoublyLinkedList
{
    private:
        DoublyLinkedListNode<T> *head;
        DoublyLinkedListNode<T> *tail;

    public:
        DoublyLinkedList();

        void PushBack( T data );
        void PushFront( T data );
        void PopBack();
        void PopFront();

        DoublyLinkedListNode<T> * At( int idx );

        void DeleteAt( int idx );
        void InsertAt( T data, int idx );
        void InsertSorted( T data );
        void Clear();

        bool ElementPresent( T data );
        bool InsertIfUnique( T data );
        int IndexOf( T data );

        int Size();

        void Swap( int l_idx, int r_idx );
        void Swap( DoublyLinkedListNode<T> *lhs, DoublyLinkedListNode<T> *rhs );

        void Sort();

        int Bytes();

        void PrintData();
        void PrintDataReverse();
};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    head = NULL;
    tail = NULL;
}

template <class T>
void DoublyLinkedList<T>::PushBack( T data )
{
    DoublyLinkedListNode<T> *node = new DoublyLinkedListNode<T>( data, tail, NULL );

    tail = node;

    if( head == NULL )
    {
        head = node;
    }
}

template <class T>
void DoublyLinkedList<T>::PushFront( T data )
{
    DoublyLinkedListNode<T> *node = new DoublyLinkedListNode<T>( data, NULL, head );

    head = node;

    if( tail == NULL )
    {
        tail = node;
    }
}

template <class T>
void DoublyLinkedList<T>::PopFront()
{
    if( head == NULL ) return;

    DoublyLinkedListNode<T> *to_delete = head;

    to_delete->next->prev = NULL;
    head = to_delete->next;
    delete to_delete;
}

template <class T>
void DoublyLinkedList<T>::PopBack()
{
    if( head == NULL ) return;

    DoublyLinkedListNode<T> *to_delete = tail;

    to_delete->prev->next = NULL;
    tail = to_delete->prev;
    delete to_delete;
}

template <class T>
void DoublyLinkedList<T>::DeleteAt( int idx )
{
    DoublyLinkedListNode<T> *to_delete = At( idx );
    if( to_delete == NULL ) return;

    to_delete->prev->next = to_delete->next;
    to_delete->next->prev = to_delete->prev;

    delete to_delete;
}

template <class T>
void DoublyLinkedList<T>::InsertAt( T data, int idx )
{
    DoublyLinkedListNode<T> *prev = At( idx );
    if( prev == NULL ) return;

    DoublyLinkedListNode<T> *to_insert = new DoublyLinkedListNode<T>( data, prev, prev->next );

    prev->next->prev = to_insert;
    prev->next = to_insert;
}

template <class T>
void DoublyLinkedList<T>::InsertSorted( T data )
{
    if( head == NULL || data < head->data )
    {
        PushFront( data );
    }
    else if( data > tail->data )
    {
        PushBack( data );
    }
    else
    {
        DoublyLinkedListNode<T> *insert_after = head;
        while( insert_after != NULL && data > insert_after->next->data )
        {
            insert_after = insert_after->next;
        }
        DoublyLinkedListNode<T> *node = new DoublyLinkedListNode<T>( data, insert_after, insert_after->next );
        if( insert_after == tail )
        {
            tail = node;
        }
    }
}

template <class T>
bool DoublyLinkedList<T>::ElementPresent( T data )
{
    return IndexOf( data ) > -1;
}

template <class T>
bool DoublyLinkedList<T>::InsertIfUnique( T data )
{
    DoublyLinkedListNode<T> *node = head;
    while( node != NULL )
    {
        if( node->data == data ) return false;
        node = node->next;
    }
    InsertSorted( data );
    return true;
}

template <class T>
int DoublyLinkedList<T>::IndexOf( T data )
{
    int result = 0;
    DoublyLinkedListNode<T> *node = head;

    while( node != NULL )
    {
        if( node->data == data ) return result;
        ++result;
        node = node->next;
    }

    return -1;
}

template <class T>
int DoublyLinkedList<T>::Size()
{
    int result = 0;
    DoublyLinkedListNode<T> *node = head;

    while( node != NULL )
    {
        ++result;
        node = node->next;
    }

    return result;
}

template <class T>
DoublyLinkedListNode<T> * DoublyLinkedList<T>::At( int idx )
{
    DoublyLinkedListNode<T> *node = head;
    for( int i = 0; i < idx; ++i )
    {
        node = node->next;
    }
    return node;
}

template <class T>
void DoublyLinkedList<T>::Swap( int l_idx, int r_idx )
{
    DoublyLinkedListNode<T> *l_node = At( l_idx );
    DoublyLinkedListNode<T> *r_node = At( r_idx );

    Swap( l_node, r_node );
}

template <class T>
void DoublyLinkedList<T>::Swap( DoublyLinkedListNode<T> *lhs, DoublyLinkedListNode<T> *rhs )
{
    if( lhs == NULL || rhs == NULL ) return;

    if( head == lhs ) head = rhs;
    else if( head == rhs ) head = lhs;

    if( tail == lhs ) tail = rhs;
    else if( tail == rhs ) tail = lhs;

    DoublyLinkedListNode<T> *l_prev = lhs->prev;
    DoublyLinkedListNode<T> *l_next = lhs->next;

    DoublyLinkedListNode<T> *r_prev = rhs->prev;
    DoublyLinkedListNode<T> *r_next = rhs->next;

    if( l_next == rhs ) 
    {
        lhs->prev = rhs;
        lhs->next = r_next;

        rhs->prev = l_prev;
        rhs->next = lhs;

        if( l_prev != NULL ) l_prev->next = rhs;
        if( r_next != NULL ) r_next->prev = lhs;
    }
    else if( r_next == lhs )
    {
        rhs->prev = lhs;
        rhs->next = l_next;

        lhs->prev = r_prev;
        lhs->next = rhs;

        if( r_prev != NULL ) r_prev->next = lhs;
        if( l_next != NULL ) l_next->prev = rhs;
    }
    else
    {
        lhs->prev = r_prev;
        lhs->next = r_next;

        rhs->prev = l_prev;
        rhs->next = l_next;

        if( l_prev != NULL ) l_prev->next = rhs;
        if( l_next != NULL ) l_next->prev = rhs;

        if(r_prev != NULL ) r_prev->next = lhs;
        if(r_next != NULL ) r_next->prev = lhs;
    }
}

template <class T>
void DoublyLinkedList<T>::Sort()
{
    if( head == NULL ) return;
    if( head == tail ) return;

    bool swapped = false;

    DoublyLinkedListNode<T> *node = head;
    do
    {
        swapped = false;

        while( node->next != NULL )
        {
            if( node->data > node->next->data )
            {
                Swap( node, node->next );
                swapped = true;
            }
            if( node->next == NULL ) break;
            node = node->next;
        }

        if( !swapped ) break;

        while( node->prev != NULL )
        {
            if( node->data < node->prev->data )
            {
                Swap( node, node->prev );
                swapped = true;
            }
            if( node->prev == NULL ) break;
            node = node->prev;
        }
    }
    while( swapped );
}

template <class T>
int DoublyLinkedList<T>::Bytes()
{
    int result = 0;
    result += sizeof *this;

    DoublyLinkedListNode<T> *node = head;
    while( node != NULL )
    {
        result += sizeof *node;
        node = node->next;
    }

    return result;
}

template <class T>
void DoublyLinkedList<T>::PrintData()
{
    std::cout << "{ ";
    DoublyLinkedListNode<T> *node = head;
    while( node != NULL )
    {
        std::cout << node->data;
        if( node->next != NULL )
        {
            std::cout << ",";
        }
        std::cout << " ";
        node = node->next;
    }
    std::cout << "}" << std::endl;
}

template <class T>
void DoublyLinkedList<T>::PrintDataReverse()
{
    std::cout << "{ ";
    DoublyLinkedListNode<T> *node = tail;
    while( node != NULL )
    {
        std::cout << node->data;
        if( node->prev != NULL )
        {
            std::cout << ",";
        }
        std::cout << " ";
        node = node->prev;
    }
    std::cout << "}" << std::endl;
}

template <class T>
void DoublyLinkedList<T>::Clear()
{
    DoublyLinkedListNode<T> *node = head;
    DoublyLinkedListNode<T> *next;
    while( node != NULL )
    {
        next = node->next;
        delete node;
        node = next;
    }
}
