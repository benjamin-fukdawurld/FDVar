#ifndef FDVAR_INTVALUE_H
#define FDVAR_INTVALUE_H

#ifndef FDVAR_INT_TYPE
    #define FDVAR_INT_TYPE int64_t
#endif // FDVAR_INT_TYPE

#include <FDVar/AbstractValue.h>

namespace FDVar
{
    class IntValue : public AbstractValue
    {
      public:
        typedef FDVAR_INT_TYPE IntType;

      private:
        IntType m_value;

      public:
        IntValue() : m_value(0) {}

        template<
          typename T,
          typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntType>>
        explicit IntValue(T value) : m_value(static_cast<IntType>(value))
        {
        }

        IntValue(IntValue &&) = default;
        IntValue(const IntValue &) = default;

        ~IntValue() noexcept override = default;

        ValueType getValueType() const override { return ValueType::Integer; }

        IntValue &operator=(IntValue &&) = default;
        IntValue &operator=(const IntValue &) = default;

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator=(
          const T &value)
        {
            m_value = static_cast<IntType>(value);
            return *this;
        }

        template<
          typename T,
          typename U = std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T>>
        explicit operator T() const
        {
            return static_cast<T>(m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
          const T &value) const
        {
            return m_value == static_cast<IntType>(value);
        }

        bool operator==(const IntValue &value) const { return m_value == value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
          const T &value) const
        {
            return m_value != static_cast<IntType>(value);
        }

        bool operator!=(const IntValue &value) const { return m_value != value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
          const T &value) const
        {
            return m_value <= static_cast<IntType>(value);
        }

        bool operator<=(const IntValue &value) const { return m_value <= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
          const T &value) const
        {
            return m_value < static_cast<IntType>(value);
        }

        bool operator<(const IntValue &value) const { return m_value < value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
          const T &value) const
        {
            return m_value >= static_cast<IntType>(value);
        }

        bool operator>=(const IntValue &value) const { return m_value >= value.m_value; }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
          const T &value) const
        {
            return m_value > static_cast<IntType>(value);
        }

        bool operator>(const IntValue &value) const { return m_value > value.m_value; }

        IntValue operator-() const { return IntValue(-m_value); }

        IntValue operator~() const { return IntValue(~m_value); }

        IntValue operator+() const { return IntValue(m_value); }

        IntValue &operator++()
        {
            ++m_value;
            return *this;
        }

        IntValue operator++(int) { return IntValue(m_value++); }

        IntValue &operator--()
        {
            --m_value;
            return *this;
        }

