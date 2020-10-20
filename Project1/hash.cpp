// ECE-165 Data Structures & Algorithms 2 Program #1
// Omar Thenmalai

#include "hash.h"

hashTable::hashTable(int size) // hashTable constructor
{
    filled = 0;
    capacity = getPrime(size);
    data.resize(capacity);
    for(int i = 0; i < data.size(); i++)
        data[i].isOccupied = false;
}
int hashTable::insert(const std::string &key, void *pv) // Creates a key using a NULL pointer and rehashes the table at half of the current capacity
{
    int id;
    if(contains(key))
        return 1;
    if(filled >= capacity/2)
        if(!rehash())
            return 2;
    id = hash(key);
    while(data[id].isOccupied)
        id = (id+1) % capacity;
    data[id].key = key;
    data[id].isOccupied = true;
    data[id].isDeleted = false;
    data[id].pv = NULL;
    filled++;

    return 0;
}
bool hashTable::contains(const std::string &key) // Check if the given key is in the hashtable
{   
    if(findPos(key) == -1)
        return false;
    return true;
}

int hashTable::hash(const std::string &key) // Hash function
{
    int val = 0;
    for(int i = 0; i < key.length(); i++)
        val = 37 * val + key[i];
    val %= capacity;
    if(val < 0)
        val += capacity;
    return val;
}

int hashTable::findPos(const std::string &key) // Find the position of the given key in the hashTable
{
    int pos = hash(key);

    if(!data[pos].isOccupied)
        return -1;

    while(data[pos].isOccupied)
        if(data[pos].key == key && !data[pos].isDeleted)
            return pos;
        else
            pos = (pos+1) % capacity;

    return -1;
}
bool hashTable::rehash() // Rehash function
{
    std::vector<hashItem> prev_data = data;
    capacity = getPrime(capacity);
    data.clear();
    data.resize(capacity);

    for(int i = 0; i < capacity; i++)
        data[i].isOccupied = false;
    for(int i = 0; i < prev_data.size(); i++)
        if(prev_data[i].isOccupied)
            insert(prev_data[i].key);
    prev_data.clear();

    return true;
}
unsigned int hashTable::getPrime(int size) // Returns the next largest prime number from the list
{
	int primes[7] = {100003, 200003, 400009, 800011, 1600033, 3200003, 6400013};
    for(int i = 0; i < sizeof(primes); i++)
        if(primes[i] > size)
            return primes[i];
    return 1;
}


void *hashTable::getPointer(const std::string &key, bool *b) {
    int id = findPos(key);
    if(id != -1 && !data[id].isDeleted) {
        *b = true;
        return data[id].pv;
    }
    *b = false;
    return NULL;
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int id = findPos(key);
    if(id == -1)
        return 1;
    data[id].pv = pv;
    return 0;
}

bool hashTable::remove(const std::string &key) {
    int idx = findPos(key);
    if(idx == -1)
        return false;
    data[idx].isDeleted = true;

    return true;
}
