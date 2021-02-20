#ifndef FDVAR_STRINGVALUE_H
#define FDVAR_STRINGVALUE_H

#ifndef FDVAR_STRING_TYPE
    #include <string>
    #include <string_view>
    #ifndef FDVAR_USE_WIDE_STRING
        #define FDVAR_STRING_TYPE std::string
        #define FDVAR_STRING_VIEW_TYPE std::string_view
    #else
        #define FDVAR_STRING_TYPE std::wstring
        #define FDVAR_STRING_VIEW_TYPE std::wstring_view
    #endif // FDVAR_USE_WIDE_STRING
#endif     // FDVAR_STRING_TYPE

#include <FDVar/AbstractValue.h>
#include <utility>

namespace FDVar
{
    class StringValue : public AbstractValue
    {
      public:
        typedef FDVAR_STRING_TYPE StringType;
        typedef FDVAR_STRING_VIEW_TYPE StringViewType;
        typedef size_t SizeType;

      private:
        StringType m_value;

      public:
        StringValue() = default;
        StringValue(StringValue &&) = default;
        StringValue(const StringValue &) = default;
        explicit StringValue(StringViewType value) : m_value(value) {}

        ~StringValue() noexcept override = default;

        ValueType getValueType() const override { return ValueType::String; }

        StringValue &operator=(StringValue &&) = default;
        StringValue &operator=(const StringValue &) = default;

        explicit operator const StringType &() const { return m_value; }
        explicit operator StringViewType() const { return m_value; }

        StringValue &operator=(StringViewType value)
        {
            m_value = value;
            return *this;
        }

        bool operator==(const StringValue &value) const { return m_value == value.m_value; }

        bool operator==(StringViewType value) const { return m_value == value; }

        bool operator!=(const StringValue &value) const { return m_value != value.m_value; }

        bool operator!=(const StringType &value) const { return m_value != value; }

        StringValue &operator+=(StringViewType value)
        {
            m_value += value;
            return *this;
        }

        StringValue operator+(StringViewType value) const
        {
            return StringValue(m_value + value.data());
        }

        SizeType size() const { return m_value.size(); }
        bool isEmpty() const { return m_value.empty(); }

        StringType::value_type &operator[](size_t pos) { return m_value[pos]; }

        const StringType::value_type &operator[](size_t pos) const { return m_value[pos]; }

        void clear() { m_value.clear(); }

        void append(StringViewType str) { m_value.append(str); }
        StringValue subString(SizeType from, SizeType count)
        {
            return StringValue(m_value.substr(from, count));
        }
    };

    template<>
    struct is_AbstractValue_constructible<StringValue::StringType>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<StringValue::StringType, T>, T> &value)
    {
        return AbstractValue::Ptr(new StringValue(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_same_v<StringValue::StringType, T>, T>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(value->isType(ValueType::String))
        {
            return static_cast<T>(static_cast<const StringValue &>(*value));
        }

        return std::nullopt;
    }

    template<>
    struct is_AbstractValue_constructible<StringValue::StringViewType>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<StringValue::StringViewType, T>, T> &value)
    {
        return AbstractValue::Ptr(new StringValue(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_same_v<StringValue::StringViewType, T>, T>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(value->isType(ValueType::String))
        {
            return static_cast<T>(static_cast<const StringValue &>(*value));
        }

        return std::nullopt;
    }
} // namespace FDVar

inline bool operator==(const FDVar::StringValue::StringType &value, const FDVar::StringValue &other)
{
    return value == static_cast<FDVar::StringValue::StringType>(other);
}

inline bool operator!=(const FDVar::StringValue::StringType &value, const FDVar::StringValue &other)
{
    return value == static_cast<FDVar::StringValue::StringType>(other);
}

inline FDVar::StringValue::StringType &operator+=(FDVar::StringValue::StringType &value,
                                                  const FDVar::StringValue &other)
{
    return value += static_cast<FDVar::StringValue::StringType>(other);
}

inline FDVar::StringValue::StringType operator+(const FDVar::StringValue::StringType &value,
                                                const FDVar::StringValue &other)
{
    return value + static_cast<FDVar::StringValue::StringType>(other);
}

template<typename StreamType>
StreamType &operator<<(StreamType &stream, const FDVar::StringValue &value)
{
    stream << static_cast<FDVar::StringValue::StringType>(value);
    return stream;
}

template<typename StreamType>
StreamType &operator>>(StreamType &stream, FDVar::StringValue &value)
{
    FDVar::StringValue::StringType tmp;
    stream >> tmp;
    value = tmp;
    return stream;
}

#endif // FDVAR_STRINGVALUE_H
