#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t ip;
    uint32_t mask;
} Subnet;

// Calculates the broadcast address for a given host address
uint32_t broadcast_address(uint32_t host, uint32_t mask) {
    return host | ~mask;
}

// Prints the broadcast tree for a given subnet
void print_broadcast_tree(Subnet subnet) {
    uint32_t host_ip = subnet.ip & subnet.mask;
    uint32_t mask_length = 32 - __builtin_clz(subnet.mask);
    uint32_t network_ip = host_ip & ~((1 << (32 - mask_length)) - 1);
    uint32_t broadcast_ip = broadcast_address(host_ip, subnet.mask);

    printf("Subnet: %d.%d.%d.%d/%d\n",
           (network_ip >> 24) & 0xFF,
           (network_ip >> 16) & 0xFF,
           (network_ip >> 8) & 0xFF,
           network_ip & 0xFF,
           mask_length);
    printf("Host IP: %d.%d.%d.%d\n",
           (host_ip >> 24) & 0xFF,
           (host_ip >> 16) & 0xFF,
           (host_ip >> 8) & 0xFF,
           host_ip & 0xFF);
    printf("Broadcast IP: %d.%d.%d.%d\n",
           (broadcast_ip >> 24) & 0xFF,
           (broadcast_ip >> 16) & 0xFF,
           (broadcast_ip >> 8) & 0xFF,
           broadcast_ip & 0xFF);
    printf("Subnet tree:\n");
    for (uint32_t i = 0; i < (1 << mask_length); i++) {
        uint32_t host = host_ip | i;
        uint32_t broadcast = broadcast_address(host, subnet.mask);
        printf("%d.%d.%d.%d - %d.%d.%d.%d\n",
               (host >> 24) & 0xFF,
               (host >> 16) & 0xFF,
               (host >> 8) & 0xFF,
               host & 0xFF,
               (broadcast >> 24) & 0xFF,
               (broadcast >> 16) & 0xFF,
               (broadcast >> 8) & 0xFF,
               broadcast & 0xFF);
    }
}

int main() {
    Subnet subnet = {.ip = 0x0A0B0C0D, .mask = 0xFFFFFFF0};
    print_broadcast_tree(subnet);
    return 0;
}
