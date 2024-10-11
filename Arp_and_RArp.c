#include <stdio.h>
#include <string.h>

struct ARPEntry {
    char ip[20];
    char mac[20];
};

void displayTable(struct ARPEntry table[], int size) {
    printf("\nIP Address\tMAC Address\n");
    printf("-----------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%s\t%s\n", table[i].ip, table[i].mac);
    }
}

void simulateARP(struct ARPEntry table[], int size, char ip[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(ip, table[i].ip) == 0) {
            printf("\nARP Response: MAC Address for IP %s is %s\n", ip, table[i].mac);
            return;
        }
    }
    printf("\nARP Response: No MAC Address found for IP %s\n", ip);
}

void simulateRARP(struct ARPEntry table[], int size, char mac[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(mac, table[i].mac) == 0) {
            printf("\nRARP Response: IP Address for MAC %s is %s\n", mac, table[i].ip);
            return;
        }
    }
    printf("\nRARP Response: No IP Address found for MAC %s\n", mac);
}

int main() {
    struct ARPEntry table[5] = {
        {"192.168.0.1", "00:0a:95:9d:68:16"},
        {"192.168.0.2", "00:0a:95:9d:68:17"},
        {"192.168.0.3", "00:0a:95:9d:68:18"},
        {"192.168.0.4", "00:0a:95:9d:68:19"},
        {"192.168.0.5", "00:0a:95:9d:68:20"}
    };

    char choice;
    char ip[20], mac[20];
    
    displayTable(table, 5);

    printf("\nChoose Simulation:\n1. ARP\n2. RARP\n");
    scanf(" %c", &choice);
    
    switch (choice) {
        case '1':
            printf("\nEnter IP address to simulate ARP: ");
            scanf("%s", ip);
            simulateARP(table, 5, ip);
            break;
        case '2':
            printf("\nEnter MAC address to simulate RARP: ");
            scanf("%s", mac);
            simulateRARP(table, 5, mac);
            break;
        default:
            printf("\nInvalid Choice\n");
    }

    return 0;
}
