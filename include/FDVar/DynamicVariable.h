#ifndef FDVAR_DYNAMICVARIABLE_H
#define FDVAR_DYNAMICVARIABLE_H

#include <math.h>

#include <FDVar/DynamicVariable_ctors.h>
#include <FDVar/DynamicVariable_fwd.h>
#include <FDVar/DynamicVariable_stl.h>

namespace FDVar
{
    template<typename T>
    void DynamicVariable::convert(
      std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &result) const
    {
        if(isType(ValueType::Integer))
        {
            result = static_cast<T>(toInteger());
        }
        else if(isType(ValueType::Float))
        {
            result = static_cast<T>(toFloat());
        }
        else
        {
            throw generateCastException(__func__);
        }
    }

    template<typename T>
    void DynamicVariable::convert(std::enable_if_t<std::is_floating_point_v<T>, T> &result) const
    {
        if(isType(ValueType::Integer))
        {
            result = static_cast<T>(static_cast<IntType>(toInteger()));
        }
        else if(isType(ValueType::Float))
        {
            result = static_cast<T>(toFloat());
        }
        else
        {
            throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator==(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return toInteger() == value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() == value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator==(const T &value) const
    {
        if(isType(ValueType::Float))
        {
            return toFloat() == value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator!=(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return toInteger() != value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() != value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator!=(const T &value) const
    {
        if(isType(ValueType::Float))
        {
            return toFloat() != value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator<=(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return toInteger() <= value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() <= value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator<=(const T &value) const
    {
        if(isType(ValueType::Float))
        {
            return toFloat() <= value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator<(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return toInteger() < value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() < value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator<(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return static_cast<IntType>(toInteger()) < value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() < value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator>=(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return toInteger() >= value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() >= value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator>=(const T &value) const
    {
        if(isType(ValueType::Float))
        {
            return toFloat() >= value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, bool> DynamicVariable::
      operator>(const T &value) const
    {
        if(isType(ValueType::Integer))
        {
            return toInteger() > value;
        }

        if(isType(ValueType::Float))
        {
            return toFloat() > value;
        }

        throw generateCastException(__func__);
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, bool>
      DynamicVariable::operator>(const T &value) const
    {
        if(!isType(ValueType::Float))
        {
            throw generateCastException(__func__);
        }

        return toFloat() > value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator+=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() += value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() += static_cast<FloatType>(value);
                return *this;
            }

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator+=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FloatValue(static_cast<IntType>(toInteger()) + value);
                return *this;

            case ValueType::Float:
                toFloat() += value;
                return *this;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator-=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() -= value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() -= static_cast<FloatType>(value);
                return *this;
            }

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator-=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FloatValue(static_cast<IntType>(toInteger()) - value);
                return *this;

            case ValueType::Float:
                toFloat() -= value;
                return *this;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator+(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() + value;
            case ValueType::Float:
                return toFloat() + static_cast<FloatType>(value);

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator+(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FloatValue(static_cast<IntType>(toInteger()) + value);

            case ValueType::Float:
                return toFloat() + value;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator-(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() - value;

            case ValueType::Float:
                return toFloat() - static_cast<FloatType>(value);

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator-(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FloatValue(static_cast<IntType>(toInteger()) - value);

            case ValueType::Float:
                return toFloat() - value;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator%=(const T &value)
    {
        if(!isType(ValueType::Integer))
        {
            throw generateCastException(__func__);
        }

        toInteger() %= value;
        return *this;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator%(const T &value) const
    {
        if(!isType(ValueType::Integer))
        {
            throw generateCastException(__func__);
        }

        return toInteger() % value;
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator*=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() *= value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() *= static_cast<FloatType>(value);
                return *this;
            }

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator*=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FloatValue(static_cast<IntType>(toInteger()) * value);
                return *this;

            case ValueType::Float:
                toFloat() *= value;
                return *this;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator*(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() * value;

            case ValueType::Float:
                return toFloat() * static_cast<FloatType>(value);

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator*(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FloatValue(static_cast<IntType>(toInteger()) * value);

            case ValueType::Float:
                return toFloat() * value;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      &DynamicVariable::operator/=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
            {
                toInteger() /= value;
                return *this;
            }

            case ValueType::Float:
            {
                toFloat() /= static_cast<FloatType>(value);
                return *this;
            }

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      &DynamicVariable::operator/=(const T &value)
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                *this = FloatValue(static_cast<IntType>(toInteger()) / value);
                return *this;

            case ValueType::Float:
                toFloat() /= value;
                return *this;

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, DynamicVariable>
      DynamicVariable::operator/(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return toInteger() / value;

            case ValueType::Float:
                return toFloat() / static_cast<FloatType>(value);

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename T>
    std::enable_if_t<!std::is_same_v<T, bool> && std::is_floating_point_v<T>, DynamicVariable>
      DynamicVariable::operator/(const T &value) const
    {
        switch(getValueType())
        {
            case ValueType::Integer:
                return FloatValue(static_cast<IntType>(toInteger()) / value);

            case ValueType::Float:
                return toFloat() / value;

            default:
                throw generateCastException(__func__);
        }
    }

    DynamicVariable operator""_var(unsigned long long value) { return DynamicVariable(value); }

    DynamicVariable operator""_var(long double value) { return DynamicVariable(value); }

    DynamicVariable operator""_var(const DynamicVariable::StringType::value_type *value,
                                   size_t size)
    {
        return DynamicVariable(DynamicVariable::StringType(value, size));
    }

    template<typename StreamType, typename U>
    void DynamicVariable::read(StreamType &stream)
    {
        switch(getValueType())
        {
            case ValueType::Boolean:
            {
                bool tmp = 0;
                stream >> tmp;
                *this = tmp;
                break;
            }

            case ValueType::Integer:
            {
                DynamicVariable::IntType tmp = 0;
                stream >> tmp;
                *this = tmp;
                break;
            }

            case ValueType::Float:
            {
                DynamicVariable::FloatType tmp = NAN;
                stream >> tmp;
                *this = tmp;
                break;
            }

            default:
                throw generateCastException(__func__);
        }
    }

    template<typename StreamType, typename U>
    void DynamicVariable::write(StreamType &stream) const
    {
        switch(getValueType())
        {
            case ValueType::Boolean:
                operator<<(stream, toBoolean());
                break;

            case ValueType::Integer:
                ::operator<<(stream, toInteger());
                break;

            case ValueType::Float:
                ::operator<<(stream, toFloat());
                break;

            default:
                throw generateCastException(__func__);
        }
    }

} // namespace FDVar



template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator==(
  const T &value, const FDVar::DynamicVariable &other)
{
    return other == value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator!=(
  const T &value, const FDVar::DynamicVariable &other)
{
    return other != value;
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator<=(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value <= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator<(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value < static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator>=(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value >= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, bool> operator>(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value > static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator+=(
  T &value, const FDVar::DynamicVariable &other)
{
    return value += static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator-=(
  T &value, const FDVar::DynamicVariable &other)
{
    return value -= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> operator+(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value + static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> operator-(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value - static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator*=(
  T &value, const FDVar::DynamicVariable &other)
{
    return value *= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> &operator/=(
  T &value, const FDVar::DynamicVariable &other)
{
    return value /= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> operator*(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value * static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_arithmetic_v<T>, T> operator/(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value / static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator%=(
  T &value, const FDVar::DynamicVariable &other)
{
    return value %= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator%(
  const T &value, const FDVar::DynamicVariable &other)
{
    return value % static_cast<T>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<=(const T &value,
                                                       const FDVar::DynamicVariable &other)
{
    return value <<= static_cast<const FDVar::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> operator<<(const T &value,
                                                      const FDVar::DynamicVariable &other)
{
    return value << static_cast<const FDVar::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>=(const T &value,
                                                        FDVar::DynamicVariable &other)
{

    return value >>= static_cast<const FDVar::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> &operator>>(const T &value,
                                                       FDVar::DynamicVariable &other)
{

    return value >> static_cast<const FDVar::DynamicVariable::IntType &>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator&=(
  T &value, FDVar::DynamicVariable &other)
{
    return value &= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator&(
  const T &value, FDVar::DynamicVariable &other)
{
    return value & static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator|=(
  T &value, FDVar::DynamicVariable &other)
{
    return value |= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator|(
  const T &value, FDVar::DynamicVariable &other)
{
    return value | static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> &operator^=(
  T &value, FDVar::DynamicVariable &other)
{
    return value ^= static_cast<T>(other);
}

template<typename T>
std::enable_if_t<!std::is_same_v<T, bool> && std::is_integral_v<T>, T> operator^(
  const T &value, FDVar::DynamicVariable &other)
{
    return value ^ static_cast<T>(other);
}

template<typename StreamType>
std::enable_if_t<!std::is_integral_v<StreamType> &&
                   !std::is_same_v<FDVar::DynamicVariable, StreamType>,
                 StreamType>
  &operator<<(StreamType &stream, const FDVar::DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case FDVar::ValueType::Boolean:
            stream << static_cast<bool>(value);
            break;

        case FDVar::ValueType::Integer:
            stream << static_cast<FDVar::DynamicVariable::IntType>(value);
            break;

        case FDVar::ValueType::Float:
            stream << static_cast<FDVar::DynamicVariable::FloatType>(value);
            break;

        case FDVar::ValueType::String:
            stream << static_cast<const FDVar::DynamicVariable::StringType &>(value);
            break;

        default:
            break;
    }

    return stream;
}

template<typename StreamType>
std::enable_if_t<!std::is_integral_v<StreamType> &&
                   !std::is_same_v<FDVar::DynamicVariable, StreamType>,
                 StreamType>
  &operator>>(StreamType &stream, FDVar::DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case FDVar::ValueType::Boolean:
        {
            bool tmp = 0;
            stream >> tmp;
            value = tmp;
            break;
        }

        case FDVar::ValueType::Integer:
        {
            FDVar::DynamicVariable::IntType tmp = 0;
            stream >> tmp;
            value = tmp;
            break;
        }

        case FDVar::ValueType::Float:
        {
            FDVar::DynamicVariable::FloatType tmp = NAN;
            stream >> tmp;
            value = tmp;
            break;
        }

        case FDVar::ValueType::String:
        {
            FDVar::DynamicVariable::StringType tmp;
            stream >> tmp;
            value = tmp;
            break;
        }

        default:
            break;
    }

    return stream;
}

#endif // FDVAR_DYNAMICVARIABLE_H
