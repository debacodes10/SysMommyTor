#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cpu_monitor.h"

// Helper function to read /proc/stat 
static int read_proc_stat(unsigned long long *idle, unsigned long long *total) {
  FILE *fp = fopen("/proc/stat", "r");
  if (!fp) {
    perror("Failed to open /proc/stat");
    return -1;
  }

  char buffer[256];
  if (fgets(buffer, sizeof(buffer), fp) == NULL) {
    perror("Failed to read /proc/stat");
    fclose(fp);
    return -1;
  }

  fclose(fp);

  unsigned long long user, nice, system, idle_time, iowait, irq, softirq, steal;
  if (sscanf(buffer, "cpu %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle_time, &iowait, &irq, &softirq, &steal) != 8) {
    fprintf(stderr, "Failed to parse /proc/date\n");
    return -1;
  }
  *idle = idle_time + iowait;
  *total = user + nice + system + idle_time + iowait + irq + softirq + steal;
  return 0;
}

float get_cpu_usage() {
  unsigned long long idle1, total1, idle2, total2;
  if (read_proc_stat(&idle1, &total1) < 0) {
    return -1;
  }
  usleep(100000);
  if (read_proc_stat(&idle2, &total2) < 0){
    return -1;
  }
  unsigned long long idle_diff = idle2 - idle1;
  unsigned long long total_diff = total2 - total1;

  if (total_diff == 0) {
    return 0.0f;
  }
  return ((float)(total_diff - idle_diff) / total_diff) * 100.0f;
}
