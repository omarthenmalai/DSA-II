// Omar Thenmalai

#ifndef _HEAP_H
#define _HEAP_H

#include "hash.h"
#include <vector>
#include <string>

class heap {
    public:

    // heap - The constructor allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified capacity
    //
    heap(int capacity);

    //
    // insert - Inserts a new node into the binary heap
    //
    // Inserts a node with the specified id string, key,
    // and optionally a pointer. They key is used to
    // determine the final position of the new node.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is already filled to capacity
    //   2 if a node with the given id already exists (but the heap
    //     is not filled to capacity)
    //
    int insert(const std::string &id, int key, void *pv = NULL);

    //
    // setKey - set the key of the specified node to the specified value
    //
    // I have decided that the class should provide this member function
    // instead of two separate increaseKey and decreaseKey functions.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int setKey(const std::string &id, int key);

    //
    // deleteMin - return the data associated with the smallest key
    //             and delete that node from the binary heap
    //
    // If pId is supplied (i.e., it is not NULL), write to that address
    // the id of the node being deleted. If pKey is supplied, write to
    // that address the key of the node being deleted. If ppData is
    // supplied, write to that address the associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is empty
    //
    int deleteMin(std::string *pId = NULL, int *pKey = NULL, void *ppData = NULL);

    //
    // remove - delete the node with the specified id from the binary heap
    //
    // If pKey is supplied, write to that address the key of the node
    // being deleted. If ppData is supplied, write to that address the
    // associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    //
    int remove(const std::string &id, int *pKey = NULL, void *ppData = NULL);

    // Private members, an add-on to the public members provided in the sample code
    private:
    class node { // Inner class
        public:
            std::string id; // ID
            int key; // Key
            void *pData; // Pointer to the node's data
    };

    int capacity; // Current capacity of the heap
    int filled; // Number of occupied items in table

    std::vector<node> data; // Entries are here

    hashTable *map; // Mapping ids to pointers
    
    void percolateUp(int key); // Percolates up a given key
    void percolateDown(int key); // Percolates down a given key
    int getPosition(node *pn); // Finds the position of a node in data, returns the position or -1 if error
    decreaseKey(int pos);
    increaseKey(int pos);
    bool isEmpty();
};

#endif //_HEAP_H