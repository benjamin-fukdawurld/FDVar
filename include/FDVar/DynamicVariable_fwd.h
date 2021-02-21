#ifndef FDVAR_DYNAMICVARIABLE_FWD_H
#define FDVAR_DYNAMICVARIABLE_FWD_H

#include <algorithm>
#include <deque>
#include <forward_list>
#include <initializer_list>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <FDVar/AbstractValue.h>

#include <FDVar/AbstractArrayValue.h>
#include <FDVar/AbstractObjectValue.h>
#include <FDVar/ArrayValue.h>
#include <FDVar/BoolValue.h>
#include <FDVar/FloatValue.h>
#include <FDVar/FunctionValue.h>
#include <FDVar/IntValue.h>
#include <FDVar/ObjectValue.h>
#include <FDVar/StringValue.h>

namespace FDVar
{
    class DynamicVariable;

    template<typename T, typename U = void>
    struct is_DynamicVariable_constructible
    {
        constexpr static bool value = is_AbstractValue_constructible_v<T>;
    };

    template<class T>
    inline constexpr bool is_DynamicVariable_constructible_v =
      is_DynamicVariable_constructible<T>::value;

    template<typename T>
    struct is_DynamicVariable_constructible<
      T,
      std::enable_if_t<
        std::is_same_v<std::vector<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
          std::is_same_v<std::deque<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
          std::is_same_v<std::list<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
          std::is_same_v<std::forward_list<DynamicVariable, std::allocator<DynamicVariable>>, T>,
        T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    struct is_DynamicVariable_constructible<
      T,
      std::enable_if_t<
        std::is_same_v<std::initializer_list<std::pair<ObjectValue::StringType, DynamicVariable>>,
                       T>,
        T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    struct is_DynamicVariable_constructible<
      T,
      std::enable_if_t<
        std::is_same_v<std::map<ObjectValue::StringType, DynamicVariable>, T> ||
          std::is_same_v<std::unordered_map<ObjectValue::StringType, DynamicVariable>, T>,
        T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    struct is_DynamicVariable_constructible<
      std::initializer_list<T>,
      std::enable_if_t<is_DynamicVariable_constructible_v<T>, std::initializer_list<T>>>
    {
        constexpr static bool value = true;
    };

    template<template<typename, typename> class ContainerType, typename T, typename AllocatorType>
    struct is_DynamicVariable_constructible<
      ContainerType<T, AllocatorType>,
      std::enable_if_t<is_DynamicVariable_constructible_v<T>, T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    struct is_DynamicVariable_constructible<
      std::initializer_list<std::pair<ObjectValue::StringType, T>>,
      std::enable_if_t<is_DynamicVariable_constructible_v<T>,
                       std::initializer_list<std::pair<ObjectValue::StringType, T>>>>
    {
        constexpr static bool value = true;
    };
    template<template<typename, typename, typename, typename> class ContainerType,
             typename Key,
             typename T,
             typename Compare,
             typename AllocatorType>
    struct is_DynamicVariable_constructible<
      ContainerType<Key, T, Compare, AllocatorType>,
      std::enable_if_t<is_DynamicVariable_constructible_v<T>,
                       ContainerType<Key, T, Compare, AllocatorType>>>
    {
        constexpr static bool value = true;
    };

    class DynamicVariable
    {
      public:
        typedef IntValue::IntType IntType;
        typedef FloatValue::FloatType FloatType;
        typedef StringValue::StringType StringType;
        typedef StringValue::StringViewType StringViewType;
        typedef ArrayValue::ArrayType ArrayType;
        typedef ArrayValue::SizeType SizeType;
        typedef ObjectValue::ObjectType ObjectType;
        typedef std::function<DynamicVariable(DynamicVariable)> FunctionType;

      private:
        AbstractValue::Ptr m_value;

      public:
        DynamicVariable();
        DynamicVariable(ValueType type);

        DynamicVariable(DynamicVariable &&) = default;
        DynamicVariable(const DynamicVariable &);

