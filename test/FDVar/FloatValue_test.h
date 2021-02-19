#ifndef FDVAR_FLOATVALUE_TEST_H
#define FDVAR_FLOATVALUE_TEST_H

#include <FDVar/FloatValue.h>
#include <gtest/gtest.h>
#include <iostream>

static constexpr FDVar::FloatValue::FloatType TEST_FLOAT_VALUE = 3.1415;

TEST(FloatValue_test, test_constructors)
{
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue()), 0.0f);
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(TEST_FLOAT_VALUE)), TEST_FLOAT_VALUE);
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(2.0F)), 2.0F);

    FDVar::FloatValue value;
    value = TEST_FLOAT_VALUE;
    ASSERT_FLOAT_EQ(static_cast<float>(value), TEST_FLOAT_VALUE);
    ASSERT_NE(value, 2.0F);
}

TEST(FloatValue_test, test_comparison_operators)
{
    ASSERT_TRUE(FDVar::FloatValue() == 0);
    ASSERT_TRUE(FDVar::FloatValue(TEST_FLOAT_VALUE) == TEST_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::FloatValue(TEST_FLOAT_VALUE) <= TEST_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::FloatValue(TEST_FLOAT_VALUE) < 2.0F * TEST_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::FloatValue(TEST_FLOAT_VALUE) >= TEST_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::FloatValue(TEST_FLOAT_VALUE) > 0);
}

TEST(FloatValue_test, test_plus_operators)
{
    float test = 1;
    FDVar::FloatValue value(1.0F);
    ASSERT_FLOAT_EQ(static_cast<float>(value += 0), test += 0);
    ASSERT_FLOAT_EQ(static_cast<float>(value + 0.0), test + 0.0);
    ASSERT_FLOAT_EQ(static_cast<float>(value += 1), test += 1);
    ASSERT_FLOAT_EQ(static_cast<float>(value += value), test += test);
    ASSERT_FLOAT_EQ(static_cast<float>(value + value), test + test);

    ASSERT_FLOAT_EQ(static_cast<float>(value + test), test + value);
    ASSERT_FLOAT_EQ(static_cast<float>(value += test), 8u);
    ASSERT_FLOAT_EQ(test += value, 12.0);

    value = test = -1.0F;
    ASSERT_FLOAT_EQ(static_cast<float>(+value), +test);
}

TEST(FloatValue_test, test_minus_operators)
{
    float test = 4.0F;
    FDVar::FloatValue value(4);
    ASSERT_FLOAT_EQ(static_cast<float>(value -= 0), test -= 0);
    ASSERT_FLOAT_EQ(static_cast<float>(value - 0), test - 0);
    ASSERT_FLOAT_EQ(static_cast<float>(value -= 1), test -= 1);
    ASSERT_FLOAT_EQ(static_cast<float>(value -= value), test -= test);

    value = test = 2;
    ASSERT_FLOAT_EQ(static_cast<float>(value - value), test - test);
    ASSERT_FLOAT_EQ(static_cast<float>(value - test), test - value);
    ASSERT_FLOAT_EQ(static_cast<float>(value -= test), 0.0F);
    value = 4LU;
    ASSERT_FLOAT_EQ(test -= value, -2.0F);

    value = test = -1;
    ASSERT_FLOAT_EQ(static_cast<float>(-value), -test);
    value = test = 0;
    ASSERT_FLOAT_EQ(static_cast<float>(-value), 0);
}

TEST(FloatValue_test, test_multiplication_operators)
{
    float test = 1;
    FDVar::FloatValue value(1);
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(value) *= 0), 0);
    ASSERT_FLOAT_EQ(static_cast<float>(value * 0), 0);
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(value) *= 1), static_cast<float>(value));
    ASSERT_FLOAT_EQ(static_cast<float>(value * 1), static_cast<float>(value));
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(value) *= -1), static_cast<float>(-value));
    ASSERT_FLOAT_EQ(static_cast<float>(value *= 2), test *= 2);
    ASSERT_FLOAT_EQ(static_cast<float>(value * 2), test * 2);
    ASSERT_FLOAT_EQ(static_cast<float>(value *= value), test *= test);
    ASSERT_FLOAT_EQ(static_cast<float>(value * value), test * test);
}

TEST(FloatValue_test, test_division_operators)
{
    float test = TEST_FLOAT_VALUE;
    FDVar::FloatValue value(TEST_FLOAT_VALUE);
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(value) /= 1), static_cast<float>(value));
    ASSERT_FLOAT_EQ(static_cast<float>(value / 1), static_cast<float>(value));
    ASSERT_FLOAT_EQ(static_cast<float>(FDVar::FloatValue(value) /= -1), static_cast<float>(-value));
    ASSERT_FLOAT_EQ(static_cast<float>(value /= 2), test /= 2);
    ASSERT_FLOAT_EQ(static_cast<float>(value / 2), test / 2);
    ASSERT_FLOAT_EQ(static_cast<float>(value / value), test / test);
    ASSERT_FLOAT_EQ(static_cast<float>(100 / value), 100 / test);
    value = 2;
    test = 4;
    ASSERT_FLOAT_EQ(test /= value, 2);
}

TEST(FloatValue_test, test_stream_operators)
{
    float test = TEST_FLOAT_VALUE;
    FDVar::FloatValue value;
    std::stringstream ss;
    ss << test;
    ss >> value;
    ASSERT_FLOAT_EQ(static_cast<float>(value), test);
    ss.clear();
    value = 0;
    ss << value;
    ss >> test;
    ASSERT_FLOAT_EQ(static_cast<float>(value), test);
}

#endif // FDVAR_FLOATVALUE_TEST_H
