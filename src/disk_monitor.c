#include <stdio.h>
#include <sys/statvfs.h>
#include "disk_monitor.h"

float get_disk_usage(const char *path) {
  struct statvfs stat;

  if (statvfs(path, &stat) != 0) {
    perror("Failed to get filesystem statistics");
    return -1.0f;
  }

  unsigned long long total_space = stat.f_blocks * stat.f_frsize;
  unsigned long long free_space = stat.f_bfree * stat.f_frsize;
  unsigned long long used_space = total_space - free_space;

  return ((float)used_space/total_space) * 100.0f;
}
