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
// 6. сравнение бинарных данных

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

/**
 * test 2: test the s21_memcmp function where the blocks are not equal.
 * it compares the result of s21_memcmp and the standard memcmp function.
 */
START_TEST(test_memcmp_basic_not_equal) {
  char str1[] = "Hello";
  char str2[] = "World";
  int result_s21 = s21_memcmp(str1, str2, 5);
  int result_og = memcmp(str1, str2, 5);
  ck_assert_int_eq(
      result_s21,
      result_og);  // should not be 0 since the strings are different
}
END_TEST

/**
 * test 3: test the s21_memcmp function with an empty string.
 * this ensures the function correctly compares an empty string to another
 * string.
 */
START_TEST(test_memcmp_empty_string) {
  char str1[] = "";
  char str2[] = "Hello";
  int result_s21 = s21_memcmp(str1, str2, 5);
  int result_og = memcmp(str1, str2, 5);
  ck_assert_int_eq(
      result_s21,
      result_og);  // should return negative value since str1 is empty
}
END_TEST

/**
 * test 4: test the s21_memcmp function with n = 0 (no comparison).
 * the function should return 0 since no bytes are compared.
 */
START_TEST(test_memcmp_zero_length) {
  char str1[] = "Test";
  char str2[] = "Test";
  int result_s21 = s21_memcmp(str1, str2, 0);
  int result_og = memcmp(str1, str2, 0);
  ck_assert_int_eq(result_s21,
                   result_og);  // should return 0 as no bytes are compared
}
END_TEST

/**
 * test 5: test the s21_memcmp function where one block is a prefix of the
 * other. this checks that the function compares the entire length.
 */
START_TEST(test_memcmp_prefix) {
  char str1[] = "Hello";
  char str2[] = "Hell";
  int result_s21 = s21_memcmp(str1, str2, 4);
  int result_og = memcmp(str1, str2, 4);
  ck_assert_int_eq(
      result_s21,
      result_og);  // should return 0 as the first 4 characters are equal
}
END_TEST

/**
 * test 6: test the s21_memcmp function where the comparison is made over a
 * larger block. this ensures the function compares all bytes.
 */
START_TEST(test_memcmp_large_string) {
  char str1[1000];
  char str2[1000];
  memset(str1, 'A', 999);
  str1[999] = '\0';
  memset(str2, 'A', 999);
  str2[999] = '\0';
  int result_s21 = s21_memcmp(str1, str2, 1000);
  int result_og = memcmp(str1, str2, 1000);
  ck_assert_int_eq(result_s21,
                   result_og);  // should return 0 as both strings are equal
}
END_TEST

/**
 * test 7: test the s21_memcmp function with a large string where blocks are
 * different. this ensures the function works correctly with large inputs.
 */
START_TEST(test_memcmp_large_string_diff) {
  char str1[1000];
  char str2[1000];
  memset(str1, 'A', 999);
  str1[999] = '\0';
  memset(str2, 'B', 999);
  str2[999] = '\0';
  int result_s21 = s21_memcmp(str1, str2, 1000);
  int result_og = memcmp(str1, str2, 1000);
  ck_assert_int_eq(
      result_s21,
      result_og);  // should return negative value as strings are different
}
END_TEST

/**
 * test 8: test the s21_memcmp function with different data types (e.g.,
 * integers). this ensures the function can handle arbitrary binary data.
 */
START_TEST(test_memcmp_binary_data) {
  int arr1[] = {1, 2, 3, 4};
  int arr2[] = {1, 2, 3, 4};
  int result_s21 = s21_memcmp(arr1, arr2, sizeof(arr1));
  int result_og = memcmp(arr1, arr2, sizeof(arr2));
  ck_assert_int_eq(result_s21,
                   result_og);  // should return 0 as both arrays are equal
}
END_TEST

/**
 * test 9: test the s21_memcmp function with n greater than the size of the
 * string. this ensures that the function does not go out of bounds and handles
 * large n gracefully.
 */
START_TEST(test_memcmp_large_n) {
  char str1[] = "Hello";
  char str2[] = "Hello";
  int result_s21 = s21_memcmp(str1, str2, 1000);
  int result_og = memcmp(str1, str2, 1000);
  ck_assert_int_eq(result_s21, result_og);  // should return 0 as comparison
                                            // stops at the end of the string
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tc_core = tcase_create("Core");

  // adding all tests to the test case group
  tcase_add_test(tc_core, test_memcmp_basic_equal);        // Test 1
  tcase_add_test(tc_core, test_memcmp_basic_not_equal);    // Test 2
  tcase_add_test(tc_core, test_memcmp_empty_string);       // Test 3
  tcase_add_test(tc_core, test_memcmp_zero_length);        // Test 4
  tcase_add_test(tc_core, test_memcmp_prefix);             // Test 5
  tcase_add_test(tc_core, test_memcmp_large_string);       // Test 6
  tcase_add_test(tc_core, test_memcmp_large_string_diff);  // Test 7
  tcase_add_test(tc_core, test_memcmp_binary_data);        // Test 8
  tcase_add_test(tc_core, test_memcmp_large_n);            // Test 9

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main(void) {
  int number_failed;
  Suite *suite = s21_memcmp_suite();
  SRunner *sr = srunner_create(suite);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
