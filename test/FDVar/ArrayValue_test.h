#ifndef FDVAR_ARRAYVALUE_TEST_H
#define FDVAR_ARRAYVALUE_TEST_H

#include <FDVar/ArrayValue.h>
#include <FDVar/BoolValue.h>
#include <FDVar/FloatValue.h>
#include <FDVar/IntValue.h>
#include <FDVar/StringValue.h>

#include <gtest/gtest.h>
#include <iostream>
#include <list>

static const FDVar::ArrayValue::ArrayType TEST_ARRAY_VALUE = {
    FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)),
    FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)),
    FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)),
    FDVar::AbstractValue::Ptr(new FDVar::StringValue("text"))
};

static const std::list<FDVar::AbstractValue::Ptr> TEST_CUSTOM_ARRAY_VALUE = {
    FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)),
    FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)),
    FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)),
    FDVar::AbstractValue::Ptr(new FDVar::StringValue("text"))
};

class CustomArrayValue : public FDVar::AbstractArrayValue
{
  public:
    typedef std::list<FDVar::AbstractValue::Ptr> ArrayType;

  private:
    ArrayType m_values;

  public:
    CustomArrayValue() = default;
    CustomArrayValue(CustomArrayValue &&) = default;
    CustomArrayValue(const CustomArrayValue &) = default;
    CustomArrayValue(ArrayType &&values) : m_values(std::move(values)) {}
    CustomArrayValue(const ArrayType &values) : m_values(values) {}

    CustomArrayValue(std::initializer_list<FDVar::AbstractValue::Ptr> l) : m_values(l) {}

    ~CustomArrayValue() override = default;

    explicit operator const ArrayType &() const { return m_values; }

    SizeType size() const override { return m_values.size(); }
    bool isEmpty() const override { return m_values.empty(); }
    FDVar::AbstractValue::Ptr operator[](SizeType pos) override
    {
        auto it = m_values.begin();
        std::advance(it, pos);
        return *it;
    }

    const FDVar::AbstractValue::Ptr &operator[](SizeType pos) const override
    {
        auto it = m_values.begin();
        std::advance(it, pos);
        return *it;
    }

    void push(AbstractValue::Ptr value) override { m_values.push_back(std::move(value)); }
    AbstractValue::Ptr pop() override
    {
        AbstractValue::Ptr result = m_values.back();
        m_values.pop_back();
        return result;
    }

    void insert(AbstractValue::Ptr value, SizeType pos) override
    {
        auto it = m_values.begin();
        std::advance(it, pos);
        m_values.insert(it, value);
    }

    AbstractValue::Ptr removeAt(SizeType pos) override
    {
        auto it = m_values.begin();
        std::advance(it, pos);
        AbstractValue::Ptr result = *it;
        m_values.erase(it);

        return result;
    }

    void clear() override { m_values.clear(); }
};

TEST(ArrayValue_test, test_constructors)
{
    ASSERT_TRUE(FDVar::ArrayValue().isEmpty());
    ASSERT_EQ(FDVar::ArrayValue().size(), 0);
    ASSERT_FALSE(FDVar::ArrayValue(TEST_ARRAY_VALUE).isEmpty());
    ASSERT_EQ(FDVar::ArrayValue(TEST_ARRAY_VALUE).size(), TEST_ARRAY_VALUE.size());
    ASSERT_EQ(FDVar::ArrayValue({ FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)),
                                  FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)),
                                  FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)),
                                  FDVar::AbstractValue::Ptr(new FDVar::StringValue("text")) })
                .size(),
              TEST_ARRAY_VALUE.size());
}

TEST(ArrayValue_test, test_cast_operators)
{
    ASSERT_TRUE(static_cast<FDVar::ArrayValue::ArrayType>(FDVar::ArrayValue()).empty());
    ASSERT_FALSE(
      static_cast<const FDVar::ArrayValue::ArrayType &>(FDVar::ArrayValue(TEST_ARRAY_VALUE))
        .empty());

    FDVar::ArrayValue value(TEST_ARRAY_VALUE);
    const auto &arr = static_cast<const FDVar::ArrayValue::ArrayType &>(value);
    for(size_t i = 0; i < TEST_ARRAY_VALUE.size(); ++i)
    {
        ASSERT_EQ(value[i], arr[i]);
    }
}

TEST(ArrayValue_test, test_member_functions)
{
    FDVar::ArrayValue value(TEST_ARRAY_VALUE);
    FDVar::ArrayValue::ArrayType arr(TEST_ARRAY_VALUE);
    FDVar::AbstractValue::Ptr cell(new FDVar::IntValue(42));
    arr.push_back(cell);
    value.push(cell);
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

TEST(CustomArrayValue_test, test_constructors)
{
    ASSERT_TRUE(CustomArrayValue().isEmpty());
    ASSERT_EQ(CustomArrayValue().size(), 0);
    ASSERT_FALSE(CustomArrayValue(TEST_CUSTOM_ARRAY_VALUE).isEmpty());
    ASSERT_EQ(CustomArrayValue(TEST_CUSTOM_ARRAY_VALUE).size(), TEST_CUSTOM_ARRAY_VALUE.size());
    ASSERT_EQ(CustomArrayValue({ FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)),
                                 FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)),
                                 FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)),
                                 FDVar::AbstractValue::Ptr(new FDVar::StringValue("text")) })
                .size(),
              TEST_CUSTOM_ARRAY_VALUE.size());
}

TEST(CustomArrayValue_test, test_cast_operators)
{
    ASSERT_TRUE(static_cast<CustomArrayValue::ArrayType>(CustomArrayValue()).empty());
    ASSERT_FALSE(
      static_cast<const CustomArrayValue::ArrayType &>(CustomArrayValue(TEST_CUSTOM_ARRAY_VALUE))
        .empty());

    CustomArrayValue value(TEST_CUSTOM_ARRAY_VALUE);
    const auto &arr = static_cast<const CustomArrayValue::ArrayType &>(value);
    auto it = arr.begin();
    for(size_t i = 0; i < value.size(); ++i, ++it)
    {
        ASSERT_EQ(value[i], *it);
    }
}

TEST(CustomArrayValue_test, test_member_functions)
{
    CustomArrayValue value(TEST_CUSTOM_ARRAY_VALUE);
    CustomArrayValue::ArrayType arr(TEST_CUSTOM_ARRAY_VALUE);
    FDVar::AbstractValue::Ptr cell(new FDVar::IntValue(42));
    arr.push_back(cell);
    value.push(cell);
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


#endif // FDVAR_ARRAYVALUE_TEST_H
