#include "string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
  char *ret = dest;
  while (*dest) dest++;
  while (n--) *dest++ = *src++;
  return ret;
}