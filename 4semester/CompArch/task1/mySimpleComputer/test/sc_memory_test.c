#include "test.h"

#include "../../include/mySimpleComputer.h"

#include <stdlib.h>

#define FILE_NAME "save_test_file.bin"

START_TEST (memory_test)
{
  sc_memoryInit ();

  int value = 3, value_ = 0;
  sc_memorySet (0, value);
  sc_memoryGet (0, &value_);
  ck_assert_int_eq (value, value_);

  for (int i = 0; i < MEMORY_SIZE; ++i)
    sc_memorySet (i, i);

  sc_memorySave (FILE_NAME);

  sc_memoryInit ();
  for (int i = 0; i < MEMORY_SIZE; ++i)
    {
      sc_memoryGet (i, &value);
      ck_assert_int_eq (value, 0);
    }

  sc_memoryLoad (FILE_NAME);
  for (int i = 0; i < MEMORY_SIZE; ++i)
    {
      sc_memoryGet (i, &value);
      ck_assert_int_eq (value, i);
    }

  char cmd[255] = "rm -rf ";
  system (strcat (cmd, FILE_NAME));
}
END_TEST

Suite *
create_sc_memory_suite ()
{
  Suite *suite = suite_create ("SC_Memory suite");
  TCase *test_case = tcase_create ("SC_Memory test case");

  tcase_add_test (test_case, memory_test);

  suite_add_tcase (suite, test_case);
  return suite;
}
