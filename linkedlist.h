#include <iostream>

template <class T>
class LinkedListNode
{
    public:
        T data;
        LinkedListNode *next;
        LinkedListNode();
        LinkedListNode( T data );
        LinkedListNode( T data, LinkedListNode *next );
};

template <class T>
LinkedListNode<T>::LinkedListNode()
{
    this->next = NULL;
}

template <class T>
LinkedListNode<T>::LinkedListNode( T data )
{
    this->data = data;
    this->next = NULL;
}

template <class T>
LinkedListNode<T>::LinkedListNode( T data, LinkedListNode *next )
{
    this->data = data;
    this->next = next;
}

template <class T>
class LinkedList
{
    private:
        LinkedListNode<T> *head;
        LinkedListNode<T> *tail;
    public:
        LinkedList();

        void PushBack( T data );
        void PushFront( T data );
        void DeleteHead();
        void DeleteTail();

        LinkedListNode<T> * At( int idx );
        LinkedListNode<T> * Predecessor( int idx );

        void DeleteAt( int idx );
        void InsertAt( T data, int idx );
        void InsertSorted( T data );
        void InsertIfUnique( T data );

        int IndexOf( T data );
        bool ElementPresent( T data );

        void Clear();

        int Size();

        void Swap( int l_idx, int r_idx );

        void Sort();

        int Bytes();

        void PrintData();
};

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
}

template <class T>
void LinkedList<T>::PushBack( T data )
{
    LinkedListNode<T> *node = new LinkedListNode<T>( data );

    if( head == NULL )
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
}

template <class T>
void LinkedList<T>::PushFront( T data )
{
    LinkedListNode<T> *node = new LinkedListNode<T>( data );

    if( head == NULL )
    {
        head = node;
        tail = node;
    }
    else
    {
        node->next = head;
        head = node;
    }
}

template <class T>
void LinkedList<T>::DeleteHead()
{
    if( head != NULL )
    {
        LinkedListNode<T> *node = head;
        head = node->next;
        delete node;
        if( head == NULL ) tail = NULL;
    }
}

template <class T>
void LinkedList<T>::DeleteTail()
{
    if( head == tail )
    {
        DeleteHead();
        return;
    }

    if( tail != NULL )
    {
        LinkedListNode<T> *node = head;
        while( node->next != tail )
        {
            node = node->next;
        }
        node->next = NULL;
        delete tail;
        tail = node;
    }
}

template <class T>
LinkedListNode<T> * LinkedList<T>::At( int idx )
{
    if( head == NULL ) return NULL;
    LinkedListNode<T> *node = head;

    for( int i = 0; i < idx; ++i )
    {
        node = node->next;
        if( node == NULL ) return NULL;
    }

    return node;
}

template <class T>
LinkedListNode<T> * LinkedList<T>::Predecessor( int idx )
{
    if( head == NULL || idx == 0 ) return NULL;
    LinkedListNode<T> *node = head;

    for(int i = 1; i < idx; ++i )
    {
        node = node->next;
        if( node == NULL ) return NULL;
    }

    return node;
}

template <class T>
void LinkedList<T>::DeleteAt( int idx )
{
    if( head == NULL ) return;
    if( head == tail && idx == 0 ) 
    {
        delete head;
        head = NULL;
        tail = NULL;
        return;
    }

    LinkedListNode<T> *pred = Predecessor( idx );
    if( pred == NULL ) return;

    LinkedListNode<T> *node = pred->next;
    if( node == NULL ) return;

    pred->next = node->next;

    if( node == tail )
    {
        tail = pred;
    }

    if( node == head )
    {
        head = head->next;
    }

    delete node;
}

template <class T>
void LinkedList<T>::InsertAt( T data, int idx )
{
    LinkedListNode<T> *pred = Predecessor( idx );
    LinkedListNode<T> *node = new LinkedListNode<T>( data );
    LinkedListNode<T> *succ;

    if( pred != NULL )
    {
        succ = pred->next;
        pred->next = node;
    }
    else
    {
        succ = head;
        head = node;
    }

    node->next = succ;
}

