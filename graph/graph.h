/*
    Graph.h

*/

#ifndef __GRAPH__
#define __GRAPH__

#include "gluethread/glthread.h"
#include <stdlib.h>

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10

// forward declaration
typedef struct node_ node_t;
typedef struct link_ link_t;
typedef struct interface_ interface_t;
typedef struct graph_ graph_t;

struct interface_ {
    char if_name[IF_NAME_SIZE];
    node_t *att_node; // pointer usage
    link_t *link;     // pointer usage
} ;

struct link_
{
    interface_t intf1;      // complete usage
    interface_t intf2;      // complete usage
    unsigned int cost;
};

struct node_
{
    char node_name[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE];  
    glthread_node_t graph_glue;
};

struct graph_ {
    /* data */
    char topology_name[32];
    glthread_t node_list;
};

static inline node_t *get_nbr_node(interface_t *interface) {
    if (!interface) return NULL;
    return interface->att_node;
}

static inline int get_node_intf_available_slot(node_t *node) {
    if (!node) return -1;
    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (node->intf[i] == NULL) {
            return i;
        }
    }
    return -1;
}

graph_t *create_new_graph(char *topology_name);

node_t *create_graph_node(graph_t *graph, char *node_name);

void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost);

void dump_graph(graph_t *graph);

#endif