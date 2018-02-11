/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 * 
 * A dictionary is a collection of pairs of the form (k,v), where k is a
 * key and v is the value associated with the key k (equivalently, v is the
 * value whose key is k).
 */

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

template<class K, class E>
class Pair {
public:
    Pair() {}
    Pair(Pair<K, E> &p) {
        key = p.key;
        value = p.value;
    }
    K key;
    E value;
};


template <class K, class E>
class Dictionary {
public:
    // create an empty dictionary
    virtual void create() = 0;
    // return true if the dictionary is empty
    virtual bool empty() const = 0;
    // return the number of pairs in the dictionary
    virtual int size() const = 0;
    // return the pair with key k
    virtual Pair<K, E>* find(const K &k) const = 0;
    // insert the pair p into the dictionary
    virtual void insert(Pair<K, E> &p) = 0;
    // delete the pair with key k
    virtual void erase(const K &k) = 0;
    // modify the value of the pair with key k to e
    virtual void modify(const K &k, const E &e) = 0;
};

#endif /* _DICTIONARY_H */
