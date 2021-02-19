#ifndef FDVAR_BOOLVALUE_TEST_H
#define FDVAR_BOOLVALUE_TEST_H

#include <FDVar/BoolValue.h>
#include <gtest/gtest.h>
#include <sstream>

TEST(BoolValue_test, test_constructors)
{
    ASSERT_FALSE(static_cast<bool>(FDVar::BoolValue()));
    ASSERT_TRUE(static_cast<bool>(FDVar::BoolValue(true)));

    FDVar::BoolValue b;
    b = true;
    ASSERT_TRUE(static_cast<bool>(b));
}

TEST(BoolValue_test, test_operators)
{
    FDVar::BoolValue b;
    FDVar::BoolValue other(true);
    b = true;
    ASSERT_FALSE(!b);

    ASSERT_TRUE(b == true);
    ASSERT_TRUE(b == other);

    ASSERT_TRUE(b != false);
    ASSERT_TRUE(b != !other);

    ASSERT_FALSE(b && false);
    ASSERT_TRUE(b && other);

    ASSERT_TRUE(b || false);
    ASSERT_TRUE(b || other);

    ASSERT_TRUE(b ^ false);
    ASSERT_FALSE(b ^ other);
}

TEST(BoolValue_test, test_stream_operators)
{
    FDVar::BoolValue b;
    bool tmp = true;
    std::stringstream ss;
    ss << tmp;
    ss >> b;
    ASSERT_TRUE(b);
    tmp = false;
    ss.clear();
    ss << b;
    ss >> tmp;
    ASSERT_TRUE(tmp);
}

#endif // FDVAR_BOOLVALUE_TEST_H
