#include <gtest/gtest.h>
#include <cstdlib>
#include "../source/dynamic_matrix.h"

TEST(dynamic_matrix_test, insert)
{
    algo::DynamicMatrix<int> matrix{};
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}