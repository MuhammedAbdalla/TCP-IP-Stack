/*
    utils.h
*/

#ifndef __UTILS__
#define __UTILS__

#include <string.h>

#define IS_MAC_BROADCAST_ADDR(mac) (strcmp(mac, "FF:FF:FF:FF:FF:FF"))

void apply_mask(char *prefix, char mask, char *str_prefix);

void layer2_fill_with_broadcast_mac(char *mac_array);

#endif