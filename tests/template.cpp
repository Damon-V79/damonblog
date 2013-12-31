/*
 * template.cpp
 *
 *  Created on: 24.04.2013
 *      Author: damon
 */

/*
 *
 *

Утверждения (assertion)

Утверждения, порождающие в случае их ложности критические отказы начинаются с
ASSERT_, некритические — EXPECT_. Следует иметь ввиду, что в случае критического
отказа выполняется немедленный возврат из функции, в которой встретилось вызвавшее
отказ утверждение. Если за этим утверждением идет какой-то очищающий память код
или какие-то другие завершающие процедуры, можете получить утечку памяти.

Имеются следующие утверждения (некритические начинаются не с ASSERT_, а с EXPECT_):

Простейшие логические

ASSERT_TRUE(condition);
ASSERT_FALSE(condition);


Сравнение

ASSERT_EQ(expected, actual); — =
ASSERT_NE(val1, val2); — !=
ASSERT_LT(val1, val2); — <
ASSERT_LE(val1, val2); — <=
ASSERT_GT(val1, val2); — >
ASSERT_GE(val1, val2); — >=


Сравнение строк

ASSERT_STREQ(expected_str, actual_str);
ASSERT_STRNE(str1, str2);
ASSERT_STRCASEEQ(expected_str, actual_str); — регистронезависимо
ASSERT_STRCASENE(str1, str2); — регистронезависимо


Проверка на исключения

ASSERT_THROW(statement, exception_type);
ASSERT_ANY_THROW(statement);
ASSERT_NO_THROW(statement);


Проверка предикатов

ASSERT_PREDN(pred, val1, val2, ..., valN); — N <= 5
ASSERT_PRED_FORMATN(pred_format, val1, val2, ..., valN); — работает аналогично
предыдущей, но позволяет контролировать вывод


Сравнение чисел с плавающей точкой

ASSERT_FLOAT_EQ(expected, actual); — неточное сравнение float
ASSERT_DOUBLE_EQ(expected, actual); — неточное сравнение double
ASSERT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает погрешность abs_error


Вызов отказа или успеха

SUCCEED();
FAIL();
ADD_FAILURE();
ADD_FAILURE_AT(«file_path», line_number);
 *
 *
 *
 *
Флаги


Вызванная перед RUN_ALL_TESTS() функция InitGoogleTest(argc, argv) делает вашу
тестовую программу не просто исполняемым файлом, выводящим на экран результаты
тестирования. Это целостное приложение, принимающие на вход параметры, меняющие
его поведение. Как обычно ключи -h, --help дадут вам список всех поддерживаемых
параметров. Перечислю некоторые из них (за полным списком можно обратиться к документации).

./test --gtest_filter=TestCaseName.*-TestCaseName.SomeTest — запустить все тесты
набора TestCaseName за исключением SomeTest

./test --gtest_repeat=1000 --gtest_break_on_failure — запустить тестирующую программу
1000 раз и остановиться при первой неудаче

./test --gtest_output=«xml:out.xml» — помимо выдачи в std::out будет создан out.xml —
XML отчет с результатами выполнения тестовой программы

./test --gtest_shuffle — запускать тесты в случайном порядке

Если вы используете какие-то параметры постоянно, можете задать соответствующую
переменную окружения и запускать исполняемый файл без параметров. Например задание
переменной GTEST_ALSO_RUN_DISABLED_TESTS ненулевого значения эквивалентно использованию
флага --gtest_also_run_disabled_tests.


 *
 *
 */


#include "gtest/gtest.h"

int test_add(int value1, int value2) {
  return (value1 + value2);
}

TEST (Template, Test1) {
  EXPECT_EQ (16, test_add(8, 8));
}

TEST (Template, Test2) {
  EXPECT_EQ (16, test_add(8, 8));
}
