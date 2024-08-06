/*
    graph.c
*/

#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

graph_t *create_new_graph(char *topology_name) {
    graph_t *graph = calloc(1, sizeof(graph_t));
    graph->node_list = calloc(1, sizeof(glthread_t));

    strncpy(graph->topology_name, topology_name, 32);
    graph->topology_name[31] = '\0';
    
    init_glthread(graph->node_list, offsetof(node_t, graph_glue));

    printf("Created Graph: %s\n", graph->topology_name);
    return graph;
}

node_t *create_graph_node(graph_t *graph, char *node_name) {
    node_t *node = calloc(1, sizeof(node_t));
    strncpy(node->node_name, node_name, NODE_NAME_SIZE);
    node->node_name[NODE_NAME_SIZE-1] = '\0';
    init_node_nw_prop(&node->node_nw_prop);

    glthread_node_init((&node->graph_glue));

    glthread_add(graph->node_list, &node->graph_glue);
    printf("adding node %s to Graph: %s\n", node->node_name, graph->topology_name);
    return node;
}

void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost) {
    link_t *link = calloc(1, sizeof(link_t));

    /* interface properties */
    strncpy(link->intf1.if_name, from_if_name, IF_NAME_SIZE);
    link->intf1.if_name[IF_NAME_SIZE-1] = '\0';
    strncpy(link->intf2.if_name, to_if_name, IF_NAME_SIZE);
    link->intf2.if_name[IF_NAME_SIZE-1] = '\0';

    /* set back pointers */
    link->intf1.link = link;
    link->intf2.link = link;

    link->intf1.att_node = node1;
    link->intf2.att_node = node2;
    link->cost = cost;

    int empty_intf_slot1 = 0, empty_intf_slot2 = 0;
    empty_intf_slot1 = get_node_intf_available_slot(node1);
    node1->intf[empty_intf_slot1] = &link->intf1;

    empty_intf_slot2 = get_node_intf_available_slot(node2);
    node2->intf[empty_intf_slot2] = &link->intf2;


    // initialize interface network properties
    init_intf_nw_prop(&node1->intf[empty_intf_slot1]->intf_nw_prop);
    init_intf_nw_prop(&node2->intf[empty_intf_slot2]->intf_nw_prop);

    // assign mac address to interfaces
    interface_assign_mac_addr(node1->intf[empty_intf_slot1]);
    interface_assign_mac_addr(node2->intf[empty_intf_slot2]);
}

void print_interface_details(interface_t *interface[]) {
    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (interface[i]) {
            printf(" interface = %s\n", (interface[i])->if_name);
            printf("\tlocal node : %s", (interface[i])->link->intf1.att_node->node_name);
            printf("\tNeighbor   : %s", (interface[i])->link->intf2.att_node->node_name);
            printf("\n");
            printf("\tIP Addr    : %s", (interface[i])->intf_nw_prop.ip_addr.ip);
            printf("\tMAC Addr   : %s", (interface[i])->intf_nw_prop.mac_addr.mac);
            printf("\n");
        }
    }
}

void print_node_details(node_t *node) {
    printf("node = %s\n", node->node_name);
    print_interface_details(node->intf);
}

void dump_graph(graph_t *graph) {
    node_t *ptr = NULL;

    printf("\nNetwork Topology\t%s\n", graph->topology_name);

    // if (!graph->node_list) return;

    ITERATE_GLTHREADS_BEGIN(graph->node_list, node_t, ptr){
        print_node_details(ptr);
        printf("\n");
    } ITERATE_GLTHREADS_ENDS;
}