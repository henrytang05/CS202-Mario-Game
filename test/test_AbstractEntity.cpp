#include <gtest/gtest.h>

// Function to test
int add(int a, int b) { return a + b; }

// Test case
TEST(AdditionTest, HandlesPositiveNumbers) { EXPECT_EQ(add(1, 2), 3); }

TEST(AdditionTest, HandlesNegativeNumbers) { EXPECT_EQ(add(-1, -2), -3); }

TEST(AdditionTest, HandlesMixedNumbers) { EXPECT_EQ(add(-1, 2), 1); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
