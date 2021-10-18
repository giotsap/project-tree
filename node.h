#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node{
    public:
        string key; // the word of the node
        Node *l; // the left child of the node
        Node *r; // the right child of the node
        int num; // a counter for the word 
        int h; // the height of the node;
};

#endif