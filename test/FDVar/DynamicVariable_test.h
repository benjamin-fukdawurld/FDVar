#ifndef FDVAR_DYNAMICVARIABLE_TEST_H
#define FDVAR_DYNAMICVARIABLE_TEST_H

#include <iostream>
#include <sstream>

#include "ArrayValue_test.h"
#include "BoolValue_test.h"
#include "FloatValue_test.h"
#include "FunctionValue_test.h"
#include "IntValue_test.h"
#include "ObjectValue_test.h"
#include "StringValue_test.h"

#include <FDVar/DynamicVariable.h>

static constexpr FDVar::DynamicVariable::IntType TEST_DYN_INT_VALUE = 10;
static constexpr FDVar::DynamicVariable::FloatType TEST_DYN_FLOAT_VALUE = 3.14159F;
static const FDVar::DynamicVariable::StringType TEST_DYN_STRING_VALUE("text");
static const FDVar::ArrayValue::ArrayType TEST_DYN_ARRAY_VALUE = {
    FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)),
    FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)),
    FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)),
    FDVar::AbstractValue::Ptr(new FDVar::StringValue("text"))
};
static FDVar::ObjectValue::ObjectType TEST_DYN_OBJECT_VALUE = {
    { "i", FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)) },
    { "b", FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)) },
    { "f", FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)) },
    { "s", FDVar::AbstractValue::Ptr(new FDVar::StringValue("text")) }
};

TEST(DynamicVariable_test, test_constructors)
{
    using namespace FDVar;

    ASSERT_EQ(FDVar::DynamicVariable().getValueType(), FDVar::ValueType::None);

    ASSERT_EQ(FDVar::DynamicVariable(true), true);
    ASSERT_EQ(FDVar::DynamicVariable(false), false);

    ASSERT_EQ(FDVar::DynamicVariable(TEST_DYN_INT_VALUE), TEST_DYN_INT_VALUE);
    ASSERT_EQ(FDVar::DynamicVariable(2U), 2U);

    ASSERT_FLOAT_EQ(
      static_cast<FDVar::DynamicVariable::FloatType>(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE)),
      TEST_DYN_FLOAT_VALUE);
    ASSERT_FLOAT_EQ(static_cast<FDVar::DynamicVariable::FloatType>(FDVar::DynamicVariable(1.61803)),
                    1.61803);

    ASSERT_EQ(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE), TEST_DYN_STRING_VALUE);
    ASSERT_EQ(FDVar::DynamicVariable("test"), DynamicVariable::StringViewType("test"));

    {
        FDVar::DynamicVariable value(TEST_DYN_ARRAY_VALUE);
        for(FDVar::DynamicVariable::SizeType i = 0, imax = value.size(); i != imax; ++i)
        {
            ASSERT_EQ(value[i], TEST_DYN_ARRAY_VALUE[i]);
        }
    }

    {
        FDVar::DynamicVariable value { 0_var, 1_var, 2_var, 3_var, 4_var, 5_var };
        for(FDVar::DynamicVariable::SizeType i = 0, imax = value.size(); i != imax; ++i)
        {
            ASSERT_EQ(value[i], i);
        }
    }

    /*{
        FDVar::DynamicVariable value(
          std::vector<DynamicVariable> { 0_var, 1_var, 2_var, 3_var, 4_var, 5_var });
        for(FDVar::DynamicVariable::SizeType i = 0, imax = value.size(); i != imax; ++i)
        {
            ASSERT_EQ(value[i], i);
        }
    }*/

    {
        FDVar::DynamicVariable value { { "i", 0_var }, { "j", 1_var }, { "k", 2_var } };
        ASSERT_EQ(value["i"], 0);
        ASSERT_EQ(value["j"], 1);
        ASSERT_EQ(value["k"], 2);
    }

    {
        FDVar::DynamicVariable value(TEST_DYN_OBJECT_VALUE);
        ASSERT_EQ(value["i"], 42);
    }

    {
        ASSERT_TRUE(!FDVar::DynamicVariable(FDVar::ValueType::Function));

        ASSERT_FALSE(
          !FDVar::DynamicVariable([](FDVar::DynamicVariable) { return FDVar::DynamicVariable(); }));

        FDVar::DynamicVariable value(FDVar::ValueType::Function);
        value = [](const FDVar::DynamicVariable & /*unused*/) { return FDVar::DynamicVariable(); };
        ASSERT_FALSE(!value);
    }

    {
        FDVar::DynamicVariable value;
        value = TEST_DYN_INT_VALUE;
        ASSERT_EQ(value, TEST_DYN_INT_VALUE);
        ASSERT_NE(value, 2);
        value = TEST_DYN_FLOAT_VALUE;
        ASSERT_EQ(value, TEST_DYN_FLOAT_VALUE);
        ASSERT_NE(value, 2.0F);
        value = TEST_DYN_STRING_VALUE;
        ASSERT_EQ(value, TEST_DYN_STRING_VALUE);
        ASSERT_NE(value, "not the same string");
    }

    ASSERT_EQ(-42_var, -42);
    ASSERT_FLOAT_EQ(static_cast<FDVar::DynamicVariable::FloatType>(1.61803_var), 1.61803);
    ASSERT_EQ("test"_var, FDVar::DynamicVariable::StringType("test"));
}

