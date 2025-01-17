#include "logger.h"

FILE *init_log(const char *file_name) {
  FILE *file = fopen(file_name, "a");
  if (file == NULL) {
    perror("Error opening log file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    fprintf(file, "Timestamp, CPU Usage (%%), Memory Usage (%%), Disk Usage (%%), RX(bytes), TX(bytes)\n");
  }
  return file;
}

void log_metrics(FILE *log_file, double cpu_usage, double mem_usage, double disk_usage, unsigned long long rx_bytes, unsigned long long tx_bytes) {
  if (log_file == NULL) return;

  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

  fprintf(log_file, "%s, %.2f, %.2f, %.2f, %llu, %llu\n", timestamp, cpu_usage, mem_usage, disk_usage, rx_bytes, tx_bytes);
  fflush(log_file);
}

void close_log(FILE *log_file) {
  if (log_file != NULL) {
    fclose(log_file);
  }
}
