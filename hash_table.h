#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string> 
#include <iostream>
#include "table_entry.h"

using namespace std;

class HashTable {
    int size_of_table;
    TableEntry **entry; // the hash table
    int current_size;  
    int hash_key(string); // gets a hash key 
    TableEntry* new_entry(string,int num = 0); // creates a new table entry for the hash table
    public: 
        HashTable();
        void Insert(string key,int num = 0); 
        int Search(string key);
};

#endif