TEST(DynamicVariable_test, test_comparison_operators)
{
    ASSERT_TRUE(FDVar::DynamicVariable() == nullptr);
    ASSERT_TRUE(FDVar::DynamicVariable() == FDVar::DynamicVariable());

    ASSERT_TRUE(FDVar::DynamicVariable(true) == true);
    ASSERT_TRUE(FDVar::DynamicVariable(true) == FDVar::DynamicVariable(true));
    ASSERT_TRUE(FDVar::DynamicVariable(true) != false);
    ASSERT_TRUE(FDVar::DynamicVariable(true) != FDVar::DynamicVariable(false));

    ASSERT_TRUE(FDVar::DynamicVariable(0) == 0);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) ==
                FDVar::DynamicVariable(TEST_DYN_INT_VALUE));
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) == TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) != -TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) <= TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) < 2 * TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) >= TEST_DYN_INT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_INT_VALUE) > 0);

    ASSERT_TRUE(FDVar::DynamicVariable(0.0F) == 0.0F);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) ==
                FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE));
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) == TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) != -TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) <= TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) < 2.0F * TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) >= TEST_DYN_FLOAT_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_FLOAT_VALUE) > 0.0F);

    ASSERT_TRUE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) ==
                FDVar::DynamicVariable::StringType(""));
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE) ==
                FDVar::DynamicVariable(TEST_DYN_STRING_VALUE));
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE) == TEST_DYN_STRING_VALUE);
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE) !=
                FDVar::DynamicVariable::StringType("some other string"));
    ASSERT_TRUE(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE) !=
                FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("some other string")));

    ASSERT_FALSE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) ==
                 FDVar::DynamicVariable(false));
    ASSERT_TRUE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) !=
                FDVar::DynamicVariable(false));
    ASSERT_FALSE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) ==
                 FDVar::DynamicVariable(1));
    ASSERT_TRUE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) !=
                FDVar::DynamicVariable(1));
    ASSERT_FALSE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) ==
                 FDVar::DynamicVariable(1.0F));
    ASSERT_TRUE(FDVar::DynamicVariable(FDVar::DynamicVariable::StringType("")) !=
                FDVar::DynamicVariable(1.0F));
}

