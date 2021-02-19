#ifndef FDVAR_FUNCTIONVALUE_TEST_H
#define FDVAR_FUNCTIONVALUE_TEST_H

#include <FDVar/FunctionValue.h>
#include <FDVar/IntValue.h>

TEST(FunctionValue_test, test_constructors)
{
    ASSERT_TRUE(!FDVar::FunctionValue());
    ASSERT_FALSE(static_cast<bool>(FDVar::FunctionValue()));

    ASSERT_FALSE(
      !FDVar::FunctionValue([](FDVar::AbstractValue::Ptr) { return FDVar::AbstractValue::Ptr(); }));
    ASSERT_TRUE(static_cast<bool>(
      FDVar::FunctionValue([](FDVar::AbstractValue::Ptr) { return FDVar::AbstractValue::Ptr(); })));

    FDVar::FunctionValue value;
    value = [](FDVar::AbstractValue::Ptr) { return FDVar::AbstractValue::Ptr(); };
    ASSERT_FALSE(!value);
    ASSERT_TRUE(static_cast<bool>(value));
}

TEST(FunctionValue_test, test_member_functions)
{
    FDVar::FunctionValue value;
    value = [](FDVar::AbstractValue::Ptr var) {
        return FDVar::AbstractValue::Ptr(
          new FDVar::IntValue(static_cast<FDVar::IntValue &>(*var) * 2));
    };

    ASSERT_EQ(
      static_cast<FDVar::IntValue &>(*(value(FDVar::AbstractValue::Ptr(new FDVar::IntValue(1))))),
      2);
}

#endif // FDVAR_FUNCTIONVALUE_TEST_H
