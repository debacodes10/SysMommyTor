#include <stdio.h>
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "disk_monitor.h"
#include "network_monitor.h"
#include "logger.h"
#include <unistd.h>
#include "config_parser.h"

int main() {
  
  int log_interval = get_logging_interval("config.ini");
  if (log_interval <= 0) {
    fprintf(stderr, "Invalid or missing logging interval. Using default of 5 seconds.\n");
    log_interval = 5;
  }

  FILE *log_file = init_log("system_metrics.csv");
  if (log_file == NULL) {
    return 1;
  }

  while (1) {
    // Fetch metrics 
    double cpu_usage = get_cpu_usage();
    double mem_usage = get_memory_usage();
    double disk_usage= get_disk_usage("/");
    unsigned long long rx_bytes, tx_bytes;
    get_network_usage("wlp1s0", &rx_bytes, &tx_bytes);

    log_metrics(log_file, cpu_usage, mem_usage, disk_usage, rx_bytes, tx_bytes);
    sleep(log_interval);
  }

  close_log(log_file);

  return 0;
}
