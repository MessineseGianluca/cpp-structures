/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "../dictionary.h"
#include <stdexcept>

// Exception
struct HashTableFull : public std::out_of_range {
    HashTableFull() : out_of_range("Can't add object. The hash table is full. ") {};
};

struct InexistentPair : public std::invalid_argument {
    InexistentPair() : invalid_argument("This pair doesn't exist.") {};
};



/* A possibility for the representation of a dictionary is to use hashing.
 *
 * This method use a hash function to map dictionary pairs into positions in a table
 * called the hash table.
 *
 * In the ideal situation, if pair p has the key k and f is the hash function, the pair p
 * is stored in position f(k) of the table.
 *
 * Assume for now that each position of the table can store at most one pair. To search for
 * a pair with key k, we compute f(k) and see whether a pair exists at position f(k) of the table.
 * If so, we have found the desired pair. If not, the dictionary contains no pair with the
 * specified key k. In the former case the pair may be deleted (if desired) by making position
 * f(k) of the table empty. In the latter case the pair may be ed by placing it in position
 * f(k).
 *
 * In the ideal situation just described, it takes O(b) time to initialize an empty dictionary
 * (b is the number of positions in the hash table) and O(1) time to perform a find, insert or
 * erase operation.
 *
 * When the key range is too large, we use a hash table that has a number of positions that is
 * smaller than the key range and a hash function f(k) that maps several different keys into the
 * same position of the hash table. Each position of the table is a _bucket_; f(k) is the
 * _home bucket_ for the pair whose key is k; and the number of buckets in a table equals the
 * table length.
 *
 * Since a hash function may map several keys into the same bucket, we may consider designing
 * buckets that can hold more than one pair.
 *
 * Of the many hash functions that have been proposed, hashing by division is most common.
 * In hashing by division, the hash function has the form f(k) = k % D, where k is the key,
 * D is the length (number of buckets) of the hash table.
 *
 * A collision occurs whenever two different keys have the same home bucket.
 *
 * = DELETION =
 *
 * The deletion of a pair must leave behind a table on which the search method works correctly.
 *
 * A deletion may require us to move several pairs. The search for pairs to move begins just after
 * the bucket vacated by the deleted pair and proceeds to successive buckets until 1) we either
 * reach an empty bucket or 2) we return to the bucket from which the deletion took place.
 *
 * When pairs are moved up the table following a deletion, we must take care not to move a pair
 * to a position before its home bucket because making such a pair move would cause the search
 * for this pair to fail.
 *
 * An alternative to this method is to introduce the field never_used in each bucket. When the
 * table is initialized, this field is set to true for all buckets. When a pair is placed into a
 * bucket, its never_used field is set to false. Now condition (2) for search termination is
 * replaced by: a bucket with its never_used field equal to true is reached.
 *
 * We accomplish a removal by setting the table position occupied by the removed pair to NULL.
 * A new pair  may be inserted into the key empty bucket encountered during a search that
 * begins at the pair's home bucket.
 *
 * Notice that in this alternative scheme, never_used is never reset to true. After a while all
 * buckets have this field equal to false, and unsuccessful searches examines all buckets.
 *
 * To improve performance, we must reorganize the table when many empty buckets have their
 * never_used field equal to false. This reorganization could, for example, involve reinserting
 * all remaining pairs into an empty hash table.
 */

template<class T>
class Hash {
public:
    size_t operator()(const T key) const {
        return size_t(key);
    }
};

/* a specialization with type string */
template<>
class Hash<std::string> {
public:
    size_t operator() (const std::string key) const {
        unsigned long hash_value = 0;
        int length = (int) key.length();
        for (int i = 0; i < length; i++) {
            hash_value = 5 * hash_value + key.at(i);
        }
        return size_t(hash_value); // functional notation casting
    }
};

/* = LINEAR PROBING =
 *
 * The easiest way to find a place to put a value in the table is to search the
 * table for the next available bucket.
 *
 * On the other side, the search begins at the home bucket f(k) of the key k we
 * are searching for and continues by examining successive buckets in the table
 * until one of the following conditions happens:
 *   i) a bucket containing a pair with key k is reached
 *  ii) an empty bucket is reached
 * iii) we return to the home bucket
 */

/* HashTable class with linear probing */
// template<class K, class E> class Pair;

template<class K, class E>
class HashTable: public Dictionary<K, E> {
public:
    HashTable(int); // constructor
    bool empty() const{
        return (dsize == 0);
    };
    int size() const{
        return dsize;
    };
    void erase(const K &);
    void modify(const K &, const E &);
    void create(){};
    int search(const K &) const;
    Pair<K, E>* find(const K &) const;
    void insert( Pair<K, E> &);
private:
    Pair<K, E>** table; // hash table
    Hash<K> hashm; // maps type K to non negative integer(return a position)
    int dsize; // number of pairs in dictionary
    int divisor; // hash function divisor (it's the table max dimension)
};

template<class K, class E>
HashTable<K, E>::HashTable(int divisor) {
    this->divisor = divisor;
    dsize = 0;
    // table is an array of pointers to pairs of dimension "divisor"
    table = new Pair<K, E>*[divisor];
    for (int i = 0; i < divisor; i++)
        table[i] = NULL;
}

/* This method returns a bucket b in the table that satisfies exactly one of the following:
 * 1) table[b] points to a pair whose key is the_key
 * 2) no pair in the table has the key the_key, table[b] is NULL
 * 3) no pair in the table has the key the_key, table[b] has a key other than
 *    the_key, and the table is full
 */
template<class K, class E>
int HashTable<K, E>::search(const K &the_key) const {
    int h_b = (int)hashm(the_key) % divisor; // the home bucket
    int j = h_b;
    do {
        if (table[j] == NULL || table[j]->key == the_key) {
            return j; // 1) and 2) conditions
        }
        j = (j + 1) % divisor; // the next bucket
    } while (j != h_b);
    return j; // the table is full
}

/* The method HashTable<K,E>::find */
template<class K, class E>
Pair<K, E>* HashTable<K, E>::find(const K& key) const {
    // search the table
    int b = search(key);
    // see if a match was found at table[b]
    if (table[b] == NULL || table[b]->key != key)
        return NULL; // no match
    return table[b]; // matching pair
}

/* = INSERTING =
 * It begins by invoking the method search. If the returned bucket b is empty,
 * then there is no pair in the table with key p.key and the pair p may be
 * inserted into this bucket. If the returned bucket is not empty,
 * then it either contains a pair with key p.key or the table is full.
 * In the former case we change the second component of the pair stored
 * in the bucket to p.second; in the latter, we throw an exception
 */
template<class K, class E>
void HashTable<K, E>::insert(Pair<K, E> &p) {
    // search the table for a matching element
    int b = search(p.key);
    // chack if matching element found
    if (table[b] == NULL) {
        // no matching element and table not full
        table[b] = new Pair<K, E>(p);
        dsize++;
    } else {
        // check id duplicate or table full
        if (table[b]->key == p.key)
            table[b]->value = p.value; // duplicate, change table[b]->value
        else { // table is full
            throw HashTableFull();
        }
    }
}

template<class K, class E>
void HashTable<K, E>::erase(const K &k) {
    int b = search(k);
    if(table[b] != NULL) {
        delete table[b];
        table[b] = NULL;
    }
}

template<class K, class E>
void HashTable<K,E>::modify(const K &k, const E &e){
    Pair<K, E> *p = find(k);
    if(p != NULL) {
        p->value = e;
    } else {
        throw InexistentPair();
    }
}

#endif /* HASH_TABLE_H */
