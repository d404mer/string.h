#include "s21_string.h"

int s21_memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  int ret = 0;
  while (n-- && !ret)
    if (*p1 < *p2)
      ret = -1;
    else if (*p1 > *p2)
      ret = 1;
  return ret;
}

/*
  potential logical error:
  test_memcmp_bigger_n:0: Assertion 'result_s21 == result_og' failed:
  result_s21
  == 0, result_og == 138

*/
