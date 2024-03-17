/*
    glthread.h
    Glued Doubly Linked List
*/

#ifndef __GLTHREADS__
#define __GLTHREADS__

/* iterative macro to iterate over GLThreads*/
#define ITERATE_GLTHREADS_BEGIN(lstptr, struct_type, ptr)       \
{                                                               \
    glthread_node_t *_glnode = NULL, *_next = NULL;             \
    for (_glnode = lsptr->head; _glnode; _glnode =_next) {      \
        _next = _glnode->right;                                 \
        ptr = (struct_type*((char *)_glnode - lstprtr->offset))
#define ITERATE_GLTHREADS_ENDS }}

/* macro for init glnode*/
#define gltrhead_node_init(glnodes) \
    glnode->left = NULL;            \
    glnode->right = NULL;           \

/* macro for field name offset in any struct*/
#define offsetof(struct_name, field_name)   \
    ((unsigned int)&((struct_name *)0)->field_name)

typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node *right;
} glthread_node_t;

typedef struct glthread_ {
    glthread_node_t *head;
    // int (*key_match)(void*, void*);
    // int (*comparison_fn)(void*, void*);
    unsigned int offset;
} glthread_t;

void glthread_add (glthread_t *lst, glthread_node_t *glnode);

void glthead_remove(glthread_t *lst, glthread_node_t *node);

void init_glthread(glthread_t *glthread, unsigned int offset);

#endif /* __GLTHREADS__ */
