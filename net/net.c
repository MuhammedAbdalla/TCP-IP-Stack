/*
    net.c
*/

#include "graph/graph.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// API to set network node properties
int node_set_lb_addr(node_t *node, char *ip_addr) {
    assert(ip_addr);

    node->node_nw_prop.is_lb_addr_config = 1;
    strncpy(NODE_LO_ADDR(node), ip_addr, 16);
    NODE_LO_ADDR(node)[15] = '\0';

    return 1;
}


int node_set_intf_ip_addr(node_t *node, char *local_intf, char *ip_addr, char mask) {
    interface_t *intf = get_node_if_by_name(node, local_intf);
    if (!intf) assert(0);

    strncpy(INTF_IP(intf), ip_addr, 16);
    INTF_IP(intf)[15] = '\0';
    intf->intf_nw_prop.mask = mask;
    intf->intf_nw_prop.is_ipaddr_config = 1;
    
    return 1;
}


int node_unset_intf_ip_addr(node_t *node, char *local_intf) {
    interface_t *intf = get_node_if_by_name(node, local_intf);
    
    if (!intf) assert(0);
    memset(INTF_IP(intf), 0, sizeof(INTF_MAC(intf)));

    return 1;
}

// Mac addr = fn(node, interface, some heristics)
// random num generator
static unsigned int hash_code(void *ptr, unsigned int size) {
    unsigned int value = 0, i = 0;
    char *str = (char*)ptr;

    while (i < size) {
        value += *str;
        value *= 97;
        str++;
        i++;
    }
    return value;
}
void interface_assign_mac_addr(interface_t *interface) {
    node_t *node = interface->att_node;

    if (!node) return;

    unsigned int hash_val = 0;
    hash_val = hash_code(node->node_name, NODE_NAME_SIZE);
    hash_val *= hash_code(interface->if_name, IF_NAME_SIZE);
    memset(INTF_MAC(interface), 0, sizeof(INTF_MAC(interface)));
    memcpy(INTF_MAC(interface), (char *)&hash_val, sizeof(unsigned int));
}

void dump_nw_graph(graph_t *graph) {
    /* for further implementation, exists in graph.c dump_graph()*/
}

interface_t *node_get_matching_subnet_interface(node_t *node, char *ip_addr) {
    // making subnet, search for an interface with the same attachment node
    
    return NULL;
}

/*
Write a function in net.h/net.c which converts an ip address in string form (A.B.C.D format) into its equivalent 32-bit integer form.
*/
unsigned int convert_ip_from_str_to_int(char *ip_addr) {
    return -1;
}


/*
Write a function in net.h/net.c which converts an ip address in integer form into its equivalent dot decimal form (A.B.C.D format)

Output should be stored in the array output_buffer of size 16 bytes passed as second argument.
*/
void convert_ip_from_int_to_str(unsigned int ip_addr, char *output_buffer) {

}