TEST(DynamicVariable_test, test_int_operators)
{
    {
        int test = 1;
        FDVar::DynamicVariable value(1);
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

    {
        int test = 4;
        FDVar::DynamicVariable value(4);
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

    {
        int test = 1;
        FDVar::DynamicVariable value(1);
        ASSERT_EQ(FDVar::DynamicVariable(value) *= 0, 0);
        ASSERT_EQ(value * 0, 0);
        ASSERT_EQ(FDVar::DynamicVariable(value) *= 1, value);
        ASSERT_EQ(value * 1, value);
        ASSERT_EQ(FDVar::DynamicVariable(value) *= -1, -value);
        ASSERT_EQ(value *= 2, test *= 2);
        ASSERT_EQ(value * 2, test * 2);
        ASSERT_EQ(value *= value, test *= test);
        ASSERT_EQ(value * value, test * test);
    }

    {
        int test = TEST_DYN_INT_VALUE;
        FDVar::DynamicVariable value(TEST_DYN_INT_VALUE);
        ASSERT_EQ(FDVar::DynamicVariable(value) /= 1, value);
        ASSERT_EQ(value / 1, value);
        ASSERT_EQ(FDVar::DynamicVariable(value) /= -1, -value);
        ASSERT_EQ(value /= 2, test /= 2);
        ASSERT_EQ(value / 2, test / 2);
        ASSERT_EQ(value / value, test / test);
        ASSERT_EQ(100 / value, 100 / test);
        value = 2;
        test = 4;
        ASSERT_EQ(test /= value, 2);
    }

    {
        int test = TEST_DYN_INT_VALUE;
        FDVar::DynamicVariable value(3);
        ASSERT_EQ(FDVar::DynamicVariable(test) % value, 1);
        ASSERT_EQ(FDVar::DynamicVariable(test) %= value, 1);
        ASSERT_EQ(test % value, 1);
        ASSERT_EQ(test %= value, 1);
    }

    {
        int test = 0;
        FDVar::DynamicVariable value(0);
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

    {
        int test = TEST_DYN_INT_VALUE;
        FDVar::DynamicVariable value(FDVar::ValueType::Integer);
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
}

TEST(DynamicVariable_test, test_float_operators)
{
    {
        float test = 1;
        FDVar::DynamicVariable value(1.0F);
        ASSERT_FLOAT_EQ(static_cast<float>(value += 0), test += 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value + 0.0), test + 0.0);
        ASSERT_FLOAT_EQ(static_cast<float>(value += 1), test += 1);
        ASSERT_FLOAT_EQ(static_cast<float>(value += value), test += test);
        ASSERT_FLOAT_EQ(static_cast<float>(value + value), test + test);

        ASSERT_FLOAT_EQ(static_cast<float>(value + test), test + value);
        ASSERT_FLOAT_EQ(static_cast<float>(value += test), 8U);
        ASSERT_FLOAT_EQ(test += value, 12.0);

        value = test = -1.0F;
        ASSERT_FLOAT_EQ(static_cast<float>(+value), +test);
    }

    {
        float test = 4.0F;
        FDVar::DynamicVariable value(4.0F);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= 0), test -= 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value - 0), test - 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= 1), test -= 1);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= value), test -= test);

        value = test = 2.0F;
        ASSERT_FLOAT_EQ(static_cast<float>(value - value), test - test);
        ASSERT_FLOAT_EQ(static_cast<float>(value - test), test - value);
        ASSERT_FLOAT_EQ(static_cast<float>(value -= test), 0.0F);
        value = 4.0F;
        ASSERT_FLOAT_EQ(test -= value, -2.0F);

        value = test = -1.0F;
        ASSERT_FLOAT_EQ(static_cast<float>(-value), -test);
        value = test = 0.0F;
        ASSERT_FLOAT_EQ(static_cast<float>(-value), 0);
    }

    {
        float test = 1;
        FDVar::DynamicVariable value(1.0F);
        ASSERT_FLOAT_EQ(static_cast<float>(FDVar::DynamicVariable(value) *= 0), 0);
        ASSERT_FLOAT_EQ(static_cast<float>(value * 0), 0);
        ASSERT_FLOAT_EQ(static_cast<float>(FDVar::DynamicVariable(value) *= 1),
                        static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(value * 1), static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(FDVar::DynamicVariable(value) *= -1),
                        static_cast<float>(-value));
        ASSERT_FLOAT_EQ(static_cast<float>(value *= 2), test *= 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value * 2), test * 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value *= value), test *= test);
        ASSERT_FLOAT_EQ(static_cast<float>(value * value), test * test);
    }

    {
        float test = TEST_DYN_FLOAT_VALUE;
        FDVar::DynamicVariable value(TEST_DYN_FLOAT_VALUE);
        ASSERT_FLOAT_EQ(static_cast<float>(FDVar::DynamicVariable(value) /= 1),
                        static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(value / 1), static_cast<float>(value));
        ASSERT_FLOAT_EQ(static_cast<float>(FDVar::DynamicVariable(value) /= -1),
                        static_cast<float>(-value));
        ASSERT_FLOAT_EQ(static_cast<float>(value /= 2), test /= 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value / 2), test / 2);
        ASSERT_FLOAT_EQ(static_cast<float>(value / value), test / test);
        ASSERT_FLOAT_EQ(static_cast<float>(100.0F / value), 100 / test);
        value = 2.0F;
        test = 4.0F;
        ASSERT_FLOAT_EQ(test /= value, 2);
    }

    {
        float test = TEST_DYN_FLOAT_VALUE;
        FDVar::DynamicVariable value(FDVar::ValueType::Float);
        std::stringstream ss;
        ss << test;
        ss >> value;
        ASSERT_FLOAT_EQ(static_cast<float>(value), test);
        ss.clear();
        value = 0.0F;
        ss << value;
        ss >> test;
        ASSERT_FLOAT_EQ(static_cast<float>(value), test);
    }
}

