#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <Arduino.h>
#include <stdarg.h> // For va_list and related operations

// Function to print formatted strings
inline void printFormatted(const char *prefix, const char *format,
                           va_list args) {
  char temp[128];
  char *buffer = temp;
  size_t length = vsnprintf(temp, sizeof(temp), format, args);
  if (length >= sizeof(temp)) {
    // Temporary buffer not large enough, allocate on heap
    buffer = new char[length + 1];
    vsnprintf(buffer, length + 1, format, args);
  }
  Serial.print(prefix);
  Serial.println(buffer);
  if (buffer != temp) {
    delete[] buffer; // Free dynamically allocated buffer
  }
}

// Modified functions for floats
inline void print_info(const char *format, ...) {
  va_list args;
  va_start(args, format);
  printFormatted("[INFO] - ", format, args);
  va_end(args);
}

inline void print_warn(const char *format, ...) {
  va_list args;
  va_start(args, format);
  printFormatted("[WARN] - ", format, args);
  va_end(args);
}

inline void print_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  printFormatted("[ERROR] - ", format, args);
  va_end(args);
}

#endif // !LOGGER_HPP
