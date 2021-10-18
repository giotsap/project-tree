
#include "avl_tree.h"

Node* AVLTree::rotate(Node *node1, int type){
    switch(type){
        case 0: { // R Rotation
            Node* node2 = node1->l;  
            Node *unbal = node2->r; 

            // the rotation 
            node2->r = node1;
            node1->l = unbal;
            return node2; 
        }
        case 1: { // L Rotation
            Node* node2 = node1->r;  
            Node *unbal = node2->l;

            // the rotation  
            node2->l = node1;  
            node1->r = unbal; 
            return node2;
        }
    }
}

int AVLTree::height_of_node(Node *node){
    return (node ? node->h : 0 ); 
}
int AVLTree::balance_score(Node *node){ 
    return (node ? height_of_node(node->l) - height_of_node(node->r) : 0);
}

Node* AVLTree::R_rotate(Node *node, string key, int b_score, int type){
    /* 
        condition depends on the function that calls the operation. (insert->type=0, delete->type=1)
    */
    bool condition = (type == 0 ? (b_score > 1 && key < node->l->key) : (b_score > 1 && balance_score(node->l) >= 0));
    if (condition) {
            Node *new_node =  rotate(node,0); // applies the rotation 

            //updates the heights of the nodes 
            node->h = 1 + ( height_of_node(node->l) > height_of_node(node->r) ? height_of_node(node->l) : height_of_node(node->r));
            new_node->h = 1 + (height_of_node(new_node->l) > height_of_node(new_node->r) ? height_of_node(new_node->l) : height_of_node(new_node->r));
            return new_node;  
    }
    return node;
}

Node* AVLTree::L_rotate(Node *node, string key, int b_score, int type){
    bool condition = (type == 0 ? (b_score < -1 && key > node->r->key) : (b_score < -1 && balance_score(node->r) <= 0));
    if (condition) {
            Node *new_node = rotate(node,1);
            node->h = 1 + ( height_of_node(node->l) > height_of_node(node->r) ? height_of_node(node->l) : height_of_node(node->r));
            new_node->h = 1 + (height_of_node(new_node->l) > height_of_node(new_node->r) ? height_of_node(new_node->l) : height_of_node(new_node->r));
            return new_node;
    }
    return node;
}

Node* AVLTree::LR_rotate(Node *node, string key,int b_score, int type){
    bool condition = (type == 0 ? (b_score > 1 && key > node->l->key) : (b_score > 1 && balance_score(node->l) < 0));
    if (condition) {
            node->l = L_rotate(node->l,key,b_score,type);
            return R_rotate(node,key,b_score,type);
    }
    return node;
}

Node* AVLTree::RL_rotate(Node* node, string key,int b_score, int type){
    bool condition = (type == 0 ? (b_score < -1 && key < node->r->key) :(b_score < -1 && balance_score(node->r) > 0));
    if (condition) {
            node->r = R_rotate(node->r,key,b_score,type);
            return L_rotate(node,key,b_score,type);
    }
    return node;
}

Node* AVLTree::do_rotations(Node* node,string key,int type){ 
    /*
        If a rotation has to be applied in the avl tree, then this function does it. 
    */
    int b_score = balance_score(node); // the balance score of the node
    node = R_rotate(node,key,b_score,type); 
    node = L_rotate(node,key,b_score,type);
    node = LR_rotate(node,key,b_score,type);
    node = RL_rotate(node,key,b_score,type);
    return node;
}

Node* AVLTree::add_a_node(Node* node,string key){ 
    /*
        adds a new node to the tree
    */
    if (!node){ // the node is empty
        Node* new_node = new Node; // creates a new node
        new_node->key = key; // assigns the key
        new_node->l = 0;
        new_node->r = 0 ;
        new_node->h = 1; // height is equal to 1
        new_node->num = 1; 
        return new_node; 
    } 

    /*
        the node is not empty
    */
   
    if ( key < node->key)  node->l = add_a_node(node->l,key); // traverses left 
    else if (key > node->key) node->r = add_a_node(node->r,key); // traverses right
    else {node->num++; return node;} // the word is in the node, increases the counter 

    // updates the height of each node recursevily. 
    node->h = 1 +(height_of_node(node->l) > height_of_node(node->r) ? height_of_node(node->l) : height_of_node(node->r));
   
    // applies the rotations if it is needed.
    return do_rotations(node,key,0);
} 


void AVLTree::Insert(string key){ 
    entry  = add_a_node(entry,key);
}

Node* AVLTree::delete_a_node(Node* node,string key){
    // the node is empty
    if (!node)  return 0;
 
    // as in insert function
    if ( key < node->key )  node->l = delete_a_node(node->l, key);
    else if (key > node-> key) node->r = delete_a_node(node->r, key);
    else { 
        if (node->l && node->r){ // the node has two childrean
            Node* smaller = node->r; // gets the larger word
            while (smaller->l) smaller = smaller->l; // and the find the smallest one
            node->key = smaller->key; // copies the key to the current node
            node->r = delete_a_node(node->r,smaller->key); 
        } else { // only one child or not
            Node *child = node->l ? node->l : node->r; // the child
            
            if (!child) { // no child 
                child = node; // swap
                node = 0; 
            }else *node = *child;  
            delete child; 
        }
        if (!node) return 0;
        
        // as in insert function
        node->h = 1 + (height_of_node(node->l) > height_of_node(node->r) ? height_of_node(node->l) : height_of_node(node->r));
        return do_rotations(node,key,1);
    }   
    return node;
}

void AVLTree::Delete(string key){
    entry = delete_a_node(entry,key);
}
