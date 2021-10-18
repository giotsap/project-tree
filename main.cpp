#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "data_structure.h"
#include "binary_search_tree.h"
#include "avl_tree.h"
#include "table_entry.h"
#include "hash_table.h"

using namespace std;
/*
    returns true if a word will be in the q set.
*/
bool included(){
    switch(rand()%2){
        case 0: return false;
        case 1: return true;
    }
    return false;
}
/*
    reads the file and returns the updated data structures and the q set.
*/
void readfile(char *filename,string* q_set, DataStructure<Node> *ds[2], HashTable *hash_table){
    ifstream file;
    string word; // stores a word from the fild
    int random_words_counter = 0; // counter for the q set

    file.open (filename);
    if (!file.is_open()) { // if there is not such file
        cout <<"Please include the file path as argument" << endl;
        exit(1); // exit the program
    }
    while (file >> word) // for each word in the file
    {
        if (random_words_counter < 1000) { // q set has less than 1000 words
            if (included()) {
                bool exist = false;
                for (int i=0;i<random_words_counter;i++){
                    if (q_set[i] == word) {
                        exist = true;
                        break;
                    }
                }
                if (!exist) // q set without duplicates
                    q_set[random_words_counter++] = word; // fills the q set with words
            }
        }
        for (int i=0;i<2;i++) ds[i]->Insert(word); // inserts the words in the data structures
        hash_table->Insert(word);
    }
}

/*
    Calculates the time of a data structure to find words from the set q and prints the time
    of the_algorithm
*/
template <class T> void calculcate_time(T *data_structure,string *q, string the_algorithm){
    auto t1 = chrono::high_resolution_clock::now(); // calculates the time when the algorithm starts
    for (int i=0;i<1000;i++){
        data_structure->Search(q[i]); // calls the search function from the binary search tree.
    }
    auto t2 = chrono::high_resolution_clock::now(); // calculates the time when the algorithm ends

    chrono::duration<int64_t,nano> elapsed = t2 - t1; // calculates the difference between the begin and end time.
    cout << "Time taken by algorithm " << the_algorithm  << ":" <<  fixed
        << elapsed.count() / pow(10,6)  << setprecision(5); // prints the time in miliseconds.
    cout << " mil " << endl;
}

int main(int argc, char *argv[]){
    string *q = new string[1000]; // the q set
    DataStructure<Node> *ds[2]; // trees inherit the DataStructure
    HashTable *hash_table = new HashTable;
    for (int i=0;i<2;i++) // initializes the table
        ds[i] = 0;
    ds[0] = new BinarySearchTree(); // dynamically creates a binary search tree
    ds[1] = new AVLTree(); // dynamically creates an avl tree.
    readfile(argv[1],q,ds,hash_table); // reads the file


    //((Tree *)ds[1])->Preorder(); // uncoment this to traverse the avl tree

    // //((Tree *)ds[0]) ->Inorder();// uncomment this to traverse the binary search tree.
    string the_algorithm[] = {"binary search tree", "avl tree"};
    for (int i=0;i<2;i++) {
        calculcate_time(ds[i],q, the_algorithm[i]);
    }
    calculcate_time(hash_table,q, "hash table");


    // prints the counters of the words in the set Q for each data structure.
    for (int i=0;i<1000;i++){
        cout << q[i] << ":\t"  << ds[0]->Search(q[i]) << "->" << ds[1]->Search(q[i]) << "->" << hash_table->Search(q[i]) << endl;
    }
    return 0;
}
