#include "test.h"

#include "../../include/myBigChars.h"

START_TEST (test_bc_strlen)
{
  char *str = "Привет, Мир!\nHello, World!";
  int len = bc_strlen (str);
  ck_assert_int_eq (len, 26);
}
END_TEST

START_TEST (test_bc_printA)
{
  char *str = "Привет, Мир!\nHello, World!";
  bc_printA (str);
}
END_TEST

START_TEST (test_bc_box)
{
  bc_box (1, 1, 10, 10, RED, WHITE, "Привет", RED, BLACK);
}
END_TEST

Suite *
myBigChars_suite ()
{
  Suite *s = suite_create ("myBigChars");
  TCase *tc_core = tcase_create ("Core");

  tcase_add_test (tc_core, test_bc_strlen);
  tcase_add_test (tc_core, test_bc_printA);
  tcase_add_test (tc_core, test_bc_box);

  suite_add_tcase (s, tc_core);

  return s;
}
