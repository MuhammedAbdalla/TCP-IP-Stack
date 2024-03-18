/*
    Graph.h

*/

#include "gluethread/glthread.h"

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10

// forward declaration
struct node_t;
struct link_t;

typedef struct interface_
{
    char if_name[IF_NAME_SIZE];
    struct node_t *att_node; // pointer usage
    struct link_t *link;     // pointer usage
} interface_t;

typedef struct link_
{
    interface_t intf1;      // complete usage
    interface_t intf2;      // complete usage
    unsigned int cost;
} link_t;

typedef struct node_
{
    char node_name[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE];  
    glthread_t graph_glue;
} node_t;

typedef struct graph_
{
    /* data */
    char topology_name[32];
    glthread_t node_list;
} graph_t;

static inline node_t * get_nbr_node(interface_t *interface) {
    if (!interface) return;
    return interface->att_node;
}

static inline int get_node_intf_available_slot(node_t *node) {
    if (!node) return;
    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (node->intf[i] == -1) {
            return i;
        }
    }
    return -1;
}

graph_t *create_new_graph(char *topology_name);

node_t *create_graph_node(graph_t *graph, char *node_name);

void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost);
