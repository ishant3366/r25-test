#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>

// Function to open the serial port
FILE* open_file(const char* portname, const char* mode) {
    FILE* file_ptr = fopen(portname, mode);
    if (file_ptr == NULL) {
        printf("Error opening %s : %d\n", portname, errno);
        return NULL;
    }
    return file_ptr;
}

// Function to read data from SBUS
void read_SBUS(uint8_t* buffer, size_t size, size_t n, FILE* file_ptr) {
    size_t rc = fread(buffer, size, n, file_ptr);
    if (rc != n) {
        printf("Error reading file : %d\n", errno);
    }
}

// Function to write data to Sabertooth
void write_to_SB(FILE* file_ptr, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int rc = vfprintf(file_ptr, fmt, args);
    va_end(args);
    if (rc < 0) {
        printf("Error writing to file : %d\n", errno);
    }
}

// Function to close the serial port
void close_file(FILE* file_ptr) {
    fclose(file_ptr);
}

