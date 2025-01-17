#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

FILE *init_log(const char *file_name);

void log_metrics(FILE *log_file, double cpu_usage, double mem_usage, double disk_usage, unsigned long long rx_bytes, unsigned long long tx_bytes);

void close_log(FILE *log_file);

#endif
