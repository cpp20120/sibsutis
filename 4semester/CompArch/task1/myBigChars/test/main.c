#include "test.h"

int
main ()
{
  int number_failed;
  SRunner *sr = srunner_create (myBigChars_suite ());

  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);

  return (number_failed == 0) ? 0 : 1;
}