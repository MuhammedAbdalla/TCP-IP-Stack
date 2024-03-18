/*
    glthread.c
*/

#include "glthread.h"
#include <stdlib.h>

/* 
    private functions to add a new_node after current node
    inserts the head node right of the new node
*/
static void _glthread_add_next(glthread_node_t *curr_node, glthread_node_t *new_node) {
    if (!curr_node->right) {
        curr_node->right = new_node;
        new_node->left = curr_node;
        return;
    }

    glthread_node_t *temp = curr_node->right;
    curr_node->right = new_node;
    new_node->left = curr_node;
    temp->left = new_node;
}
/*
    insert a new GLnode into a glthread at the first position
    new node becomes the head of the list
*/
void glthread_add(glthread_t *lst, glthread_node_t *glnode) {
    glnode->left = NULL;
    glnode->right = NULL;

    // if list has no head, then insert glnode as head
    if (!lst->head) {
        lst->head = glnode;
        return;
    }
    glthread_node_t *head = lst->head;
    _glthread_add_next(glnode, head);
    lst->head = glnode;
}

static void _remove_glthread(glthread_node_t *glnode) {
    if (!glnode->left) {
        if (glnode->right) {
            glnode->right->left = NULL;
            glnode->right = 0;
            return;
        }
        return;
    }

    if(!glnode->right) {
        glnode->left->right = NULL;
        glnode->left = NULL;
        return;
    }

    glnode->left->right = glnode->right;
    glnode->right->left = glnode->left;
    glnode->left = 0;
    glnode->right = 0;
}

void gltrhead_remove(glthread_t *lst, glthread_node_t *glnode) {
    glthread_node_t *head = lst->head;

    if (head == glnode) {
        lst->head = head->right;
    }
    _remove_glthread(glnode);
}

void init_glthread(glthread_t *glthread, unsigned int offset) {
    if (glthread->head == NULL) {
         glthread_node_init(glthread->head);
    }
}
