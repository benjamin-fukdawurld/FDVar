#ifndef FDVAR_DYNAMICVARIABLE_BOOLVALUE_H
#define FDVAR_DYNAMICVARIABLE_BOOLVALUE_H

#include <FDVar/AbstractValue.h>

#include <optional>

namespace FDVar
{
    class BoolValue : public AbstractValue
    {
      private:
        bool m_value;

      public:
        BoolValue() : BoolValue(false) {}
        explicit BoolValue(bool value) : m_value(value) {}

        BoolValue(BoolValue &&) = default;
        BoolValue(const BoolValue &) = default;
        ~BoolValue() override = default;

        ValueType getValueType() const override { return ValueType::Boolean; }

        BoolValue &operator=(bool value)
        {
            m_value = value;
            return *this;
        }

        BoolValue &operator=(BoolValue &&) = default;
        BoolValue &operator=(const BoolValue &) = default;

        explicit operator bool() const { return m_value; }

        BoolValue operator!() const { return BoolValue(!m_value); }

        bool operator==(bool other) const { return m_value == other; }
        bool operator==(const BoolValue &other) const { return m_value == other.m_value; }

        bool operator!=(bool other) const { return m_value != other; }
        bool operator!=(const BoolValue &other) const { return m_value != other.m_value; }

        bool operator&&(bool other) const { return m_value && other; }
        bool operator&&(const BoolValue &other) const { return m_value && other.m_value; }

        bool operator||(bool other) const { return m_value || other; }
        bool operator||(const BoolValue &other) const { return m_value || other.m_value; }

        BoolValue &operator^=(bool other)
        {
            m_value ^= static_cast<int>(other);
            return *this;
        }

        bool operator^(bool other) const { return m_value ^ other; }

        BoolValue &operator^=(const BoolValue &other)
        {
            m_value ^= static_cast<int>(other.m_value);
            return *this;
        }

        BoolValue operator^(const BoolValue &other) const
        {
            return BoolValue(m_value ^ other.m_value);
        }
    };

    template<>
    struct is_AbstractValue_constructible<bool>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(std::enable_if_t<std::is_same_v<bool, T>, T> value)
    {
        return AbstractValue::Ptr(new BoolValue(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_same_v<bool, T>, T>> fromAbstractValuePtr(
      const AbstractValue::Ptr &value)
    {
        if(value->isType(ValueType::Boolean))
        {
            return static_cast<T>(static_cast<const BoolValue &>(*value));
        }

        return std::nullopt;
    }

} // namespace FDVar

inline bool operator==(bool a, const FDVar::BoolValue &b) { return b == a; }

inline bool operator!=(bool a, const FDVar::BoolValue &b) { return b != a; }

inline bool operator&&(bool a, const FDVar::BoolValue &b) { return b && a; }

inline bool operator||(bool a, const FDVar::BoolValue &b) { return b || a; }

inline bool operator^(bool a, const FDVar::BoolValue &b) { return b ^ a; }

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDVar::BoolValue &value)
{
    stream << static_cast<bool>(value);
    return stream;
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDVar::BoolValue &value)
{
    bool tmp = 0;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDVAR_DYNAMICVARIABLE_BOOLVALUE_H
