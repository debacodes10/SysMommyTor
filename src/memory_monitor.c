#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_monitor.h"

// Helper function to parse /proc/meminfo 
static int parse_meminfo(unsigned long long *total_mem, unsigned long long *free_mem) {
  FILE *fp = fopen("/proc/meminfo", "r");
  if (!fp) {
    printf("Failed to open /proc/meminfo");
    return -1;
  }

  char buffer[256];
  while (fgets(buffer, sizeof(buffer), fp)) {
    if (strncmp(buffer, "MemTotal:", 9) == 0) {
      sscanf(buffer + 9, "%llu", total_mem);
    } else if (strncmp(buffer, "MemAvailable:", 13) == 0){
      sscanf(buffer + 13, "%llu", free_mem);
    }

    //Stop Parsing once both values are found
    if (*total_mem > 0 && *free_mem > 0) {
      break;
    }
  }

  fclose(fp);
  if (*total_mem == 0 || *free_mem == 0) {
    fprintf(stderr, "Failed to parse memory info from /proc/meminfo\n");
    return -1;
  }

  return 0;
}

float get_memory_usage() {
  unsigned long long total_mem = 0, free_mem = 0;
  if (parse_meminfo(&total_mem, &free_mem) < 0) {
    return -1;
  }
  // Calculate memory usage percentage
  return ((float)(total_mem - free_mem)/total_mem) * 100.0f;
}
