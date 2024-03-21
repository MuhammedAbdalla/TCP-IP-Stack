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
    for (_glnode = lstptr->head; _glnode; _glnode =_next) {     \
        _next = _glnode->right;                                 \
        ptr = (struct_type*)((char *)_glnode - lstptr->offset);

#define ITERATE_GLTHREADS_ENDS }}

/* macro for init glnode*/
#define glthread_node_init(glnode)  \
    glnode->left = NULL;            \
    glnode->right = NULL;           

/* macro for field name offset in any struct*/
#define offsetof(TYPE, FIELD)   \
    ((size_t)&((TYPE *)0)->FIELD)

typedef struct glthread_node_ glthread_node_t;
typedef struct glthread_ glthread_t;

typedef enum {
    glFALSE,
    glTRUE
} glthread_init;

struct glthread_node_ {
    glthread_node_t *left;
    glthread_node_t *right;
};

struct glthread_ {
    glthread_node_t *head;
    unsigned int offset;
};

void glthread_add (glthread_t *lst, glthread_node_t *glnode);

void glthead_remove(glthread_t *lst, glthread_node_t *node);

void init_glthread(glthread_t *glthread, unsigned int offset);

#endif /* __GLTHREADS__ */
