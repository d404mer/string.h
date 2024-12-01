#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

extern Suite *s21_memchr_suite(void);
extern Suite *s21_memcmp_suite(void);

int main(void) {
  int number_failed;

  Suite *sr_memchr;
  SRunner *sr;

  // TODO: fix output???
  sr = srunner_create(s21_memchr_suite());
  sr_memchr = s21_memchr_suite();
  srunner_add_suite(sr, sr_memchr);

  srunner_add_suite(sr, s21_memcmp_suite());

  srunner_run_all(sr, CK_NORMAL);

  // Check if any tests failed
  number_failed = srunner_ntests_failed(sr);

  // Free resources
  srunner_free(sr);

  // Return 0 if all tests passed, 1 if some tests failed
  return (number_failed == 0) ? 0 : 1;
}
