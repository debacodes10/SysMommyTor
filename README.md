# **SysMommyTor**

## **Overview**

`SysMommyTor` is a lightweight, modular tool designed for monitoring system performance metrics such as:

- **CPU Usage**
- **Memory Usage**
- **Disk Usage**
- **Network Activity**

This tool logs the data periodically into a `.csv` file, enabling users to analyze historical system performance trends. The project is written entirely in C and built from scratch, adhering to best practices in modular programming.

---

## **Features**

- **Real-Time Monitoring**: Fetches and displays CPU, memory, disk, and network statistics.
- **Historical Logging**: Periodically logs metrics into a `.csv` file for later analysis.
- **Configurable Logging Interval**: Allows users to set the logging frequency via a simple `config.ini` file.
- **Portable and Lightweight**: Designed for Linux systems with minimal dependencies.

---

## **Getting Started**

### **Prerequisites**

- A Linux-based operating system.
- GCC (GNU Compiler Collection).

### **Installation**

1. Clone the repository:
   ```bash
   git clone https://github.com/debacodes10/SysMommyTor.git
   cd SysMommyTor
   ```
2. Build the project using the included `Makefile`:
   ```bash
   make
   ```

### **Usage**

1. **Run the application**:

   ```bash
   ./build/system_monitor
   ```

2. **Edit Configuration**:

   - Modify the logging interval in the `config.ini` file:
     ```ini
     LOG_INTERVAL=10
     ```
   - The default interval is 5 seconds.

3. **View Logs**:

   - Open `system_metrics.csv` to view the logged metrics.

---

## **File Structure**

```plaintext
.
├── build/                  # Directory for the compiled binary
├── include/                # Header files for all modules
│   ├── cpu_monitor.h
│   ├── memory_monitor.h
│   ├── disk_monitor.h
│   ├── network_monitor.h
│   ├── logger.h
│   ├── config_parser.h
├── src/                    # Source files for all modules
│   ├── main.c
│   ├── cpu_monitor.c
│   ├── memory_monitor.c
│   ├── disk_monitor.c
│   ├── network_monitor.c
│   ├── logger.c
│   ├── config_parser.c
├── config.ini              # Configuration file for logging interval
├── system_metrics.csv      # Log file for historical data (generated at runtime)
├── Makefile                # Build instructions
└── README.md               # Documentation
```

---

## **Modules**

1. **CPU Monitor (`cpu_monitor.c`)**

   - Fetches CPU utilization percentage using `/proc/stat`.

2. **Memory Monitor (`memory_monitor.c`)**

   - Retrieves memory usage percentage using `/proc/meminfo`.

3. **Disk Monitor (`disk_monitor.c`)**

   - Calculates disk usage statistics using `statvfs`.

4. **Network Monitor (`network_monitor.c`)**

   - Tracks bytes received and transmitted using `/proc/net/dev`.

5. **Logger (`logger.c`)**

   - Logs system metrics into a `.csv` file with timestamps.

6. **Config Parser (`config_parser.c`)**

   - Parses `config.ini` for user-defined settings.

---

## **Future Enhancements**

- Add support for **threshold-based alerts** via desktop notifications.
- Implement **visualization tools** for logged metrics using Python or JavaScript.
- Extend support for **Windows and macOS** platforms.
- Add **unit tests** for each module to ensure robustness.

---

## **Contributing**

Contributions are welcome! Please open an issue or submit a pull request for bug fixes or feature suggestions.

---

## **License**

This project is licensed under the [MIT License](LICENSE).
