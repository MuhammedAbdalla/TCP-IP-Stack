/* 
    test_utils.c
*/

#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    // if (argc != 3) return -1;
    char *prefix = "122.1.1.1";
    char mask = 24;
    char str_prefix[18];

    layer2_fill_with_broadcast_mac(str_prefix);
    printf("BROADCAST: %s\n", str_prefix);
    printf("is broadcast mac? %s\n", IS_MAC_BROADCAST_ADDR(str_prefix) == 0 ? "YES": "NO");

    // apply_mask(prefix, mask, str_prefix);
}