TEST(DynamicVariable_test, test_bool_operators)
{
    {
        FDVar::DynamicVariable b;
        FDVar::DynamicVariable other(true);
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

    {
        FDVar::DynamicVariable b(FDVar::ValueType::Boolean);
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
}

TEST(DynamicVariable_test, test_string_operators)
{
    {
        FDVar::DynamicVariable::StringType test;
        FDVar::DynamicVariable value(FDVar::DynamicVariable::StringType(""));
        ASSERT_EQ(value += TEST_DYN_STRING_VALUE, test += TEST_DYN_STRING_VALUE);
        ASSERT_EQ(value + TEST_DYN_STRING_VALUE, test + TEST_DYN_STRING_VALUE);
    }

    {
        FDVar::DynamicVariable::StringType test = TEST_DYN_STRING_VALUE;
        FDVar::DynamicVariable value(FDVar::DynamicVariable::StringType(""));
        std::stringstream ss;
        ss << test;
        ss >> value;
        std::cout << value << std::endl;
        ASSERT_EQ(value, test);
        ss.clear();
        value = FDVar::DynamicVariable::StringType("result");
        ss << value;
        ss >> test;
        ASSERT_EQ(value, test);
    }

    {
        FDVar::DynamicVariable::StringType test = TEST_DYN_STRING_VALUE;
        FDVar::DynamicVariable value(FDVar::DynamicVariable::StringType(""));
        ASSERT_TRUE(value.isEmpty());
        ASSERT_FALSE(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE).isEmpty());
        ASSERT_EQ(FDVar::DynamicVariable(TEST_DYN_STRING_VALUE).size(), test.size());
        value = TEST_DYN_STRING_VALUE;
        ASSERT_FALSE(value.isEmpty());
        value.clear();
        ASSERT_TRUE(value.isEmpty());
        value = test;
        ASSERT_EQ(value[0], FDVar::DynamicVariable::StringType(1, test[0]));
        value.append(" string");
        test.append(" string");
        ASSERT_EQ(value, test);
        ASSERT_EQ(value.subString(0, 4), test.substr(0, 4));
    }
}

TEST(DynamicVariable_test, test_array_operators)
{
    {
        ASSERT_TRUE(static_cast<const FDVar::DynamicVariable::ArrayType &>(
                      FDVar::DynamicVariable(FDVar::ValueType::Array))
                      .empty());
        ASSERT_FALSE(static_cast<const FDVar::DynamicVariable::ArrayType &>(
                       FDVar::DynamicVariable(TEST_ARRAY_VALUE))
                       .empty());

        FDVar::DynamicVariable value(TEST_ARRAY_VALUE);
        const auto &arr = static_cast<const FDVar::DynamicVariable::ArrayType &>(value);
        for(size_t i = 0; i < TEST_ARRAY_VALUE.size(); ++i)
        {
            ASSERT_EQ(value[i], arr[i]);
        }
    }

    {
        FDVar::DynamicVariable value(TEST_ARRAY_VALUE);
        FDVar::DynamicVariable::ArrayType arr(TEST_ARRAY_VALUE);
        FDVar::AbstractValue::Ptr cell(new FDVar::IntValue(42));
        arr.push_back(cell);
        value.push(FDVar::DynamicVariable(cell));
        ASSERT_EQ(value.size(), arr.size());
        ASSERT_EQ(value[value.size() - 1], arr.back());

        auto tmp = value.pop();
        ASSERT_EQ(tmp, cell);
        arr.pop_back();

        auto it = arr.begin();
        std::advance(it, 1);
        cell = *it;
        arr.erase(it);
        ASSERT_EQ(value.removeAt(1), cell);
        value.clear();
        ASSERT_TRUE(value.isEmpty());
    }
}

TEST(DynamicVariable_test, test_object_operators)
{
    {
        FDVar::DynamicVariable value(FDVar::ValueType::Object);
        ASSERT_EQ(value["no_member"], nullptr);

        value = FDVar::ObjectValue(TEST_DYN_OBJECT_VALUE);
        for(const auto &[key, val]: TEST_DYN_OBJECT_VALUE)
        {
            ASSERT_EQ(value[key], val);
        }
    }

    {
        ASSERT_TRUE(static_cast<const FDVar::DynamicVariable::ObjectType &>(
                      FDVar::DynamicVariable(FDVar::ValueType::Object))
                      .empty());
        ASSERT_FALSE(static_cast<const FDVar::DynamicVariable::ObjectType &>(
                       FDVar::ObjectValue(TEST_DYN_OBJECT_VALUE))
                       .empty());

        FDVar::DynamicVariable value(TEST_DYN_OBJECT_VALUE);
        const auto &obj = static_cast<const FDVar::DynamicVariable::ObjectType &>(value);
        for(const auto &[key, val]: obj)
        {
            ASSERT_EQ(value[key], val);
        }
    }

    {
        FDVar::DynamicVariable value(TEST_DYN_OBJECT_VALUE);
        FDVar::DynamicVariable member(42);
        value.set("i2", member);
        ASSERT_EQ(value.get("i2"), 42);
        value.unset("i2");
        ASSERT_EQ(value["i2"], nullptr);
    }
}

TEST(DynamicVariable_test, test_function_operators)
{
    using namespace FDVar;
    FDVar::DynamicVariable value;
    value = [](const FDVar::DynamicVariable &var) { return var * 2; };

    ASSERT_EQ(value(1_var), 2);
}

#endif // FDVAR_DYNAMICVARIABLE_TEST_H
