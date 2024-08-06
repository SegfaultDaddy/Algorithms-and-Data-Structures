#include <iostream>
#include <ranges>
#include <cstdlib>
//#include <gtest/gtest.h>
#include "../source/dynamic_matrix.h"

/*TEST(dynamic_matrix_test, insert)
{
    algo::DynamicMatrix<int> matrix{};
}

TEST(dynamic_matrix_test, indexing)
{
    algo::DynamicMatrix<int> matrix{4};
    try
    {
        matrix.at(4, 0);
        FAIL() << "Error: expected throw.";
    }
    catch(const std::out_of_range& error)
    {
        EXPECT_STREQ("Error: wrong row number", error.what());
    }
    catch(...)
    {
        FAIL() << "Error: expected std::out_of_range exception.";
    }
    try
    {
        matrix.at(0, 4);
        FAIL() << "Error: expected throw.";
    }
    catch(const std::out_of_range& error)
    {
        EXPECT_STREQ("Error: wrong col number.", error.what());
    }
    catch(...)
    {
        FAIL() << "Error: expected std::out_of_range exception.";
    }
    EXPECT_NO_THROW(matrix.at(1, 2));
}*/

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}