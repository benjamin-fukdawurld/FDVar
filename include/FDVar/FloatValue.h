#ifndef FDVAR_FLOATVALUE_H
#define FDVAR_FLOATVALUE_H

#ifndef FDVAR_FLOAT_TYPE
    #define FDVAR_FLOAT_TYPE double
#endif // FDVAR_FLOAT_TYPE

#include <FDVar/AbstractValue.h>
#include <math.h>
#include <type_traits>

namespace FDVar
{
    class FloatValue : public AbstractValue
    {
      public:
        typedef FDVAR_FLOAT_TYPE FloatType;

      private:
        FloatType m_value;

      public:
        FloatValue() : m_value(0) {}

        template<typename T,
                 typename U =
                   std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatType>>
        explicit FloatValue(T value) : m_value(static_cast<FloatType>(value))
        {
        }

        FloatValue(FloatValue &&) = default;
        FloatValue(const FloatValue &) = default;

        ~FloatValue() noexcept override = default;

        ValueType getValueType() const override { return ValueType::Float; }

        FloatValue &operator=(FloatValue &&) = default;
        FloatValue &operator=(const FloatValue &) = default;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator=(const T &value)
        {
            m_value = static_cast<FloatType>(value);
            return *this;
        }

        template<typename T,
                 typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                                               FloatValue>>
        explicit operator T() const
        {
            return static_cast<T>(m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator==(
          const T &value) const
        {
            return m_value == static_cast<FloatType>(value);
        }

        bool operator==(const FloatValue &value) const { return m_value == value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator!=(
          const T &value) const
        {
            return m_value != static_cast<FloatType>(value);
        }

        bool operator!=(const FloatValue &value) const { return m_value != value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator<=(
          const T &value) const
        {
            return m_value <= static_cast<FloatType>(value);
        }

        bool operator<=(const FloatValue &value) const { return m_value <= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator<(
          const T &value) const
        {
            return m_value < static_cast<FloatType>(value);
        }

        bool operator<(const FloatValue &value) const { return m_value < value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator>=(
          const T &value) const
        {
            return m_value >= static_cast<FloatType>(value);
        }

        bool operator>=(const FloatValue &value) const { return m_value >= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator>(
          const T &value) const
        {
            return m_value > static_cast<FloatType>(value);
        }

        bool operator>(const FloatValue &value) const { return m_value > value.m_value; }

        FloatValue operator-() const { return FloatValue(-m_value); }

        FloatValue operator+() const { return FloatValue(m_value); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator+=(const T &value)
        {
            m_value += static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator+=(const FloatValue &value)
        {
            m_value += value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator-=(const T &value)
        {
            m_value -= static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator-=(const FloatValue &value)
        {
            m_value -= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator+(
          const T &value) const
        {
            return FloatValue(m_value + static_cast<FloatType>(value));
        }

        FloatValue operator+(const FloatValue &value) const
        {
            return FloatValue(m_value + value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator-(
          const T &value) const
        {
            return FloatValue(m_value - static_cast<FloatType>(value));
        }

        FloatValue operator-(const FloatValue &value) const
        {
            return FloatValue(m_value - value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator*=(const T &value)
        {
            m_value *= static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator*=(const FloatValue &value)
        {
            m_value *= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue>
          &operator/=(const T &value)
        {
            m_value /= static_cast<FloatType>(value);
            return *this;
        }

        FloatValue &operator/=(const FloatValue &value)
        {
            m_value /= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator*(
          const T &value) const
        {
            return FloatValue(m_value * static_cast<FloatType>(value));
        }

        FloatValue operator*(const FloatValue &value) const
        {
            return FloatValue(m_value * value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, FloatValue> operator/(
          const T &value) const
        {
            return FloatValue(m_value / static_cast<FloatType>(value));
        }

        FloatValue operator/(const FloatValue &value) const
        {
            return FloatValue(m_value / value.m_value);
        }
    };

    template<typename T>
    struct is_AbstractValue_constructible<T, std::enable_if_t<std::is_floating_point_v<T>>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_floating_point_v<T>, T> &value)
    {
        return AbstractValue::Ptr(new FloatValue(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_floating_point_v<T>, T>> fromAbstractValuePtr(
      const AbstractValue::Ptr &value)
    {
        if(value->isType(ValueType::Float))
        {
            return static_cast<T>(static_cast<const FloatValue &>(*value));
        }

        return std::nullopt;
    }
} // namespace FDVar

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator+=(
  T &value, const FDVar::FloatValue &other)
{
    return value += static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDVar::FloatValue::FloatType>())>
  operator+(const T &value, const FDVar::FloatValue &other)
{
    return value + static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator-=(
  T &value, const FDVar::FloatValue &other)
{
    return value -= static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDVar::FloatValue::FloatType>())>
  operator-(const T &value, const FDVar::FloatValue &other)
{
    return value - static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator*=(
  T &value, const FDVar::FloatValue &other)
{
    return value *= static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDVar::FloatValue::FloatType>())>
  operator*(const T &value, const FDVar::FloatValue &other)
{
    return value * static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator/=(
  T &value, const FDVar::FloatValue &other)
{
    return value /= static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>,
                 decltype(std::declval<T>() + std::declval<FDVar::FloatValue::FloatType>())>
  operator/(const T &value, const FDVar::FloatValue &other)
{
    return value / static_cast<FDVar::FloatValue::FloatType>(other);
}

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDVar::FloatValue &value)
{
    stream << static_cast<const FDVar::FloatValue::FloatType &>(value);
    return stream;
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDVar::FloatValue &value)
{
    FDVar::FloatValue::FloatType tmp = NAN;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDVAR_FLOATVALUE_H
