#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *s21_memchr_suite(void);
Suite *s21_memcmp_suite(void);

int main(void) {
  int number_failed;

  // Создаем SRunner для запуска тестов
  SRunner *sr =
      srunner_create(s21_memcmp_suite());  // Добавляем набор тестов s21_memcmp

  // Добавляем другие тесты в SRunner
  srunner_add_suite(sr,
                    s21_memchr_suite());  // Добавляем набор тестов s21_memchr
  // srunner_add_suite(sr, другой_набор_тестов()); // Добавьте другие тесты,
  // если они есть

  // Запуск всех тестов
  srunner_run_all(
      sr, CK_VERBOSE);  // Используем CK_VERBOSE для детализированного вывода

  // Получаем количество неудачных тестов
  number_failed = srunner_ntests_failed(sr);

  // Освобождаем ресурсы
  srunner_free(sr);

  // Возвращаем 0, если все тесты прошли успешно, иначе 1
  return (number_failed == 0) ? 0 : 1;
}