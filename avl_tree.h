#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "tree.h"
#include <string> 

using namespace std;

class AVLTree : public Tree{
    Node* add_a_node(Node*,string); // adds a new node in the tree 
    Node* delete_a_node(Node*,string); // deletes a node of the tree
    Node* rotate(Node*, int); // core function for a rotate
    Node* R_rotate(Node*, string, int, int); // the R rotate
    Node* L_rotate(Node*, string, int, int ); // the L rotate
    Node* RL_rotate(Node*, string, int, int ); // the RL rotate
    Node* LR_rotate(Node*, string, int, int ); // the LR rotate
    Node* do_rotations(Node*, string, int); // applies all the rotations
    int height_of_node(Node* ); // returns the height of a node 
    int balance_score(Node* ); // returns the balance score for a node
    public:
        AVLTree() : Tree() {}
        void Insert(string key);
        void Delete(string key);

};

#endif 