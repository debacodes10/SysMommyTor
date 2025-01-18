#include <config_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_logging_interval(const char *config_file) {
  FILE *file = fopen(config_file, "r");
  if (file == NULL) {
    perror("Error opening configuration file.");
    return -1;
  }
  
  char line[256];
  int interval = 5; // Default loggin interval
  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "LOG_INTERVAL", 12) == 0) {
      char *equals_sign = strchr(line, '=');
      if (equals_sign) {
        interval = atoi(equals_sign + 1);
        break;
      }
    }
  }
  fclose(file);
  return (interval > 0) ? interval : 5;
}
