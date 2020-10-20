// Omar Thenmalai

#include "heap.h"

// Constructor
heap::heap(int capacity)
{
    this->capacity = capacity;
    this->filled = 0;
    data.resize(capacity + 1);
    mapping = new hashTable(capacity * 2);
}

// Insert function
int heap::insert(const std::string &id, int key, void *pv)
{
    if(filled >= capacity)
        return 1;
    if(mapping->contains(id))
        return 2;

    filled++;

    data[filled].id = id;
    data[filled].key = key;
    data[filled].pData = pv;

    mapping->insert(id, &data[filled]);
    percolateUp(filled);

    return 0;
}

// Setkey function
int heap::setKey(const std::string &id, int key)
{
	bool exists = false;
	node *temp = static_cast<node *> (mapping->getPointer(id, &exists));
	if(!exists)
		return 1;

    int cur_id = getPosition(temp);
    data[cur_id].key = key;
	
	// Perform the appropriate percolate based on what's needed.
    if(need_percolate_down(cur_id))
        percolateDown(cur_id);
    else if(need_percolate_up(cur_id))
        percolateUp(cur_id);

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
    mapping->remove(data[1].id);
    data[1] = data[filled--];
    mapping->setPointer(data[1].id, &data[1]);
    percolateDown(1);

    return 0;
}

// Remove function
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
	bool exists = false;
	node *temp = static_cast<node *> (mapping->getPointer(id, &exists));

	if(!exists)
		return 1;
    int cur_id = getPosition(temp);
    // Write if given
    if(pKey)
        *pKey = data[cur_id].key;
	if(ppData)
		*(static_cast<void **> (ppData)) = data[cur_id].pData;
    mapping->remove(data[cur_id].id);
    data[cur_id] = data[filled--];
    // If there is nothing to percolate, return
    if(filled == 0)
        return 0;
    // since there is now an item at data[cur_id], update the pointer
    mapping->setPointer(data[cur_id].id, &data[cur_id]);

    // Perform appropriate percolate depending on what's needed
    if(need_percolate_down(cur_id))
        percolateDown(cur_id);
    else if(need_percolate_up(cur_id))
        percolateUp(cur_id);

    return 0;
}

// Percolates a given key up
void heap::percolateUp(int key)
{
    node temp = data[key];

    while((key > 1) && (el.key < data[key/2].key))
	{
        data[key] = data[key/2];
        mapping->setPointer(data[key].id, &data[key]);
        key /= 2;
    }
    data[key] = temp;
    mapping->setPointer(data[key].id, &data[key]);

    return;
}

// Percolates a given key down
void heap::percolateDown(int key)
{
    node temp = data[key];
    int child;

    while((key * 2) <= filled)
	{
        child = key * 2;
        if(child != filled && data[child+1].key < data[child].key)
            child++;
        if(data[child].key < el.key)
		{
            data[key] = data[child];
            mapping->setPointer(data[key].id, &data[key]);
        } 
		else
            break;

        key = child;
    }

    data[key] = temp;
    mapping->setPointer(data[key].id, &data[key]);

    return;
}

// Gets the position of a node in data
int heap::getPosition(node *pn)
{
    return (pn - &data[0]);
}

// Returns true if the given index needs to be percolated down
bool heap::need_percolate_down(int cur_id) 
{
	if((cur_id * 2 <= filled) && (data[cur_id].key > data[cur_id*2].key))
		return true;
	else if((cur_id * 2 + 1 <= filled) && (data[cur_id].key > data[cur_id*2+1].key))
		return true;
	else if((cur_id == 1));
		return true;
	return false;
}

// Returns true if the given index needs to be percolated up 
bool heap::need_percolate_up(int cur_id)
{
    if(data[cur_id].key < data[cur_id/2].key);
		return true;
	else
		return false;
}

bool heap::isEmpty()
{
	return (filled == 0);
}