        DynamicVariable(AbstractValue::Ptr &&value);
        DynamicVariable(const AbstractValue::Ptr &value);

        template<typename T, typename U = std::enable_if_t<std::is_base_of_v<AbstractValue, T>, T>>
        DynamicVariable(const T &value);

        template<typename T, typename U = std::enable_if_t<std::is_base_of_v<AbstractValue, T>, T>>
        DynamicVariable(T &&value);

        DynamicVariable(StringViewType value);

        explicit DynamicVariable(ArrayType &&value);

        explicit DynamicVariable(ObjectType &&value);

        template<typename T>
        explicit DynamicVariable(const T &value,
                                 std::enable_if_t<is_DynamicVariable_constructible<T>::value,
                                                  is_DynamicVariable_constructible<T>>
                                 /*unused*/
                                 = {});

        explicit DynamicVariable(std::initializer_list<AbstractValue::Ptr> l);

        explicit DynamicVariable(std::initializer_list<DynamicVariable> l);

        explicit DynamicVariable(
          std::initializer_list<std::pair<StringViewType, DynamicVariable>> l);

        explicit DynamicVariable(const FunctionType &value);

        virtual ~DynamicVariable() = default;

        ValueType getValueType() const
        {
            return !m_value ? ValueType::None : m_value->getValueType();
        }

        bool isType(ValueType type) const { return type == getValueType(); }

        DynamicVariable &operator=(const DynamicVariable &);
        DynamicVariable &operator=(DynamicVariable &&) = default;

        DynamicVariable &operator=(StringViewType str);

        DynamicVariable &operator=(ArrayType &&arr);
        DynamicVariable &operator=(const ArrayType &arr);

        template<typename T>
        std::enable_if_t<is_DynamicVariable_constructible<T>::value, DynamicVariable &> operator=(
          const T &value);

        DynamicVariable &operator=(const FunctionType &value)
        {
            m_value = std::make_shared<FunctionValue>(wrapFunction(value));
            return *this;
        }

        explicit operator bool() const;
        explicit operator const StringType &() const;
        explicit operator const ArrayType &() const;
        explicit operator const ObjectType &() const;

        template<typename T>
        explicit operator T() const
        {
            T result;
            convert<T>(result);
            return result;
        }

        bool operator==(const DynamicVariable &value) const;

        bool operator!=(const DynamicVariable &value) const;

        bool operator==(std::nullptr_t) const;

        bool operator!=(std::nullptr_t) const;

        bool operator==(bool value) const;

        bool operator!=(bool value) const;

        bool operator==(StringViewType value) const;

