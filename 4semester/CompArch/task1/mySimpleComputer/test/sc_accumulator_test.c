#include "test.h"

#include "../../include/mySimpleComputer.h"

#include <check.h>

#define FILE_NAME "save_test_file.bin"

START_TEST (test_sc_accumulatorInit)
{
  sc_accumulatorInit ();
  int value;
  ck_assert_int_eq (sc_accumulatorGet (&value), 0);
  ck_assert_int_eq (value, 0);
}

END_TEST

START_TEST (test_sc_accumulatorSet)
{
  sc_accumulatorSet (50);
  int value;
  ck_assert_int_eq (sc_accumulatorGet (&value), 0);
  ck_assert_int_eq (value, 50);
}

END_TEST

START_TEST (test_sc_accumulatorGet)
{
  sc_accumulatorSet (50);
  int value;
  ck_assert_int_eq (sc_accumulatorGet (&value), 0);
  ck_assert_int_eq (value, 50);
}

Suite *
sc_accumulator_suite ()
{
  Suite *s;
  TCase *tc_core;

  s = suite_create ("sc_accumulator");

  tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_sc_accumulatorInit);
  tcase_add_test (tc_core, test_sc_accumulatorSet);
  tcase_add_test (tc_core, test_sc_accumulatorGet);
  suite_add_tcase (s, tc_core);

  return s;
}
