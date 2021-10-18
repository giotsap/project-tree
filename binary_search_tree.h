#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "tree.h"
#include <string> 

using namespace std;

class BinarySearchTree : public Tree{
    Node* add_a_node(Node*,string); // adds a new node in the tree 
    Node* delete_a_node(Node*,string); // delete a node of the tree
    public:
        BinarySearchTree() : Tree() {}
        void Insert(string key);
        void Delete(string key);

};

#endif 