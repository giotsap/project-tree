#include "tree.h"

Tree::Tree() {
    entry = 0;
}

void Tree::inorder(Node *node){
    if (node)  //if there is a node
    { 
        inorder(node->l);  // visit its left child first
        cout << node->key << "->" << node->num <<endl; 
        inorder(node->r); // and then its right
    } 
}

void Tree::Inorder(){
    inorder(entry);
}

void Tree::preorder(Node *node){
    if (node){
        cout << node->key << "->" << node->num << endl;
        preorder(node->l);
        preorder(node->r);
    }
}

void Tree::Preorder(){
    preorder(entry);
}

void Tree::postorder(Node *node){
    if (node){
        postorder(node->l);
        postorder(node->r);
        cout << node->key << "->" << node->num << endl;
    }
}

void Tree::Postorder(){
    postorder(entry);
}

int Tree::search(Node *node,string key){
    if (!node) //if the node is empty
        return 0;

    if (key > node->key) //searches the tree based on the key 
        return search(node->r, key); // searches the right child
    else if (key < node->key)
        return search(node->l, key); // or the left child 
    else
        return node->num; // if the key in the node 
    
}

int Tree::Search(string key){
    return search(entry,key);
}