#ifndef FDVAR_ABSTRACTOBJECTVALUE_H
#define FDVAR_ABSTRACTOBJECTVALUE_H

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
#include <FDVar/ArrayValue.h>

namespace FDVar
{
    class AbstractObjectValue : public AbstractValue
    {
      public:
        typedef FDVAR_STRING_TYPE StringType;
        typedef FDVAR_STRING_VIEW_TYPE StringViewType;

        AbstractObjectValue() = default;
        AbstractObjectValue(AbstractObjectValue &&) = default;
        AbstractObjectValue(const AbstractObjectValue &) = default;

        virtual ~AbstractObjectValue() = default;

        AbstractObjectValue &operator=(AbstractObjectValue &&) = default;
        AbstractObjectValue &operator=(const AbstractObjectValue &) = default;

        virtual AbstractValue::Ptr keys() const = 0;

        virtual AbstractValue::Ptr operator[](StringViewType member) = 0;
        virtual AbstractValue::Ptr operator[](StringViewType member) const = 0;

        virtual AbstractValue::Ptr get(StringViewType member) { return operator[](member); }
        virtual AbstractValue::Ptr get(StringViewType member) const { return operator[](member); }

        virtual void set(StringViewType key, AbstractValue::Ptr value) = 0;
        virtual void unset(StringViewType key) = 0;

        ValueType getValueType() const override { return ValueType::Object; }
    };
} // namespace FDVar

#endif // FDVAR_ABSTRACTOBJECTVALUE_H
