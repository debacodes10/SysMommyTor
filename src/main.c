#include <stdio.h>
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "disk_monitor.h"
#include "network_monitor.h"

int main() {

  printf("System Monitor Starting...\n");

  // Initialize CPU monitoring
  float cpu_usage = get_cpu_usage();
  if (cpu_usage >= 0) {
    printf("CPU Usage: %.2f%%\n", cpu_usage);
  } else {
    printf("Failed to retrieve CPU usage. \n");
  }

  float memory_usage = get_memory_usage();
  if (memory_usage >= 0) {
    printf("Memory Usage: %.2f%%\n", memory_usage);
  } else {
    printf("Failed to retrieve Memory Usage.\n");
  }

  float disk_usage = get_disk_usage("/");
  if (disk_usage >= 0) {
    printf("Disk Usage on '/': %.2f%%\n", disk_usage);
  } else {
    printf("Failed to retrieve Disk Usage.\n");
  }

  unsigned long long rx_bytes, tx_bytes;
  if (get_network_usage("wlp1s0", &rx_bytes, &tx_bytes) == 0) {
    printf("Network Usage (wslp1s0):\n");
    printf("  Received: %llu bytes.\n", rx_bytes/1024);
    printf("  Transmitted: %llu bytes.\n", tx_bytes/1024);
  } else {
    printf("Failed to retrieve network usage for interface 'wlp1s0'.\n");
  }

  return 0;
}
