/*
    utils.c
*/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Where :

prefix - is a pointer to string representing an IP address.

mask : is any value [0-32]

str_prefix : pointer to a char array of size 16 bytes. This function must fill this array with the output.

This function must apply the mask on prefix and store the result in str_prefix.

For eg : prefix = 122.1.1.1, mask 24, then str_prefix will store 122.1.1.0

*/
void apply_mask(char *prefix, char mask, char *str_prefix) {
    char *token, *endptr;
    int ip_binary[4];

    for (int i = 0; token != NULL; token = strtok(prefix, ".")) {
        ip_binary[i++] = strtol(token, &endptr, 2);
    }
    printf("Binary IP:%d.%d.%d.%d",ip_binary[0],ip_binary[1],ip_binary[2],ip_binary[3]);
}


/*
A broadcast mac address is a 6 byte mac address with all bits set to 1  as below :

FF:FF:FF:FF:FF:FF

Write a below API in utils.c/utils.h which will fill the 6-byte array passed as an argument with MAC broadcast address.
*/

void layer2_fill_with_broadcast_mac(char *mac_array) {
    memset(mac_array, 'F', 17);
    for (int i = 0; i < 17; i++) {
        if (((i+1)%3) == 0) {
            // 2 5 8 11 14
            mac_array[i] = ':';
        }
    }
    mac_array[17] = '\0';
}


void layer2_format_mac(unsigned int value, char *mac_array) {
    memset(mac_array, 'F', 17);
    for (int i = 0; i < 17; i++) {
        if (((i+1)%3) == 0) {
            // 2 5 8 11 14
            mac_array[i] = ':';
        }
    }
    mac_array[17] = '\0';
}