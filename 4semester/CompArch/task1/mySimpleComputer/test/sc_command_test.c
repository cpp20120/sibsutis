#include "test.h"

#include "../../include/mySimpleComputer.h"

START_TEST (encode_test)
{
  int value = 0;
  int sign = 1;
  int command = 30; // ADD
  int operand = 9;

  int err = sc_commandEncode (sign, command, operand, &value);

  ck_assert_int_eq (err, 0);
  ck_assert_int_eq (value, 0b100111100001001);
}
END_TEST

START_TEST (decode_test)
{
  int value = 0b100111100001001;
  int sign = 0;
  int command = 0;
  int operand = 0;

  int err = sc_commandDecode (value, &sign, &command, &operand);

  ck_assert_int_eq (err, 0);
  ck_assert_int_eq (sign, 1);
  ck_assert_int_eq (command, 30);
  ck_assert_int_eq (operand, 9);
}
END_TEST

START_TEST (validate_test_0)
{
  int command = 30;

  ck_assert_int_eq (sc_commandValidate (command), 0);
}
END_TEST

START_TEST (validate_test_1)
{
  int command = 156;

  ck_assert_int_eq (sc_commandValidate (command), -1);
}
END_TEST

Suite *
create_sc_command_suite ()
{
  Suite *suite = suite_create ("SC_Command suite");
  TCase *test_case = tcase_create ("SC_Command test case");

  tcase_add_test (test_case, encode_test);
  tcase_add_test (test_case, decode_test);
  tcase_add_test (test_case, validate_test_0);
  tcase_add_test (test_case, validate_test_1);

  suite_add_tcase (suite, test_case);
  return suite;
}
