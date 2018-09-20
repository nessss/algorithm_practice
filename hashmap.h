#include <iostream>

#define TABLE_SIZE 2047

template <typename K, typename V>
class HashNode
{
    public:
        HashNode( K &key, V &value ) : key( key ), value( value ), next( NULL ) {}
        K get_key() const { return key; }
        V get_value() const { return value; }
        void set_value( V value ) { this->value = value; }
        HashNode* get_next() const { return next; }
        void set_next( HashNode* next ) { this->next = next; }

    private:
        K key;
        V value;
        HashNode<K, V>* next;
};

template <typename K>
struct KeyHash
{
    unsigned long operator()( const K &key ) const
    {
        return reinterpret_cast<unsigned long>(key) % TABLE_SIZE;
    }
};


template <typename K, typename V, typename F = KeyHash<K>>
class HashMap
{
    public:
        HashMap()
        {
            table = new HashNode<K, V> *[TABLE_SIZE]();
        }
        ~HashMap()
        {
            Clear();
            delete[] table;
        }

        void Clear()
        {
            for( int i = 0; i < TABLE_SIZE; ++i )
            {
                HashNode<K, V> *node = table[i];
                while( node != NULL )
                {
                    HashNode<K, V> *prev = node;
                    node = node->get_next();
                    delete prev;
                }
                table[i] = NULL;
            }
        }

        bool get( const K &key, V &value )
        {
            unsigned long hash_value = hash_function( key );
            HashNode<K, V> *node = table[hash_value];

            while( node != NULL )
            {
                if( node->get_key() == key )
                {
                    value = node->get_value();
                    return true;
                }
                node = node->get_next();
            }

            return false;
        }

        bool present( const K &key )
        {
            unsigned long hash_value = hash_function( key );
            HashNode<K, V> *node = table[hash_value];
            while( node != NULL )
            {
                if( node->get_key() == key )
                {
                    return true;
                }
                node = node->get_next();
            }
        }

        void put( const K &key, const V &value )
        {
            unsigned long hash_value = hash_function( key );
            HashNode<K, V> *prev = NULL;
            HashNode<K, V> *node = table[hash_value];
            while( node != NULL && node->get_key() != key )
            {
                prev = node;
                node = node->get_next();
            }

            if( node == NULL )
            {
                node = new HashNode<K, V>( key, value );
                if( prev == NULL )
                {
                    table[hash_value] = node;
                }
                else
                {
                    prev->set_next( node );
                }
            }
            else
            {
                node->set_value( value );
            }
        }

        void remove( const K &key )
        {
            unsigned long hash_value = hash_function( key );
            HashNode<K, V> *prev = NULL;
            HashNode<K, V> *node = table[hash_value];

            while( node != NULL && node->get_key() != key )
            {
                prev = node;
                node = node->get_next();
            }
            if( node == NULL ) return;

            if( node->get_key() == key() )
            {
                if( prev == NULL )
                {
                    table[hash_value] = node->get_next();
                }
                else
                {
                    prev->set_next( node->get_next() );
                }
                delete node;
            }
        }

        void PrintData()
        {
            std::cout << "{ ";
            for( int i = 0; i < TABLE_SIZE; ++i )
            {
                HashNode<K, V> *node = table[i];
                while( node != NULL )
                {
                    std::cout << node->get_value() << ", ";
                    node = node->get_next();
                }
            }
            std::cout << "\b\b }" << std::endl;
        }

        int Size()
        {
            int result = 0;
            for( int i = 0; i < TABLE_SIZE; ++i )
            {
                HashNode<K, V> *node = table[i];
                while( node != NULL )
                {
                    ++result;
                    node = node->get_next();
                }
            }
            return result;
        }

        int Bytes()
        {
            int result = sizeof *this;
            for( int i = 0; i < TABLE_SIZE; ++i )
            {
                HashNode<K, V> *node = table[i];
                while( node != NULL )
                {
                    result += sizeof *node;
                }
            }

            return result;
        }

    private:
        HashNode<K, V> **table;
        F hash_function;
};
