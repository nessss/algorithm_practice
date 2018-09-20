#include <iostream>

class SinglyLinkedListNode
{
    public:
        int data;
        SinglyLinkedListNode *next;
};

class SinglyLinkedList
{
    private:
        SinglyLinkedListNode *head;
        SinglyLinkedListNode *tail;
    public:
        SinglyLinkedList()
        {
            head = NULL;
            tail = NULL;
        }

        void AddNode( int data )
        {
            SinglyLinkedListNode *node = new SinglyLinkedListNode;
            node->data = data;

            if( head == NULL )
            {
                node->next = NULL;
                head = node;
                tail = node;
                node = NULL;
            }
            else
            {
                tail->next = node;
                tail = node;
                tail->next = NULL;
            }
        }

        void InsertNode( int pos, int data )
        {
            SinglyLinkedListNode *node = new SinglyLinkedListNode;
            node->data = data;

            if( pos == 0 )
            {
                node->next = head;
                head = node;
                return;
            }

            SinglyLinkedListNode *pred = new SinglyLinkedListNode;
            pred = head;
            for( int i = 0; i < pos; ++i )
            {
                if( pred->next == NULL ) break;
                pred = pred->next;
            }

            SinglyLinkedListNode *succ = new SinglyLinkedListNode;
            succ = pred->next;

            pred->next = node;
            node->next = succ;
        }

        void DeleteHead()
        {
            SinglyLinkedListNode *tmp = head;
            head = head->next;
            delete tmp;
        }

        void DeleteTail()
        {
            if( head == tail )
            {
                delete tail;
                head = NULL;
                tail = NULL;
                return;
            }

            SinglyLinkedListNode *tmp = tail;
            SinglyLinkedListNode *pred = head;

            while( pred->next != tail )
            {
                pred = pred->next;
            }

            tail = pred;
            tail->next = NULL;
            delete tmp;
        }

        void DeleteNode( int pos )
        {
            if( pos == 0 )
            {
                DeleteHead();
            }

            SinglyLinkedListNode *pred = head;
            for( int i = 0; i < pos - 1; ++i )
            {
                if( pred->next == NULL ) return;
                pred = pred->next;
            }

            SinglyLinkedListNode *to_delete = pred->next;
            SinglyLinkedListNode *succ = to_delete->next;

            pred->next = succ;
            delete to_delete;
        }

        void PrintData()
        {
            std::cout << "{ ";
            SinglyLinkedListNode *node = new SinglyLinkedListNode;
            node = head;
            while( node != NULL )
            {
                std::cout << node->data;
                if( node->next != NULL )
                {
                    std::cout << ",";
                }
                std::cout << " ";

                if( node->next == NULL ) break;
                node = node->next;
            }
            std::cout << "}" << std::endl;
        }

        void Reverse()
        {
            if( head == NULL ) return;

            SinglyLinkedListNode *node = new SinglyLinkedListNode;
            SinglyLinkedListNode *succ = new SinglyLinkedListNode;
            SinglyLinkedListNode *two_ahead = new SinglyLinkedListNode;

            node = head;
            succ = node->next;
            // this will only be the case if the list has only one node
            // reversing a single element means doing nothing
            if( succ == NULL ) return;

            two_ahead = succ->next;

            // this will only be the case if the list has exactly two nodes
            // so we just swap head and tail
            if( two_ahead == NULL )
            {
                SinglyLinkedListNode *tmp = new SinglyLinkedListNode;
                tmp = head;
                head = tail;
                tail = tmp;

                head->next = tail;
                tail->next = NULL;
                return;
            }

            // the list has three or more nodes

            tail = head;

            int loops = 0;

            while( node != NULL )
            {
                ++loops;
                succ->next = node;
                node = succ;

                if( two_ahead->next != NULL )
                {
                    succ = two_ahead;
                    two_ahead = two_ahead->next;
                }
                else 
                {
                    two_ahead->next = node;
                    head = two_ahead;
                    break;
                }
            }

            std::cout << "reverse completed in " << loops << " loops" << std::endl;

            tail->next = NULL;
        }
};


int main( int argv, char *argc[] )
{
    SinglyLinkedList list;

    list.PrintData();

    for( int i = 0; i < 10; ++i )
    {
        list.AddNode( i );
    }

    list.PrintData();

    list.Reverse();
    list.PrintData();

    SinglyLinkedList list2;

    for( int i = 0; i < 1000; ++i )
    {
        list2.AddNode( i );
    }

    list2.PrintData();
    list2.Reverse();
    list2.PrintData();
}
