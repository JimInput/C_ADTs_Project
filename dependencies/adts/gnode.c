#include "../headers/helpers.h"
#include "../headers/gnode.h"

GNODE* new_node(void* v) {
    GNODE* n = malloc(sizeof(GNODE));
    if (n == NULL) {
        free(n);
        return NULL;
    }

    n->children = (GNODE**) malloc(MAX_CHILDREN*sizeof(GNODE*));
    if (n == NULL) {
        free(n->children);
        return NULL;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        n->children[i] = NULL;
    }

    n->v = v;
    n->prev = NULL;
    n->height = 0;
    n->num_children = 0;

    return n;
}

void free_gnode(GNODE* n) {
    if (n == NULL)
        return;

    if (n->children != NULL) 
        free(n->children);

    free(n);
}

void free_gnode_tree(GNODE* n) {
    if (n == NULL) 
        return;

    if (n->children != NULL) {
        for (int i = 0; i < n->num_children; i++) {
            free_gnode_tree(n->children[i]);
        }
    }

    free_gnode(n);
}

void add_child(GNODE* p, GNODE* c) {
    if (p == NULL || c == NULL || p->children == NULL)
        return;

    if (p->num_children < MAX_CHILDREN) {
        p->children[p->num_children] = c;
        p->num_children += 1;
        p->height = max(1+c->height, p->height);
        c->prev = p;
    }

    update_height(get_root(p));

}

// gets root of n-ary tree from a specific node n
GNODE* get_root(GNODE* n) {
    GNODE* curr = n;
    while (curr->prev != NULL) {
        curr = curr->prev;
    }
    return curr;
}

void add_last(GNODE** head, GNODE* n) {
    if (n == NULL)
        return;

    if (*head == NULL) {
        *head = n;
        return;
    }

    GNODE* curr = (*head);

    while (curr->num_children > 0 && curr->children != 0) {
        curr = curr->children[0];
    }

    add_child(curr, n);
}

void add_first(GNODE** head, GNODE* n) {
    if (n == NULL || n->num_children >= MAX_CHILDREN)
        return;

    if (*head == NULL) {
        *head = n;
        return;
    }

    (*head)->prev = n;
    n->children[n->num_children] = *head;
    n->prev = NULL;
    n->num_children++;
    n->height = max(n->height, 1+(*head)->height);

    (*head) = n;
}

int update_height(GNODE* n) {
    if (n == NULL) {
        return -1;
    }

    int max_h = -1;
    for (int i = 0; i < n->num_children; i++) {
        int child_height = update_height(n->children[i]);
        max_h = max(max_h, child_height);
    }

    n->height = max_h + 1;
    return n->height;
}

void print_preorder(GNODE* head, void (*f)(void*, char*, size_t)) {
    char out[TEST_BUFFER_SIZE];
    f(head->v, out, TEST_BUFFER_SIZE);
    printf("%3s - h=%d\n", out, head->height);
    for (int i = 0; i < head->num_children; i++) {
        print_preorder(head->children[i], f);
    }
}

GNODE* remove_node(GNODE* n) {
    if (n == NULL || n->prev == NULL) 
        return NULL;
    
    GNODE* parent = n->prev;
    int child_i = -1;
    // handle parent reindexing of children
    for (int i = 0; i < parent->num_children; i++) 
        if (parent->children[i] == n) {
            child_i = i;
            break;
        }

    if (child_i == -1)
        return NULL;

    for (int k = child_i; k < parent->num_children-1; k++) {
        parent->children[k] = parent->children[k+1];
    }

    parent->children[parent->num_children] = NULL;

    parent->num_children--;
    n->prev = NULL;
    update_height(parent);

    return n;
}