        IntValue operator--(int) { return IntValue(m_value--); }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator+=(
          const T &value)
        {
            m_value += static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator+=(const IntValue &value)
        {
            m_value += value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator-=(
          const T &value)
        {
            m_value -= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator-=(const IntValue &value)
        {
            m_value -= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator+(
          const T &value) const
        {
            return IntValue(m_value + static_cast<IntType>(value));
        }

        IntValue operator+(const IntValue &value) const
        {
            return IntValue(m_value + value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator-(
          const T &value) const
        {
            return IntValue(m_value - static_cast<IntType>(value));
        }

        IntValue operator-(const IntValue &value) const
        {
            return IntValue(m_value - value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator*=(
          const T &value)
        {
            m_value *= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator*=(const IntValue &value)
        {
            m_value *= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator/=(
          const T &value)
        {
            m_value /= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator/=(const IntValue &value)
        {
            m_value /= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator*(
          const T &value) const
        {
            return IntValue(m_value * static_cast<IntType>(value));
        }

        IntValue operator*(const IntValue &value) const
        {
            return IntValue(m_value * value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator/(
          const T &value) const
        {
            return IntValue(m_value / static_cast<IntType>(value));
        }

        IntValue operator/(const IntValue &value) const
        {
            return IntValue(m_value / value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator%=(
          const T &value)
        {
            m_value %= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator%=(const IntValue &value)
        {
            m_value %= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator%(
          const T &value) const
        {
            return IntValue(m_value % static_cast<IntType>(value));
        }

        IntValue operator%(const IntValue &value) const
        {
            return IntValue(m_value % value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator<<=(
          const T &value)
        {
            m_value <<= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator<<=(const IntValue &value)
        {
            m_value <<= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator>>=(
          const T &value)
        {
            m_value >>= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator>>=(const IntValue &value)
        {
            m_value >>= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator<<(
          const T &value) const
        {
            return IntValue(m_value << static_cast<IntType>(value));
        }

        IntValue operator<<(const IntValue &value) const
        {
            return IntValue(m_value << value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator>>(
          const T &value) const
        {
            return IntValue(m_value >> static_cast<IntType>(value));
        }

        IntValue operator>>(const IntValue &value) const
        {
            return IntValue(m_value >> value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator&=(
          const T &value)
        {
            m_value &= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator&=(const IntValue &value)
        {
            m_value &= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator&(
          const T &value) const
        {
            return IntValue(m_value & static_cast<IntType>(value));
        }

        IntValue operator&(const IntValue &value) const
        {
            return IntValue(m_value & value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator|=(
          const T &value)
        {
            m_value |= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator|=(const IntValue &value)
        {
            m_value |= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator|(
          const T &value) const
        {
            return IntValue(m_value | static_cast<IntType>(value));
        }

        IntValue operator|(const IntValue &value) const
        {
            return IntValue(m_value | value.m_value);
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> &operator^=(
          const T &value)
        {
            m_value ^= static_cast<IntType>(value);
            return *this;
        }

        IntValue &operator^=(const IntValue &value)
        {
            m_value ^= value.m_value;
            return *this;
        }

        template<typename T>
        std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, IntValue> operator^(
          const T &value) const
        {
            return IntValue(m_value ^ static_cast<IntType>(value));
        }

        IntValue operator^(const IntValue &value) const
        {
            return IntValue(m_value ^ value.m_value);
        }
    };

    template<typename T>
    struct is_AbstractValue_constructible<
      T,
      std::enable_if_t<!std::is_same_v<bool, T> && std::is_integral_v<T>>>
    {
        constexpr static bool value = true;

        static AbstractValue::Ptr toValue(const T &value)
        {
            return AbstractValue::Ptr(new IntValue(value));
        }

        static std::optional<T> fromValue(const AbstractValue::Ptr &value)
        {
            if(value->isType(ValueType::Integer))
                return static_cast<T>(static_cast<const IntValue &>(*value));

            return std::nullopt;
        }
    };
} // namespace FDVar

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator==(
  const T &value, const FDVar::IntValue &other)
{
    return other == value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator!=(
  const T &value, const FDVar::IntValue &other)
{
    return other != value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<=(
  const T &value, const FDVar::IntValue &other)
{
    return value <= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator<(
  const T &value, const FDVar::IntValue &other)
{
    return value < static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>=(
  const T &value, const FDVar::IntValue &other)
{
    return value >= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> operator>(
  const T &value, const FDVar::IntValue &other)
{
    return value > static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator+=(
  T &value, const FDVar::IntValue &other)
{
    return value += static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator-=(
  T &value, const FDVar::IntValue &other)
{
    return value -= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator+(
  const T &value, const FDVar::IntValue &other)
{
    return value + static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator-(
  const T &value, const FDVar::IntValue &other)
{
    return value - static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator*=(
  T &value, const FDVar::IntValue &other)
{
    return value *= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator/=(
  T &value, const FDVar::IntValue &other)
{
    return value /= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator*(
  const T &value, const FDVar::IntValue &other)
{
    return value * static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator/(
  const T &value, const FDVar::IntValue &other)
{
    return value / static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator%=(
  T &value, const FDVar::IntValue &other)
{
    return value %= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator%(
  const T &value, const FDVar::IntValue &other)
{
    return value % static_cast<T>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<=(const T &value, const FDVar::IntValue &other)
{
    return value <<= static_cast<const FDVar::IntValue::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<(const T &value, const FDVar::IntValue &other)
{
    return value << static_cast<const FDVar::IntValue::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>=(const T &value, FDVar::IntValue &other)
{

    return value >>= static_cast<const FDVar::IntValue::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>(const T &value, FDVar::IntValue &other)
{

    return value >> static_cast<const FDVar::IntValue::IntType &>(other);
}

template<typename StreamType>
std::enable_if_t<!std::is_integral_v<StreamType>, StreamType> &operator<<(
  StreamType &stream, const FDVar::IntValue &value)
{
    stream << static_cast<const FDVar::IntValue::IntType &>(value);
    return stream;
}

template<typename StreamType>
std::enable_if_t<!std::is_integral_v<StreamType>, StreamType> &operator>>(StreamType &stream,
                                                                          FDVar::IntValue &value)
{
    FDVar::IntValue::IntType tmp;
    stream >> tmp;
    value = tmp;
    return stream;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator&=(
  T &value, FDVar::IntValue &other)
{
    return value &= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator&(
  const T &value, FDVar::IntValue &other)
{
    return value & static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator|=(
  T &value, FDVar::IntValue &other)
{
    return value |= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator|(
  const T &value, FDVar::IntValue &other)
{
    return value | static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator^=(
  T &value, FDVar::IntValue &other)
{
    return value ^= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator^(
  const T &value, FDVar::IntValue &other)
{
    return value ^ static_cast<T>(other);
}

#endif // FDVAR_INTVALUE_H
