#ifndef FDVAR_OBJECTVALUE_TEST_H
#define FDVAR_OBJECTVALUE_TEST_H

#include <FDVar/BoolValue.h>
#include <FDVar/FloatValue.h>
#include <FDVar/IntValue.h>
#include <FDVar/ObjectValue.h>
#include <FDVar/StringValue.h>

#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include <map>

static FDVar::ObjectValue::ObjectType TEST_OBJECT_VALUE = {
    { "i", FDVar::AbstractValue::Ptr(new FDVar::IntValue(42)) },
    { "b", FDVar::AbstractValue::Ptr(new FDVar::BoolValue(true)) },
    { "f", FDVar::AbstractValue::Ptr(new FDVar::FloatValue(3.14159)) },
    { "s", FDVar::AbstractValue::Ptr(new FDVar::StringValue("text")) }
};

class CustomObjectValue : public FDVar::AbstractObjectValue
{
  private:
    int i;
    float f;
    bool b;
    std::string s;

  public:
    CustomObjectValue() :
        i(static_cast<int>(static_cast<FDVar::IntValue &>(*(TEST_OBJECT_VALUE["i"])))),
        f(static_cast<float>(static_cast<FDVar::FloatValue &>(*(TEST_OBJECT_VALUE["f"])))),
        b(static_cast<bool>(static_cast<FDVar::BoolValue &>(*(TEST_OBJECT_VALUE["b"])))),
        s(static_cast<std::string>(static_cast<FDVar::StringValue &>(*(TEST_OBJECT_VALUE["s"]))))
    {
    }

    CustomObjectValue(CustomObjectValue &&) = default;
    CustomObjectValue(const CustomObjectValue &) = default;

    FDVar::AbstractValue::Ptr keys() const override
    {
        std::unique_ptr<FDVar::ArrayValue> result;
        result->push(std::make_shared<FDVar::StringValue>("i"));
        result->push(std::make_shared<FDVar::StringValue>("f"));
        result->push(std::make_shared<FDVar::StringValue>("b"));
        result->push(std::make_shared<FDVar::StringValue>("s"));

        return FDVar::AbstractValue::Ptr(result.release());
    }

    ~CustomObjectValue() override = default;

    FDVar::AbstractValue::Ptr operator[](StringViewType member) override
    {
        if(member == "i")
        {
            return std::make_shared<FDVar::IntValue>(i);
        }
        if(member == "f")
        {
            return std::make_shared<FDVar::FloatValue>(f);
        }
        if(member == "b")
        {
            return std::make_shared<FDVar::BoolValue>(b);
        }
        if(member == "s")
        {
            return std::make_shared<FDVar::StringValue>(s);
        }

        throw std::runtime_error(std::string(__func__) + std::string(" cannot acces member : ") +
                                 std::string(member));
    }

    FDVar::AbstractValue::Ptr operator[](StringViewType member) const override
    {
        return const_cast<CustomObjectValue *>(this)->operator[](member);
    }

    void set(StringViewType /*key*/, FDVar::AbstractValue::Ptr /*value*/) override
    {
        throw std::runtime_error(std::string(__func__) + std::string(" is not supported"));
    }

    void unset(StringViewType /*key*/) override
    {
        throw std::runtime_error(std::string(__func__) + std::string(" is not supported"));
    }
};

TEST(ObjectValue_test, test_constructors)
{
    FDVar::ObjectValue value;
    ASSERT_EQ(value["no_member"].get(), nullptr);

    value = FDVar::ObjectValue(TEST_OBJECT_VALUE);
    for(const auto &[key, val]: TEST_OBJECT_VALUE)
    {
        ASSERT_EQ(value[key], val);
    }
}

TEST(ObjectValue_test, test_cast_operators)
{
    ASSERT_TRUE(static_cast<FDVar::ObjectValue::ObjectType>(FDVar::ObjectValue()).empty());
    ASSERT_FALSE(
      static_cast<const FDVar::ObjectValue::ObjectType &>(FDVar::ObjectValue(TEST_OBJECT_VALUE))
        .empty());

    FDVar::ObjectValue value(TEST_OBJECT_VALUE);
    const auto &obj = static_cast<const FDVar::ObjectValue::ObjectType &>(value);
    for(const auto &[key, val]: obj)
    {
        ASSERT_EQ(value[key], val);
    }
}

TEST(ObjectValue_test, test_member_functions)
{
    FDVar::ObjectValue value(TEST_OBJECT_VALUE);
    FDVar::ObjectValue::ObjectType obj(TEST_OBJECT_VALUE);
    FDVar::AbstractValue::Ptr member(new FDVar::IntValue(42));
    obj["i2"] = member;
    value.set("i2", member);
    ASSERT_EQ(value.get("i2"), obj["i2"]);

    value.unset("i2");
    ASSERT_EQ(value["i2"], nullptr);
    obj.erase("i2");
}

TEST(CustomObjectValue_test, test_constructors)
{
    CustomObjectValue value;
    ASSERT_THROW(value["no_member"].get(), std::runtime_error);
    for(const auto &[key, val]: TEST_OBJECT_VALUE)
    {
        ASSERT_EQ(value[key]->getValueType(), val->getValueType());
    }
}

TEST(CustomObjectValue_test, test_member_functions)
{
    CustomObjectValue value;
    FDVar::AbstractValue::Ptr member(new FDVar::IntValue(42));
    ASSERT_THROW(value.set("i2", member), std::runtime_error);
    ASSERT_THROW(value.get("i2"), std::runtime_error);

    ASSERT_THROW(value.unset("i2"), std::runtime_error);
}

#endif // FDVAR_OBJECTVALUE_TEST_H
