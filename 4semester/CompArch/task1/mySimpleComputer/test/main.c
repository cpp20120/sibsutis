#include "test.h"

int
main ()
{
  int number_failed;
  SRunner *runner = srunner_create (create_sc_memory_suite ());

  srunner_add_suite (runner, create_sc_command_suite ());
  srunner_add_suite (runner, sc_register_suite ());
  srunner_add_suite (runner, sc_accumulator_suite ());

  srunner_run_all (runner, CK_NORMAL);
  number_failed = srunner_ntests_failed (runner);
  srunner_free (runner);

  return (number_failed == 0) ? 0 : 1;
}
