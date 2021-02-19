#ifndef FDVAR_STRINGVALUE_TEST_H
#define FDVAR_STRINGVALUE_TEST_H

#include <FDVar/StringValue.h>
#include <gtest/gtest.h>
#include <iostream>

static const FDVar::StringValue::StringType TEST_STRING_VALUE("text");

TEST(StringValue_test, test_constructors)
{
    ASSERT_EQ(FDVar::StringValue(), FDVar::StringValue::StringType());
    ASSERT_EQ(FDVar::StringValue(TEST_STRING_VALUE), TEST_STRING_VALUE);
    FDVar::StringValue value;
    value = TEST_STRING_VALUE;
    ASSERT_EQ(value, TEST_STRING_VALUE);
}

TEST(StringValue_test, test_comparison_operators)
{
    ASSERT_TRUE(FDVar::StringValue(TEST_STRING_VALUE) == TEST_STRING_VALUE);
    ASSERT_TRUE(TEST_STRING_VALUE == FDVar::StringValue(TEST_STRING_VALUE));
    ASSERT_TRUE(FDVar::StringValue(TEST_STRING_VALUE) != FDVar::StringValue::StringType());
}

TEST(StringValue_test, test_concat_operators)
{
    FDVar::StringValue::StringType test;
    FDVar::StringValue value;
    ASSERT_EQ(value += TEST_STRING_VALUE, test += TEST_STRING_VALUE);
    ASSERT_EQ(value + TEST_STRING_VALUE, test + TEST_STRING_VALUE);
}

TEST(StringValue_test, test_stream_operators)
{
    FDVar::StringValue::StringType test = TEST_STRING_VALUE;
    FDVar::StringValue value;
    std::stringstream ss;
    ss << test;
    ss >> value;
    ASSERT_EQ(value, test);
    ss.clear();
    value = "result";
    ss << value;
    ss >> test;
    ASSERT_EQ(value, test);
}

TEST(StringValue_test, test_member_functions)
{
    FDVar::StringValue::StringType test = TEST_STRING_VALUE;
    FDVar::StringValue value;
    ASSERT_TRUE(value.isEmpty());
    ASSERT_FALSE(FDVar::StringValue(TEST_STRING_VALUE).isEmpty());
    ASSERT_EQ(FDVar::StringValue(TEST_STRING_VALUE).size(), test.size());
    value = TEST_STRING_VALUE;
    ASSERT_FALSE(value.isEmpty());
    value.clear();
    ASSERT_TRUE(value.isEmpty());
    value = test;
    ASSERT_EQ(value[0], test[0]);
    value.append(" string");
    test.append(" string");
    ASSERT_EQ(value, test);
    ASSERT_EQ(value.subString(0, 4), test.substr(0, 4));
}


#endif // FDVAR_STRINGVALUE_TEST_H
