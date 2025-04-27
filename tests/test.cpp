#include <gtest/gtest.h>

TEST(ExampleTest, BasicAssertions) {
    EXPECT_EQ(1 + 1, 2);
}

int
main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}