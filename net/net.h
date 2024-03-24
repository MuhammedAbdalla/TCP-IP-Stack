/*
    net.h
*/

#ifndef __NET__
#define __NET__

// GET macros
#define INTF_MAC(intf_ptr) ((intf_ptr)->intf_nw_prop.mac_addr.mac)
#define INTF_IP(intf_ptr) ((intf_ptr)->intf_nw_prop.ip_addr.ip)

#define NODE_LO_ADDR(node_ptr) ((node_ptr)->node_nw_prop.lb_addr.ip)
#define IS_INTF_L3_MODE(intf_ptr) ((intf_ptr)->intf_nw_prop.is_ipaddr_config)

//forward declaration
typedef struct ip_addr_ ip_addr_t;
typedef struct mac_addr_ mac_addr_t;
typedef struct node_nw_prop_ node_nw_prop_t;
typedef struct intf_nw_prop_ intf_nw_prop_t;

struct ip_addr_ {
    char ip[16];
};

struct mac_addr_ {
    char mac[48];
};

struct node_nw_prop_ {
    // L3 properties
    int is_lb_addr_config;
    ip_addr_t lb_addr; /* loopback addr */
};

struct intf_nw_prop_ {
    // L2 properties
    mac_addr_t mac_addr;

    // L3 properties
    int is_ipaddr_config;
    ip_addr_t ip_addr;
    char mask;
};

#include "graph/graph.h"
#include <memory.h>

static inline void init_node_nw_prop(node_nw_prop_t *node_nw_prop) {
    node_nw_prop->is_lb_addr_config = 0;
    memset(node_nw_prop->lb_addr.ip, 0, 16);
}

static inline void init_intf_nw_prop(intf_nw_prop_t *intf_nw_prop) {
    intf_nw_prop->is_ipaddr_config = 0;
    memset(intf_nw_prop->mac_addr.mac, 0, 48);
    memset(intf_nw_prop->ip_addr.ip, 0, 16);
    intf_nw_prop->mask = 0;
}


// API to set network node properties
int node_set_lb_addr(node_t *node, char *ip_addr);

int node_set_intf_ip_addr(node_t *node, char *local_intf, char *ip_addr, char mask);

int node_unset_intf_ip_addr(node_t *node, char *local_intf);

void interface_assign_mac_addr(interface_t *interface);

#endif