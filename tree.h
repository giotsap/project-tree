#ifndef TREE_H
#define TREE_H

#include "data_structure.h"
#include "node.h"
#include <iostream>
#include <string> 

using namespace std;

class Tree : public DataStructure<Node> { // inherits from the DataStructure 
    private:
        void inorder(Node*); // traverses the tree with inorder 
        void preorder(Node*); // traverses the tree with the preorder 
        void postorder(Node*);  // traverses the tree with the postorder 
        int search(Node *,string); // searches a word in the tree 
        
    public:
        Tree(); 
        void Preorder(); 
        void Inorder();
        void Postorder();
        virtual void Insert(string key) = 0;
        virtual void Delete(string key) = 0;
        int Search(string key);
};

#endif