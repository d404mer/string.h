#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *s21_memchr_suite(void);
Suite *s21_memcmp_suite(void);

int main(void) {
  int number_failed;

  SRunner *sr = srunner_create(s21_memcmp_suite());

  srunner_add_suite(sr, s21_memchr_suite());

  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}