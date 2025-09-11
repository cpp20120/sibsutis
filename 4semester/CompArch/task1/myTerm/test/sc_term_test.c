#include "test.h"

#include "../../include/term.h"

#include <stdio.h>

START_TEST (test_mt_clrscr)
{
  printf ("Testing mt_clrscr: Clearing the screen...\n");
  ck_assert_int_eq (mt_clrscr (), 0);
  printf ("Screen should be cleared now.\n");
}
END_TEST

START_TEST (test_mt_gotoXY)
{
  printf ("Testing mt_gotoXY: Moving cursor to (10, 10)...\n");
  ck_assert_int_eq (mt_gotoXY (10, 10), 0);
  printf ("Cursor should be at (10, 10).\n");
}
END_TEST

START_TEST (test_mt_setfgcolor)
{
  printf ("Testing mt_setfgcolor: Setting foreground color to RED...\n");
  ck_assert_int_eq (mt_setfgcolor (RED), 0);
  printf ("This text should be RED.\n");
  ck_assert_int_eq (mt_setfgcolor (GREEN), 0);
  printf ("This text should be GREEN.\n");
  ck_assert_int_eq (mt_setfgcolor (BLUE), 0);
  printf ("This text should be BLUE.\n");
  ck_assert_int_eq (mt_setfgcolor (YELLOW), 0);
  printf ("This text should be YELLOW.\n");
  ck_assert_int_eq (mt_setfgcolor (MAGENTA), 0);
  printf ("This text should be MAGENTA.\n");
  ck_assert_int_eq (mt_setfgcolor (CYAN), 0);
  printf ("This text should be CYAN.\n");
  ck_assert_int_eq (mt_setfgcolor (WHITE), 0);
  printf ("This text should be WHITE.\n");
  ck_assert_int_eq (mt_setfgcolor (BLACK), 0);
  printf ("This text should be BLACK.\n");
  ck_assert_int_eq (mt_setfgcolor (DEFAULT), 0);
  printf ("Foreground color reset to default.\n");
}
END_TEST

START_TEST (test_mt_setbgcolor)
{
  printf ("Testing mt_setbgcolor:\n");

  printf ("Setting background to BLUE...\n");
  ck_assert_int_eq (mt_setbgcolor (BLUE), 0);
  printf ("This text should have a BLUE background.\n");

  ck_assert_int_eq (mt_setdefaultcolor (), 0);
  printf ("Default background applied.\n");

  printf ("Setting background to GREEN...\n");
  ck_assert_int_eq (mt_setbgcolor (GREEN), 0);
  printf ("This text should have a GREEN background.\n");

  ck_assert_int_eq (mt_setdefaultcolor (), 0);
  printf ("Setting background to BLUE for empty string...\n");
  ck_assert_int_eq (mt_setbgcolor (BLUE), 0);
  printf ("                                         \n");
  ck_assert_int_eq (mt_setdefaultcolor (), 0);
  printf ("Final text with default background.\n");
}
END_TEST

START_TEST (test_mt_setdefaultcolor)
{
  printf ("Testing mt_setdefaultcolor: Resetting colors to default...\n");
  ck_assert_int_eq (mt_setdefaultcolor (), 0);
  printf ("Colors should be reset to default.\n");
}
END_TEST

START_TEST (test_mt_setallbgcolor)
{
  printf ("Testing mt_setbgcolor with various colors...\n");

  for (int i = 0; i < 8; i++)
    {
      printf ("Setting background color to %d...\n", i);
      ck_assert_int_eq (mt_setbgcolor (i), 0);
      printf ("Background color %d set. \033[0m\n", i);
    }

  ck_assert_int_eq (mt_setbgcolor (DEFAULT), 0);
  printf ("Background color reset to default. \033[0m\n");
}
END_TEST

START_TEST (test_mt_setcursorvisible)
{
  printf ("Testing mt_setcursorvisible: Hiding cursor...\n");
  ck_assert_int_eq (mt_setcursorvisible (0), 0);
  printf ("Cursor should be hidden now.\n");

  printf ("Testing mt_setcursorvisible: Showing cursor...\n");
  ck_assert_int_eq (mt_setcursorvisible (1), 0);
  printf ("Cursor should be visible now.\n");
}
END_TEST

START_TEST (test_mt_delline)
{
  printf ("Testing mt_delline: Clearing the current line...\n");
  ck_assert_int_eq (mt_delline (), 0);
  printf ("The current line should be cleared.\n");
}
END_TEST

Suite *
myTerm_suite ()
{
  Suite *s;
  TCase *tc_core;

  s = suite_create ("myTerm");

  tc_core = tcase_create ("Core");

  tcase_add_test (tc_core, test_mt_clrscr);
  tcase_add_test (tc_core, test_mt_gotoXY);
  tcase_add_test (tc_core, test_mt_setfgcolor);
  tcase_add_test (tc_core, test_mt_setbgcolor);
  tcase_add_test (tc_core, test_mt_setdefaultcolor);

  tcase_add_test (tc_core, test_mt_setallbgcolor);
  tcase_set_timeout (tc_core, 40);

  tcase_add_test (tc_core, test_mt_setcursorvisible);
  tcase_add_test (tc_core, test_mt_delline);

  suite_add_tcase (s, tc_core);

  return s;
}
