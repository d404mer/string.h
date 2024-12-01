#include <check.h>
#include <string.h>

#include "../s21_string.h"

// memcmp - побайтово сравненивает два блока памяти и определяет какой из них
// больше, меньше, равен.
// int s21_memcmp(const void *s1, const void *s2, size_t n)
// тесты
// 1. одинаковые массивы (одинак и оба пустые)
// 2. разные данные (больше, меньше, один пуст, различия в начале или конце)
// 3. n < длинны массивов
// 4. сравнение с длиной 0
// 5. сравнение с null, оба равны null
// 6. сравнение бинарных данных// int main(void) {
//   int number_failed;
//   Suite *suite = s21_memcmp_suite();
//   SRunner *sr = srunner_create(suite);
//   srunner_run_all(sr, CK_NORMAL);
//   number_failed = srunner_ntests_failed(sr);
//   srunner_free(sr);
//   return (number_failed == 0) ? 0 : 1;
// }

/**
 * test 1: test the s21_memcmp function with a basic test where the blocks are
 * equal. it compares the result of s21_memcmp and the standard memcmp function.
 */
START_TEST(test_memcmp_basic_equal) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  int result_s21 = s21_memcmp(str1, str2, 5);
  int result_og = memcmp(str1, str2, 5);
  ck_assert_int_eq(result_s21,
                   result_og);  // should be 0 since both strings are equal
}
END_TEST

// TODO: write descriptions

/*
 * test 2: desc
 */

START_TEST(test_memcmp_empty_equal) {
  char str1[] = "";
  char str2[] = "";
  int result_s21 = s21_memcmp(str1, str2, 1);
  int result_og = memcmp(str1, str2, 1);
  ck_assert_int_eq(result_s21, result_og);
}
END_TEST

START_TEST(test_memcmp_diff_bigger) {
  char str1[] = "test";
  char str2[] = "testest";  // should return that this string is bigger
  int result_s21 = s21_memcmp(str1, str2, 4);
  int result_og = memcmp(str1, str2, 4);
  ck_assert_int_eq(result_s21, result_og);
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcmp_basic_equal);  // Test 1
  tcase_add_test(tc_core, test_memcmp_empty_equal);  // Test 2
  tcase_add_test(tc_core, test_memcmp_diff_bigger);  // Test 3
  suite_add_tcase(suite, tc_core);

  return suite;
}
