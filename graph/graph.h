/*
    Graph.h

*/

#ifndef __GRAPH__
#define __GRAPH__

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10

// forward declaration
typedef struct node_ node_t;
typedef struct link_ link_t;
typedef struct interface_ interface_t;
typedef struct graph_ graph_t;

#include "gluethread/glthread.h"
#include "net/net.h"
#include "utils/utils.h"
#include <stdlib.h>
#include <string.h>

struct interface_ {
    char if_name[IF_NAME_SIZE];
    intf_nw_prop_t intf_nw_prop;
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
    node_nw_prop_t node_nw_prop;
    interface_t *intf[MAX_INTF_PER_NODE];  
    glthread_node_t graph_glue;
};

struct graph_ {
    /* data */
    char topology_name[32];
    glthread_t *node_list;
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

/*
 Write a function in graph.h file which returns pointer to the local interface of a node, searched searched by if_name.
*/
static inline interface_t * get_node_if_by_name(node_t *node, char *if_name) {
    if (!node) return NULL;

    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (strcmp(node->intf[i]->if_name, if_name) == 0) {
            return node->intf[i];
        }
    }
    return NULL;
}

/*
 Write a function in graph.h file which returns pointer node present in a graph list, searched by node name.
*/
static inline node_t *get_node_by_node_name(graph_t *topo, char *node_name) {
    if (!topo) return NULL;
    
    node_t *ptr = NULL;
    ITERATE_GLTHREADS_BEGIN(topo->node_list, node_t, ptr){
        if (strcmp(ptr->node_name, node_name) == 0) {
            return ptr;
        }
    } ITERATE_GLTHREADS_ENDS;

    return NULL;
}


graph_t *create_new_graph(char *topology_name);

node_t *create_graph_node(graph_t *graph, char *node_name);

void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost);

void dump_graph(graph_t *graph);

#endif