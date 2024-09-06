#ifndef PARSING_H
#define PARSING_H

#include <stdint.h>

// Function prototypes
int interpolation(uint16_t channel);
uint16_t *parse_buffer(uint8_t buff[]);

// Add prototypes for serial functions
FILE* open_file(const char* portname, const char* mode);
void read_SBUS(uint8_t* buffer, size_t size, size_t n, FILE* file_ptr);
void write_to_SB(FILE* file_ptr, const char* fmt, ...);
void close_file(FILE* file_ptr);

#endif // PARSING_H
