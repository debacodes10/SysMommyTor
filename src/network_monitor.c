#include <stdio.h>
#include <string.h>
#include "network_monitor.h"

static int parse_net_dev(const char *interface, unsigned long long *rx_bytes, unsigned long long *tx_bytes) {
  FILE *fp = fopen("/proc/net/dev", "r");
  if (!fp) {
    perror("Failed to open /proc/net/dev");
    return -1;
  }

  char buffer[512];
  int found = 0;

  if (!fgets(buffer, sizeof(buffer), fp)) {
    perror("Failed to read /proc/net/dev (header 1)");
    fclose(fp);
    return -1;
  }

  if (!fgets(buffer, sizeof(buffer), fp)) {
    perror("Failed to read /proc/net/dev (header 2)");
    fclose(fp);
    return -1;
  }

  while (fgets(buffer, sizeof(buffer), fp)) {
    char iface[32];
    unsigned long long rx, tx;

    sscanf(buffer, "%31s %llu 0 0 0 0 0 0 0 %llu", iface, &rx, &tx);
    char *colon = strchr(iface, ':');
    if (colon) *colon = '\0';
    if (strcmp(iface, interface) == 0) {
      *rx_bytes = rx;
      *tx_bytes = tx;
      found = 1;
      break;
    }
  }

  fclose(fp);

  if (!found) {
    fprintf(stderr, "Interface '%s' not found in /proc/net/dev\n", interface);
    return -1;
  }

  return 0;
}

int get_network_usage(const char *interface, unsigned long long *rx_bytes, unsigned long long *tx_bytes) {
  return parse_net_dev(interface, rx_bytes, tx_bytes);
}

