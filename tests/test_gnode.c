#include <stdio.h>
#include <stdlib.h>
#include "../dependencies/headers/gnode.h"
#include "../dependencies/headers/helpers.h"

void test_init() {
    char a = 'a', b = 'b', c = 'c';
    GNODE* head = new_node(&a);
    GNODE* n2 = new_node(&b);
    GNODE* n3 = new_node(&b);
    GNODE* n4 = new_node(&c);
    GNODE* n5 = new_node(&a);
    GNODE* n6 = new_node(&b);
    GNODE* n7 = new_node(&c);
    GNODE* n8 = new_node(&a);

    add_last(&head, n2);
    add_last(&head, n3);
    add_child(n2, n4);
    add_child(n2, n5);
    add_child(n2, n6);
    add_child(head, n7);
    add_child(n7, n8);

    print_preorder(head, char_conv);

    free_gnode_tree(head);

    printf("PASS - test_init\n");
}

void test_removal() {
    char a = 'a', b = 'b', c = 'c', d = 'd';
    GNODE* c_1 = new_node(&a);
    GNODE* head = new_node(&b);
    GNODE* c21 = new_node(&c);
    GNODE* c22 = new_node(&d);
    GNODE* c11 = new_node(&c);

    add_last(&head, c21);
    add_last(&head, c22);

    add_first(&head, c_1);

    add_child(head, c11);


    print_preorder(head, char_conv);
    printf("\n");

    GNODE* head2 = remove_node(head->children[0]);

    print_preorder(head, char_conv);
    printf("\n");
    print_preorder(head2, char_conv);
    printf("\n");

    printf("PASS - test_removal\n");

    free_gnode_tree(head);
    free_gnode_tree(head2);
}

int main() {
    test_init();
    test_removal();

    exit(0);
}