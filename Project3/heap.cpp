// Omar Thenmalai

#include "heap.h"


heap::node::node() = default;

heap::node::node(std::string _id, int _key, void *_pData) : id(std::move(_id)), key(_key), pData(_pData) {}

// Constructor
heap::heap(int capacity)
{
    this->capacity = capacity;
    this->filled = 0;
    data.resize(capacity + 1);
    map = new hashTable(capacity * 2);
}

// Insert function
int heap::insert(const std::string &id, int key, void *pv)
{
    if(filled >= capacity)
        return 1;
    if(map->contains(id))
        return 2;

    data[0] = std::move(node(id, key, pv));
	int pos = ++filled;
	int new_pos = percolateUp(pos);
    map->insert(id, &data[new_pos]);
    return 0;
}

// Setkey function
int heap::setKey(const std::string &id, int key)
{
	bool exists = false;
	node *temp = static_cast<node *> (map->getPointer(id, &exists));
	if(!exists)
		return 1;
	int pos = getPosition(temp);
	
	if(temp->key < key)
		increaseKey(pos, key);
	else if(temp->key > key)
		decreaseKey(pos, key);
    return 0;
}

// DeleteMin function
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    // deleteMin shouldn't do anything if the heap is empty.
    if(filled == 0)
        return 1;
	
    if(pId)
        *pId = data[1].id;
    if(pKey)
        *pKey = data[1].key;
	if(ppData)
		*(static_cast<void **> (ppData)) = data[1].pData;
    map->remove(data[1].id);
    data[1] = std::move(data[filled--]);
    map->setPointer(data[1].id, &data[1]);
    percolateDown(1);

    return 0;
}

// Remove function
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
	bool exists = false;
	node *temp = static_cast<node *> (map->getPointer(id, &exists));

	if(!exists)
		return 1;
    if(pKey)
        *pKey = temp->key;
	if(ppData)
		*(static_cast<void **> (ppData)) = temp->pData;
    int pos = getPosition(temp);
	decreaseKey(pos, std::numeric_limits<int>::min());
	deleteMin();
    return 0;
}

int heap::percolateUp(int pos)
{
    node temp = data[pos];	

    while((pos > 1) && (temp.key < data[pos/2].key))
	{
        data[pos] = data[pos/2];
        map->setPointer(data[pos].id, &data[pos]);
        pos /= 2;
    }
    data[pos] = std::move(data[0]);
    map->setPointer(data[pos].id, &data[pos]);

    return pos;
}

// Percolates a given key down
int heap::percolateDown(int pos)
{
    node temp = std::move(data[pos]);
    int child;

    while((pos * 2) <= filled)
	{
        child = pos * 2;
        if(child != filled && data[child+1].key < data[child].key)
            child++;
        if(data[child].key < temp.key)
		{
            data[pos] = std::move(data[child]);
            map->setPointer(data[pos].id, &data[pos]);
        } 
		else
            break;

        pos = child;
    }

    data[pos] = temp;
    map->setPointer(data[pos].id, &data[pos]);

    return pos;
}

// Gets the position of a node in data
int heap::getPosition(node *pn)
{
    return static_cast<int>(pn - &data[0]);
}

int heap::decreaseKey(int pos, int key)
{
	data[pos].key = key;
	data[0] = data[pos];
	return percolateUp(pos);
}

int heap::increaseKey(int pos, int key)
{
	data[pos].key = key;
	return percolateDown(pos);
	
}

bool heap::isEmpty()
{
	return (filled == 0);
}