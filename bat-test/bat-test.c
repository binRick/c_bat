
#include "ansi-codes/ansi-codes.h"
#include "bat-test/bat-test.h"
#include "bytes/bytes.h"
#include "c_fsio/include/fsio.h"
#include "c_greatest/greatest/greatest.h"
#include "c_string_buffer/include/stringbuffer.h"
#include "c_stringfn/include/stringfn.h"
#include "c_vector/vector/vector.h"
#include "log/log.h"
#include "ms/ms.h"
#include "timestamp/timestamp.h"

TEST t_bat_test2(){
  PASS();
}

TEST t_bat_test1(){
  PASS();
}

SUITE(s_bat_test) {
  RUN_TEST(t_bat_test1);
  if (isatty(STDOUT_FILENO))
    RUN_TEST(t_bat_test2);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(s_bat_test);
  GREATEST_MAIN_END();
}
