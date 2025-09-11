#include "test.h"

#include "../../include/mySimpleComputer.h"

#define FILE_NAME "save_test_reg_file.bin"

START_TEST (test_sc_regInit)
{
  sc_regInit ();
  int value;
  ck_assert_int_eq (sc_regGet (FLAG_OVERFLOW, &value), 0);
  ck_assert_int_eq (value, 0);
  ck_assert_int_eq (sc_regGet (FLAG_DIVISION, &value), 0);
  ck_assert_int_eq (value, 0);
}
END_TEST

START_TEST (test_sc_regSet)
{
  ck_assert_int_eq (sc_regSet (FLAG_OVERFLOW, 1), 0);
  int value;
  ck_assert_int_eq (sc_regGet (FLAG_OVERFLOW, &value), 0);
  ck_assert_int_eq (value, 1);

  ck_assert_int_eq (sc_regSet (FLAG_OVERFLOW, 0), 0);
  ck_assert_int_eq (sc_regGet (FLAG_OVERFLOW, &value), 0);
  ck_assert_int_eq (value, 0);

  ck_assert_int_eq (sc_regSet (0x100, 1), -1);
}
END_TEST

START_TEST (test_sc_regGet)
{
  int value;

  ck_assert_int_eq (sc_regGet (FLAG_MEMORY, &value), 0);
  ck_assert_int_eq (value, 0);

  sc_regSet (FLAG_MEMORY, 1);
  ck_assert_int_eq (sc_regGet (FLAG_MEMORY, &value), 0);
  ck_assert_int_eq (value, 1);

  ck_assert_int_eq (sc_regGet (0x100, &value), -1);
}
END_TEST

START_TEST (test_sc_icounterInit)
{
  sc_icounterInit ();
  int value;
  ck_assert_int_eq (sc_icounterGet (&value), 0);
  ck_assert_int_eq (value, 0);
}
END_TEST

START_TEST (test_sc_icounterSet)
{
  sc_icounterSet (100);
  int value;
  ck_assert_int_eq (sc_icounterGet (&value), 0);
  ck_assert_int_eq (value, 100);
}
END_TEST

START_TEST (test_sc_icounterGet)
{
  int value;

  sc_icounterSet (50);
  ck_assert_int_eq (sc_icounterGet (&value), 0);
  ck_assert_int_eq (value, 50);

  sc_icounterSet (200);
  ck_assert_int_eq (sc_icounterGet (&value), 0);
  ck_assert_int_eq (value, 200);
}
END_TEST

Suite *
sc_register_suite ()
{
  Suite *s;
  TCase *tc_core;

  s = suite_create ("sc_register");

  tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_sc_regInit);
  tcase_add_test (tc_core, test_sc_regSet);
  tcase_add_test (tc_core, test_sc_regGet);
  tcase_add_test (tc_core, test_sc_icounterInit);
  tcase_add_test (tc_core, test_sc_icounterSet);
  tcase_add_test (tc_core, test_sc_icounterGet);
  suite_add_tcase (s, tc_core);

  return s;
}
