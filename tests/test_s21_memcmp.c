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

//                                TEST 2
START_TEST(test_memcmp_empty_equal) {
  char str1[] = "";
  char str2[] = "";
  int result_s21 = s21_memcmp(str1, str2, 1);
  int result_og = memcmp(str1, str2, 1);
  ck_assert_int_eq(result_s21, result_og);  // strings are empty -> neg
  // ck_asser_int_lt(result_s21, 0);
}
END_TEST

//                                TEST 3
START_TEST(test_memcmp_basic_not_equal) {
  char str1[] = "Hello";
  char str2[] = "sdasd";
  int result_s21 = s21_memcmp(str1, str2, 5);
  int result_og = memcmp(str1, str2, 5);
  ck_assert((result_og < 0) && (result_s21 < 0));
}

//                                TEST 4
START_TEST(test_memcmp_basic_empty_string) {
  char str1[] = "aa";
  char str2[] = "";
  int result_s21 = s21_memcmp(str1, str2, 2);
  int result_og = memcmp(str1, str2, 2);
  ck_assert((result_og > 0) && (result_s21 > 0));
}

//                                TEST 5
START_TEST(test_memcmp_zero_n) {
  char str1[] = "ddd";
  char str2[] = "ddd";
  int result_s21 = s21_memcmp(str1, str2, 0);
  int result_og = memcmp(str1, str2, 0);
  ck_assert_int_eq(result_s21, result_og);
}

//                                TEST 6
START_TEST(test_memcmp_diff_bigger) {
  char str1[] = "test";
  char str2[] = "testest";  // should return that this string is bigger
  int result_s21 = s21_memcmp(str1, str2, 4);
  int result_og = memcmp(str1, str2, 4);
  ck_assert_int_eq(result_s21, result_og);
}
END_TEST

//                                TEST 7
START_TEST(test_memcmp_beginning) {
  char str1[] = "PPPIII";
  char str2[] = "PPPII";
  int result_s21 = s21_memcmp(str1, str2, 5);
  int result_og = memcmp(str1, str2, 5);
  ck_assert_int_eq(result_s21, result_og);
}
END_TEST

//                                TEST 8 (testing bigger inputs)
START_TEST(test_memcmp_big_block_of_memory) {
  char str1[69];
  char str2[69];
  memset(str1, 'P', 68);
  str1[68] = '\0';
  memset(str2, 'P', 68);
  str2[68] = '\0';
  int result_s21 = s21_memcmp(str1, str2, 69);
  int result_og = memcmp(str1, str2, 69);
  ck_assert_int_eq(result_s21, result_og);
}
END_TEST
//                                TEST 9
START_TEST(test_memcmp_binary) {
  int str1[] = {1, 2, 3};
  int str2[] = {1, 2, 3};
  int result_s21 = s21_memcmp(str1, str2, sizeof(str1));
  int result_og = memcmp(str1, str2, sizeof(str1));
  ck_assert_int_eq(result_s21, result_og);  //  arrs are equal -> 0
}
END_TEST

//                                TEST 10
START_TEST(test_memcmp_bigger_n) {
  char str1[] = "hi";
  char str2[] = "hi";
  int result_s21 = s21_memcmp(str1, str2, 10);
  int result_og = memcmp(str1, str2, 10);
  ck_assert_int_eq(result_s21, result_og);
  // if ((result_og > 0 && result_s21 > 0) || (result_og < 0 && result_s21 < 0))
  // {
  //   ck_abort_msg("expected_og: %d,actual_s21 = %d", result_og, result_s21);
  // }
  // ck_assert((result_og > 0 && result_s21 > 0) ||
  //           (result_og < 0 && result_s21 < 0));
}
END_TEST

Suite *s21_memcmp_suite(void) {
  Suite *suite = suite_create("s21_memcmp");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_memcmp_basic_equal);          // Test 1
  tcase_add_test(tc_core, test_memcmp_empty_equal);          // Test 2
  tcase_add_test(tc_core, test_memcmp_basic_not_equal);      // Test 3
  tcase_add_test(tc_core, test_memcmp_basic_empty_string);   // Test 4
  tcase_add_test(tc_core, test_memcmp_zero_n);               // test 5
  tcase_add_test(tc_core, test_memcmp_diff_bigger);          // Test 6
  tcase_add_test(tc_core, test_memcmp_beginning);            // Test 7
  tcase_add_test(tc_core, test_memcmp_big_block_of_memory);  // Test 8
  tcase_add_test(tc_core, test_memcmp_binary);               // Test 9
  tcase_add_test(tc_core, test_memcmp_bigger_n);             // Test10

  suite_add_tcase(suite, tc_core);
  return suite;
}
