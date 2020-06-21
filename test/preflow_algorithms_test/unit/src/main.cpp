#include <gtest/gtest.h>

// Initialize GTest
int main(int ac, char* av[]) {
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
