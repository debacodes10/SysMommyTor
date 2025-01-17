#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

int get_network_usage(const char *interface, unsigned long long *rx_bytes, unsigned long long *tx_bytes);

#endif
