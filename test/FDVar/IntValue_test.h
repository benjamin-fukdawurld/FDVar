#ifndef FDVAR_INTVALUE_TEST_H
#define FDVAR_INTVALUE_TEST_H

#include <FDVar/IntValue.h>
#include <gtest/gtest.h>
#include <iostream>

static constexpr FDVar::IntValue::IntType TEST_INT_VALUE = 10;

TEST(IntValue_test, test_constructors)
{
    ASSERT_EQ(FDVar::IntValue(), 0);
    ASSERT_EQ(FDVar::IntValue(TEST_INT_VALUE), TEST_INT_VALUE);
    ASSERT_EQ(FDVar::IntValue(2U), 2U);

    FDVar::IntValue value;
    value = TEST_INT_VALUE;
    ASSERT_EQ(value, TEST_INT_VALUE);
    ASSERT_NE(value, 2);
}

TEST(IntValue_test, test_comparison_operators)
{
    ASSERT_TRUE(FDVar::IntValue() == 0);
    ASSERT_TRUE(FDVar::IntValue(TEST_INT_VALUE) == TEST_INT_VALUE);
    ASSERT_TRUE(FDVar::IntValue(TEST_INT_VALUE) <= TEST_INT_VALUE);
    ASSERT_TRUE(FDVar::IntValue(TEST_INT_VALUE) < 2 * TEST_INT_VALUE);
    ASSERT_TRUE(FDVar::IntValue(TEST_INT_VALUE) >= TEST_INT_VALUE);
    ASSERT_TRUE(FDVar::IntValue(TEST_INT_VALUE) > 0);
}

TEST(IntValue_test, test_plus_operators)
{
    int test = 1;
    FDVar::IntValue value(1);
    ASSERT_EQ(value += 0, test += 0);
    ASSERT_EQ(value + 0, test + 0);
    ASSERT_EQ(value += 1, test += 1);
    ASSERT_EQ(value += value, test += test);
    ASSERT_EQ(value + value, test + test);

    ASSERT_EQ(value + test, test + value);
    ASSERT_EQ(value += test, 8);
    ASSERT_EQ(test += value, 12);

    value = test = -1;
    ASSERT_EQ(+value, +test);
    value = test = 0;
    ASSERT_EQ(value++, test++);
    ASSERT_EQ(++value, ++test);
}

TEST(IntValue_test, test_minus_operators)
{
    int test = 4;
    FDVar::IntValue value(4);
    ASSERT_EQ(value -= 0, test -= 0);
    ASSERT_EQ(value - 0, test - 0);
    ASSERT_EQ(value -= 1, test -= 1);
    ASSERT_EQ(value -= value, test -= test);

    value = test = 2;
    ASSERT_EQ(value - value, test - test);
    ASSERT_EQ(value - test, test - value);
    ASSERT_EQ(value -= test, 0);
    value = 4LU;
    ASSERT_EQ(test -= value, -2);

    value = test = -1;
    ASSERT_EQ(-value, -test);
    value = test = 0;
    ASSERT_EQ(-value, 0);
    ASSERT_EQ(value--, test--);
    ASSERT_EQ(value--, test--);
}

TEST(IntValue_test, test_multiplication_operators)
{
    int test = 1;
    FDVar::IntValue value(1);
    ASSERT_EQ(FDVar::IntValue(value) *= 0, 0);
    ASSERT_EQ(value * 0, 0);
    ASSERT_EQ(FDVar::IntValue(value) *= 1, value);
    ASSERT_EQ(value * 1, value);
    ASSERT_EQ(FDVar::IntValue(value) *= -1, -value);
    ASSERT_EQ(value *= 2, test *= 2);
    ASSERT_EQ(value * 2, test * 2);
    ASSERT_EQ(value *= value, test *= test);
    ASSERT_EQ(value * value, test * test);
}

TEST(IntValue_test, test_division_operators)
{
    int test = TEST_INT_VALUE;
    FDVar::IntValue value(TEST_INT_VALUE);
    ASSERT_EQ(FDVar::IntValue(value) /= 1, value);
    ASSERT_EQ(value / 1, value);
    ASSERT_EQ(FDVar::IntValue(value) /= -1, -value);
    ASSERT_EQ(value /= 2, test /= 2);
    ASSERT_EQ(value / 2, test / 2);
    ASSERT_EQ(value / value, test / test);
    ASSERT_EQ(100 / value, 100 / test);
    value = 2;
    test = 4;
    ASSERT_EQ(test /= value, 2);
}

TEST(IntValue_test, test_modulo_operators)
{
    int test = TEST_INT_VALUE;
    FDVar::IntValue value(3);
    ASSERT_EQ(FDVar::IntValue(test) % value, 1);
    ASSERT_EQ(FDVar::IntValue(test) %= value, 1);
    ASSERT_EQ(test % value, 1);
    ASSERT_EQ(test %= value, 1);
}


TEST(IntValue_test, test_byte_operators)
{
    int test = 0;
    FDVar::IntValue value(0);
    ASSERT_EQ(~value, ~test);
    ASSERT_EQ(value | 1, test | 1);
    ASSERT_EQ(value |= 1, test |= 1);
    ASSERT_EQ(value << 1, test << 1);
    ASSERT_EQ(value <<= 2, test <<= 2);
    ASSERT_EQ(value >> 1, test >> 1);
    ASSERT_EQ(value >>= 2, test >>= 2);

    value = test = ~0;
    ASSERT_EQ(value & 0x8, test & 0x8);
    ASSERT_EQ(value &= 0x8, test &= 0x8);
    value = 1;
    ASSERT_EQ(test & value, 0x8 & 1);
    ASSERT_EQ(test | value, 0x8 | 1);
    ASSERT_EQ(test |= value, 0x8 | 1);
    ASSERT_EQ(test &= value, 0x9 & 1);


    value = test = 0b11011;
    ASSERT_EQ(value ^ 2, test ^ 2);
    ASSERT_EQ(value ^= 2, test ^= 2);
    ASSERT_EQ(0xFF ^ value, 0xFF ^ test);
}

TEST(IntValue_test, test_stream_operators)
{
    int test = TEST_INT_VALUE;
    FDVar::IntValue value;
    std::stringstream ss;
    ss << test;
    ss >> value;
    ASSERT_EQ(value, test);
    ss.clear();
    value = 0;
    ss << value;
    ss >> test;
    ASSERT_EQ(value, test);
}

#endif // FDVAR_INTVALUE_TEST_H
