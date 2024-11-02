#include <gtest/gtest.h>
#include "derbit_api.h"
#include "utils.h"

// TEST(Library1Test, Function1)
// {
//   function1();
//   SUCCEED();
// }

// TEST(Library2Test, Function2)
// {
//   function2();
//   SUCCEED();
// }

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}