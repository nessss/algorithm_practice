#include <iostream>

class binary_tree
{
    public:
        binary_tree() :
            key( 0 ),
            parent( NULL ),
            left( NULL ),
            right( NULL ) {}

        binary_tree( const int& data ) :
            key( data ),
            parent( NULL ),
            left( NULL ),
            right( NULL ) {}

        int key;
        binary_tree* parent;
        binary_tree* left;
        binary_tree* right;

        bool insert( int key )
        {
            if( key == this->key ) return false;
            else if( key > this->key )
            {
                if( right == NULL )
                {
                    right = new binary_tree( key );
                    right->parent = this;
                    return true;
                }
                else
                {
                    return right->insert( key );
                }
            }
            else // key < this->key
            {
                if( left == NULL )
                {
                    left = new binary_tree( key );
                    left->parent = this;
                    return true;
                }
                else
                {
                    return left->insert( key );
                }
            }
        }

        bool operator==( const binary_tree& other ) const
        {
            if( this->key != other.key ) return false;
            if( (this->left == NULL) != (other.left == NULL) ) return false;
            if( (this->right == NULL) != (other.right == NULL) ) return false;
            if( this->left != NULL )
                if( *(this->left) != *(other.left) ) return false;
            if( this->right != NULL )
                if( *(this->right) != *(other.right) ) return false;

            return true;
        }

        bool operator!=( const binary_tree& other ) const
        {
            return !( *(this) == other );
        }
};

int main()
{
    binary_tree tree1;
    tree1.key = 5;

    tree1.insert( 8 );
    tree1.insert( 12 );
    tree1.insert( 4 );
    tree1.insert( 6 );
    tree1.insert( 7 );

    binary_tree tree2;
    tree2.key = 5;

    tree2.insert( 8 );
    tree2.insert( 12 );
    tree2.insert( 4 );
    tree2.insert( 6 );
    tree2.insert( 7 );

    binary_tree tree3;
    tree3.key = 5;

    tree3.insert( 12 );
    tree3.insert( 8 );
    tree3.insert( 6 );
    tree3.insert( 4 );
    tree3.insert( 7 );

    binary_tree tree4;
    tree4.key = 5;

    tree4.insert( 8 );
    tree4.insert( 12 );
    tree4.insert( 4 );
    tree4.insert( 6 );
    tree4.insert( 9 );

    std::cout << ( tree1 == tree2 ) << std::endl;
    std::cout << ( tree1 == tree3 ) << std::endl;
    std::cout << ( tree1 == tree4 ) << std::endl;
}