template <class T>
void LinkedList<T>::InsertSorted( T data )
{
    if( head == NULL || data < head->data ) 
    {
        PushFront( data );
        return;
    }

    LinkedListNode<T> *new_node = new LinkedListNode<T>( data );
    LinkedListNode<T> *insert_after = head;
    while( insert_after != NULL )
    {
        if( data > insert_after->data )
        {
            if( insert_after->next == NULL || data < insert_after->next->data )
            {
                LinkedListNode<T> *next = insert_after->next;
                insert_after->next = new_node;
                new_node->next = next;
                return;
            }
        }
        insert_after = insert_after->next;
    }

    PushBack( data );
}

template <class T>
void LinkedList<T>::InsertIfUnique( T data )
{
    if( !ElementPresent( data ) )
    {
        InsertSorted( data );
    }
}

template <class T>
int LinkedList<T>::IndexOf( T data )
{
    int result = 0;
    LinkedListNode<T> *node = head;

    while( node != NULL )
    {
        if( node->data == data ) return result;
        ++result;
        node = node->next;
    }

    return -1;
}

template <class T>
bool LinkedList<T>::ElementPresent( T data )
{
    return IndexOf( data ) > -1;
}

template <class T>
void LinkedList<T>::Clear()
{
    LinkedListNode<T> *node = head;
    LinkedListNode<T> *tmp;
    while( node != NULL )
    {
        tmp = node->next;
        delete node;
        node = tmp;
    }

    head = NULL;
    tail = NULL;
}

template <class T>
int LinkedList<T>::Size()
{
    int result = 0;
    LinkedListNode<T> *node = head;
    while( node != NULL )
    {
        ++result;
        node = node->next;
    }

    return result;
}

template <class T>
void LinkedList<T>::Swap( int l_idx, int r_idx )
{
    LinkedListNode<T> *l = At( l_idx );
    LinkedListNode<T> *r = At( r_idx );

    LinkedListNode<T> *l_pred = Predecessor( l_idx );
    LinkedListNode<T> *r_pred = Predecessor( r_idx );

    LinkedListNode<T> *l_succ = l->next;
    LinkedListNode<T> *r_succ = r->next;

    if( l_pred != NULL )
    {
        l_pred->next = r;
    }
    if( r_pred != NULL )
    {
        r_pred->next = l;
    }

    if( l_succ != NULL )
    {
        r->next = l_succ;
    }
    if( r_succ != NULL )
    {
        l->next = r_succ;
    }

    if( l == head )
    {
        head = r;
    }
    else if( r == head )
    {
        head = l;
    }

    if( l == tail )
    {
        tail = r;
    }
    else if( r == tail )
    {
        tail = l;
    }
}

template <class T>
void LinkedList<T>::Sort()
{
    // 0 and 1 element lists are already sorted
    if( head == NULL || head == tail ) return;

    bool swap_happened = false;

    do
    {
        swap_happened = false;

        LinkedListNode<T> *pred = NULL;
        LinkedListNode<T> *node = head;
        while( node->next != NULL )
        {
            if( node->data > node->next->data )
            {
                LinkedListNode<T> *tmp = node->next;
                if( pred != NULL )
                {
                    pred->next = tmp;
                }
                else
                {
                    head = tmp;
                }
                node->next = tmp->next;
                tmp->next = node;
                if( tmp == tail )
                {
                    tail = node;
                }
                node = tmp;

                swap_happened = true;
            }
            pred = node;
            node = node->next;
        }
    }
    while( swap_happened );
}

template <class T>
int LinkedList<T>::Bytes()
{
    int result = 0;
    result += sizeof( *this );

    LinkedListNode<T> *node = head;
    while( node != NULL )
    {
        result += sizeof( node );

        node = node->next;
    }

    return result;
}

template <class T>
void LinkedList<T>::PrintData()
{
    std::cout << "{ ";
    if( head != NULL )
    {
        LinkedListNode<T> *node = head;
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
    }
    std::cout << "}" << std::endl;
}
