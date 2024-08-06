/*
    net.c
*/

#include "graph/graph.h"
#include "utils/utils.h"
#include <assert.h>
#include <stdio.h>
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
    unsigned int hash_val = 1;
    char *str = (char*) ptr;

    for (int i = 0; i < size; i++, str++) {
        hash_val += *str;
        hash_val *= 97;
    }

    return hash_val;
}

static void format_into_mac_addr(char* mac, unsigned int hash_val) {
    unsigned int mac_val[7];
    memset(mac_val, 0, 6);

    memset(mac, 0, 17);
    for (int i = 0; i < 6; i++) {
        mac_val[i] = (hash_val*((i*8)+1) % 256);
        printf("%x\t",mac_val[i]);
    } 
    printf("\n");

    char buffer[18];
    memset(buffer, 0, 17);

    for (int i = 0, k = 0; i < 11; i++) {
        if (((i+1)%2) != 0) {
            // 0 2 4 6 8 10
            char hex[3];
            sprintf(hex,"%02x", mac_val[k]);
            strcat(buffer, hex);
            k++;
        } else {
            strcat(buffer, ":");
        }    
    }

    memcpy(mac, buffer, sizeof(buffer));
}

void interface_assign_mac_addr(interface_t *interface) {
    node_t *node = interface->att_node;

    if (!node) return;
    printf("%s %s\n", node->node_name, interface->if_name);

    unsigned int hash_val = 0;
    hash_val = hash_code(node->node_name, NODE_NAME_SIZE);
    hash_val *= hash_code(interface->if_name, IF_NAME_SIZE);

    // printf("%u %s\n", hash_val, (char *)&hash_val);

    format_into_mac_addr(INTF_MAC(interface), hash_val);
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