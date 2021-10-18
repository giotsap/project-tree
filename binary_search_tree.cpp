#include "binary_search_tree.h"

Node* BinarySearchTree::add_a_node(Node *root,string key){
    if (!root){ // tree without nodes 
        Node *node = new Node;  // creates a new node
        node->key = key; // assigns the information to the new node
        node->l = 0;
        node->r = 0;
        node->num = 1;
        return node;  // returns the new node 
    }

    if (root->key < key ) 
        root->r = add_a_node(root->r,key); // traverses right the tree
    else if (root->key > key) 
        root->l =  add_a_node(root->l,key); // traverses left the tree 
    else 
        root->num++;   // increases the counter if the key in the tree 
    return root; 

}

void BinarySearchTree::Insert(string key){
    entry = add_a_node(entry,key); // calls the insert function and updates the tree
}

Node* BinarySearchTree::delete_a_node(Node* node, string key){
    if (!node) // the key is not in the tree
        return 0; 
    if (node->key < key) 
        node->r = delete_a_node(node->r,key); 
    else if (node->key > key)
        node->l = delete_a_node(node->l,key); 
    else{ // if the key in the tree
        if (!node->l) { //and has only right child 
            Node *l = node->r; //stores the right child
            delete node; //deletes the old node 
            node = l; // makes the right child to be the node
        }
        else if (!node->r){ // and has only left child 
            Node *r = node->l; //stores the left child 
            delete node; // deletes the old node
            node =r; // makes the left child to be the node 
        }else if (node->l && node->r){ // and has two childrean 
            Node *l = node->l; // keeps the node with the smaller key 
            Node *pr = node;
            while (l->r){ // and then searches the larger key which is in the right right ... child 
                   pr = l;
                l = l->r;
            }
            node->key = l->key; // replaces the key of the node with the node of the right right ... child 
            node->l = delete_a_node(node->l, l->key); // updates the left child of the node 
                
            }
        }
            
    return node;
}

void BinarySearchTree::Delete(string key){
    entry = delete_a_node(entry,key); // calls the delete function and updates the tree
}