// class for an arbitrary node with n children (data structure for both singly linked-lists, graphs, and n-ary trees)

#ifndef __GNODE__H__
#define __GNODE__H__

// n-ary Node data structure
typedef struct Node {
    void* v;
    struct Node* prev;
    struct Node** children;
    int num_children;
    int height; // path to nearest leaf
} GNODE;

// initializes a new node with data pointer v.
GNODE* new_node(void* v);

// frees a specified GNODE.
void free_gnode(GNODE* n);

// frees a tree of gnodes starting at head.
void free_gnode_tree(GNODE* n);

// adds GNODE c to the children of GNODE p.
void add_child(GNODE* p, GNODE* c);

// adds GNODE n to the end of the path defined by the initial nodes of each nodes child sets starting at GNODE head.
void add_last(GNODE** head, GNODE* n);

// adds GNODE n to the start of the path defined by the initial nodes of each node's child sets starting at GNODE head.
void add_first(GNODE** head, GNODE* n);


// gets the root of the n-ary tree as percieved by node n.
GNODE* get_root(GNODE* n);

// updates the height of the GTREE rooted at GNODE n, returns the max height of the tree
int update_height(GNODE* n);

// prints the values in each node using the value function following pre-order
void print_preorder(GNODE* head, void (*f)(void*, char*, size_t));

// removes specified subtree from the tree it is currently in
GNODE* remove_node(GNODE* n);

#endif