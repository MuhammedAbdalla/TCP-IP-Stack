/*
    glthread.h

    Glued Doubly Linked List
    
*/


typedef struct glthrad_node_ {
    struct glthread_node_ *left;
    struct glthread_node *right;
} glthread_node_t;

typedef struct glthread_ {
    glthread_node_t *head;
    int (*key_match)(void*, void*);
    int (*comparison_fn)(void*, void*);
    unsigned int offset;
} glthread_t;