        bool operator!=(StringViewType value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator==(
          const T &value) const;


        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator!=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator<=(
          const T &value) const;


        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator<(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator>=(
          const T &value) const;


        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
          const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool> operator>(
          const T &value) const;

        DynamicVariable operator!() const
        {
            if(isType(ValueType::Boolean))
            {
                return !toBoolean();
            }

            if(isType(ValueType::Function))
            {
                return BoolValue(!toFunction());
            }

            throw generateCastException(__func__);
        }

        DynamicVariable operator()(const DynamicVariable &var) { return toFunction()(var.m_value); }

        bool operator&&(bool other) const { return toBoolean() && other; }
        bool operator&&(const DynamicVariable &other) const
        {
            return toBoolean() && other.toBoolean();
        }

        bool operator||(bool other) const { return toBoolean() || other; }
        bool operator||(const DynamicVariable &other) const
        {
            return toBoolean() || other.toBoolean();
        }

        bool operator^(bool other) const { return toBoolean() ^ other; }

        DynamicVariable operator-() const;

        DynamicVariable operator~() const;

        DynamicVariable operator+() const;

        DynamicVariable &operator++();

        DynamicVariable operator++(int);

        DynamicVariable &operator--();

        DynamicVariable operator--(int);

        DynamicVariable &operator+=(StringViewType value);

        DynamicVariable &operator+=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator+=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator+=(const T &value);

        DynamicVariable &operator-=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator-=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator-=(const T &value);

        DynamicVariable operator+(StringViewType value) const;

        DynamicVariable operator+(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator+(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator+(const T &value) const;

        DynamicVariable operator-(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator-(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator-(const T &value) const;

        DynamicVariable &operator*=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator*=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator*=(const T &value);

        DynamicVariable operator*(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator*(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator*(const T &value) const;

        DynamicVariable &operator/=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator/=(const T &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          &operator/=(const T &value);

        DynamicVariable operator/(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator/(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
          operator/(const T &value) const;

        DynamicVariable &operator%=(const DynamicVariable &value);

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator%=(const T &value);

        DynamicVariable operator%(const DynamicVariable &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator%(const T &value) const;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator<<=(const T &value)
        {
            toInteger() <<= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator<<=(const DynamicVariable &value)
        {
            toInteger() <<= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator>>=(const T &value)
        {
            toInteger() >>= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator>>=(const DynamicVariable &value)
        {
            toInteger() >>= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator<<(const T &value) const
        {
            return toInteger() << static_cast<IntType>(value);
        }

        DynamicVariable operator<<(const DynamicVariable &value) const
        {
            return toInteger() << value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator>>(const T &value) const
        {
            return toInteger() >> static_cast<IntType>(value);
        }

        DynamicVariable operator>>(const DynamicVariable &value) const
        {
            return toInteger() >> value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator&=(const T &value)
        {
            toInteger() &= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator&=(const DynamicVariable &value)
        {
            toInteger() &= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator&(const T &value) const
        {
            return toInteger() & static_cast<IntType>(value);
        }

        DynamicVariable operator&(const DynamicVariable &value) const
        {
            return toInteger() & value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator|=(const T &value)
        {
            toInteger() |= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator|=(const DynamicVariable &value)
        {
            toInteger() |= value.toInteger();
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator|(const T &value) const
        {
            return toInteger() | static_cast<IntType>(value);
        }

        DynamicVariable operator|(const DynamicVariable &value) const
        {
            return toInteger() | value.toInteger();
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          &operator^=(const T &value)
        {
            toInteger() ^= static_cast<IntType>(value);
            return *this;
        }

        DynamicVariable &operator^=(const DynamicVariable &value)
        {
            if(isType(ValueType::Integer))
            {
                toInteger() ^= value.toInteger();
            }
            else if(isType(ValueType::Boolean))
            {
                toBoolean() ^= value.toBoolean();
            }
            else
            {
                throw generateCastException(__func__);
            }

            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
          operator^(const T &value) const
        {
            return toInteger() ^ static_cast<IntType>(value);
        }

        DynamicVariable operator^(const DynamicVariable &value) const
        {
            if(isType(ValueType::Integer))
            {
                return DynamicVariable(toInteger() ^ value.toInteger());
            }
            if(isType(ValueType::Boolean))
            {
                return DynamicVariable(toBoolean() ^ value.toBoolean());
            }

            throw generateCastException(__func__);


            return *this;
        }

        SizeType size() const;
        bool isEmpty() const;
        DynamicVariable operator[](SizeType pos);
        DynamicVariable operator[](SizeType pos) const;
        DynamicVariable operator[](StringViewType member);
        DynamicVariable operator[](StringViewType member) const;
        DynamicVariable operator[](const DynamicVariable &var);
        DynamicVariable operator[](const DynamicVariable &var) const;

        DynamicVariable keys() const;
        DynamicVariable get(StringViewType member);
        void set(StringViewType key, const DynamicVariable &value);
        void unset(StringViewType key);

        void push(const DynamicVariable &value);
        DynamicVariable pop();

        void insert(const DynamicVariable &value, SizeType pos);
        DynamicVariable removeAt(SizeType pos);
        void clear();

        void append(const DynamicVariable &str) { append(static_cast<const StringType &>(str)); };
        void append(StringViewType str);
        DynamicVariable subString(SizeType from, SizeType count);

        template<typename StreamType,
                 typename U = std::enable_if_t<!std::is_integral_v<StreamType> &&
                                                 !std::is_same_v<DynamicVariable, StreamType>,
                                               StreamType>>
        void read(StreamType &stream);

        template<typename StreamType,
                 typename U = std::enable_if_t<!std::is_integral_v<StreamType> &&
                                                 !std::is_same_v<DynamicVariable, StreamType>,
                                               StreamType>>

        void write(StreamType &stream) const;

        AbstractValue::Ptr internalValue() { return m_value; }

      private:
        std::runtime_error generateCastException(const std::string &caller) const
        {
            return std::runtime_error(caller + ": unsupported action on type " +
                                      std::to_string(getValueType()));
        }

        static FunctionValue::FunctionType wrapFunction(const FunctionType &func)
        {
            return [func](AbstractValue::Ptr var) -> AbstractValue::Ptr {
                return func(DynamicVariable(std::move(var))).m_value;
            };
        }

        BoolValue &toBoolean()
        {
            if(!isType(ValueType::Boolean))
            {
                throw generateCastException(__func__);
            }

            return static_cast<BoolValue &>(*m_value);
        }


        const BoolValue &toBoolean() const
        {
            if(!isType(ValueType::Boolean))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const BoolValue &>(*m_value);
        }

        IntValue &toInteger()
        {
            if(!isType(ValueType::Integer))
            {
                throw generateCastException(__func__);
            }

            return static_cast<IntValue &>(*m_value);
        }


        const IntValue &toInteger() const
        {
            if(!isType(ValueType::Integer))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const IntValue &>(*m_value);
        }

        FloatValue &toFloat()
        {
            if(!isType(ValueType::Float))
            {
                throw generateCastException(__func__);
            }

            return static_cast<FloatValue &>(*m_value);
        }


        const FloatValue &toFloat() const
        {
            if(!isType(ValueType::Float))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const FloatValue &>(*m_value);
        }

        StringValue &toString()
        {
            if(!isType(ValueType::String))
            {
                throw generateCastException(__func__);
            }

            return static_cast<StringValue &>(*m_value);
        }

        const StringValue &toString() const
        {
            if(!isType(ValueType::String))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const StringValue &>(*m_value);
        }

        AbstractArrayValue &toArray()
        {
            if(!isType(ValueType::Array))
            {
                throw generateCastException(__func__);
            }

            return static_cast<AbstractArrayValue &>(*m_value);
        }

        const AbstractArrayValue &toArray() const
        {
            if(!isType(ValueType::Array))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const AbstractArrayValue &>(*m_value);
        }

        AbstractObjectValue &toObject()
        {
            if(!isType(ValueType::Object))
            {
                throw generateCastException(__func__);
            }

            return static_cast<AbstractObjectValue &>(*m_value);
        }

        const AbstractObjectValue &toObject() const
        {
            if(!isType(ValueType::Object))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const AbstractObjectValue &>(*m_value);
        }

        FunctionValue &toFunction()
        {
            if(!isType(ValueType::Function))
            {
                throw generateCastException(__func__);
            }

            return static_cast<FunctionValue &>(*m_value);
        }

        const FunctionValue &toFunction() const
        {
            if(!isType(ValueType::Function))
            {
                throw generateCastException(__func__);
            }

            return static_cast<const FunctionValue &>(*m_value);
        }

        template<typename T>
        void convert(
          std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &result) const;

        template<typename T>
        void convert(std::enable_if_t<std::is_floating_point_v<T>, T> &result) const;
    };

    template<typename T>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<is_AbstractValue_constructible_v<T>, T> &value)
    {
        return DynamicVariable(FDVar::toAbstractValuePtr<T>(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<is_AbstractValue_constructible_v<T>, T>> fromDynamicVariable(
      const DynamicVariable &value)
    {
        return FDVar::fromAbstractValuePtr<T>(value);
    }
} // namespace FDVar

#endif // FDVAR_DYNAMICVARIABLE_FWD_H
