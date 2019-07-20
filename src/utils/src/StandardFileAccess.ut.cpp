#include <gtest/gtest.h>

#include "StandardFileAccess.hpp"

using namespace ::testing;

namespace ocv
{
struct TestInfo
{
    std::string file;
    std::string expectedBody;
};

class StandardFileAccessTest : public TestWithParam<TestInfo>
{
public:
    StandardFileAccess fileAccess;
};

TEST_P(StandardFileAccessTest, readWholeFile)
{
    const auto& testInfo = GetParam();
    ASSERT_NO_THROW(
        ASSERT_EQ(testInfo.expectedBody,
                  fileAccess.read(std::string(__FILE__) + testInfo.file)));
}

INSTANTIATE_TEST_CASE_P(
    StandardFileAccessTest,
    StandardFileAccessTest,
    ::testing::Values(TestInfo{"1.txt",
                               "Something need to be tested\n"
                               "and will be tested.\n"},
                      TestInfo{"2.txt",
                               "Something doesn't need to be tested\n"
                               "but will be tested.\n"}));
}
