#include "hash_table.h"

HashTable::HashTable(){ 
    current_size = 0;   // increases when a new word is inserted  
    size_of_table = 80000; // the size of the hash table
    entry = new TableEntry*[size_of_table]; // dynamically creates a new hash table 
    for (int i=0;i<size_of_table;i++) entry[i] = 0;  // initializes the table 
}

int HashTable::hash_key(string key){
    /* 
         The djb2 algorithm 
    */ 
    unsigned long sum = 1345;  
    int c,i=0;
    while ((c = key[i++]))
        sum = ((sum >> 5) + sum) + c;
    return sum % size_of_table; 
}

TableEntry* HashTable::new_entry(string key,int num){
    TableEntry *e = new TableEntry; // creates a new table entry
    e->key = key;  // assigns the key
    e->num = (num > 0 ? num : 1); // num, if this function is called when we apply re-hashing
    return e; 
}

int HashTable::Search(string key){ 
    int hkey = hash_key(key); // gets the hash key
    if (!entry[hkey]) return 0; // the key is not in the table 
    while (entry[hkey] && entry[hkey]->key != key) hkey++; // searches the key in the hash table
    if (entry[hkey]) return entry[hkey]->num; // the key is in the table, gets the counter
    else return 0;
}

void HashTable::Insert(string key,int num){ 
    int hkey = hash_key(key); // gets the hash key  
    if (!entry[hkey]) { // key is not in the table 
        entry[hkey] = new_entry(key,num); // creates a new entry
        current_size++; // increases the number of words in the table 
        return; 
    } 
    /*
        The word is probably in the hash table or there is other 
        key in the hkey position 
    */
    while (entry[hkey] && entry[hkey]->key != key) 
        hkey++;
    if (entry[hkey]) entry[hkey]->num++; // the word is in the table, increases the counter
    else { 
        entry[hkey] = new_entry(key,num); // the word is not in table, creates a new node
        current_size++; // increases the number of words in the table
    }

    if (size_of_table < current_size) { // needs resize
        size_of_table *= 2; // the new size of the table 
        current_size = 0; 
        TableEntry **e = entry; // points to the old table 
        entry = new TableEntry*[size_of_table*2]; // creates the new table 
        for (int i=0;i<size_of_table*2;i++) entry[i] = 0; // initializes the new table 
        for (int i=0;i<size_of_table/2;i++)  // gets all words from the old table
            if (e[i])  
                Insert(e[i]->key, e[i]->num); // inserts to the new table
        
        delete [] e; // removes the old table 
    }
}