#ifndef FDVAR_OBJECTVALUE_H
#define FDVAR_OBJECTVALUE_H

#ifndef FDVAR_MAP_TYPE
    #include <unordered_map>
    #define FDVAR_MAP_TYPE std::unordered_map
#endif // FDVAR_MAP_TYPE

#include <FDVar/AbstractObjectValue.h>
#include <FDVar/StringValue.h>

namespace FDVar
{
    class ObjectValue : public AbstractObjectValue
    {
      public:
        typedef FDVAR_MAP_TYPE<StringType, AbstractValue::Ptr> ObjectType;

      private:
        ObjectType m_values;

      public:
        ObjectValue() = default;
        ObjectValue(ObjectValue &&) = default;
        ObjectValue(const ObjectValue &) = default;

        ObjectValue(ObjectType &&values) : m_values(std::move(values)) {}
        ObjectValue(const ObjectType &values) : m_values(values) {}

        ~ObjectValue() override = default;

        ObjectValue &operator=(ObjectValue &&) = default;
        ObjectValue &operator=(const ObjectValue &) = default;

        ObjectValue &operator=(ObjectType &&values)
        {
            m_values = std::move(values);
            return *this;
        }

        ObjectValue &operator=(const ObjectType &values)
        {
            m_values = values;
            return *this;
        }

        AbstractValue::Ptr keys() const override
        {
            std::unique_ptr<ArrayValue> result(new ArrayValue());
            for(const auto &[key, val]: m_values)
            {
                result->push(AbstractValue::Ptr(new StringValue(key)));
            }

            return AbstractValue::Ptr(result.release());
        }

        explicit operator const ObjectType &() const { return m_values; }

        AbstractValue::Ptr operator[](StringViewType member) override
        {
            auto it = m_values.find(StringType(member));
            if(it == m_values.end())
            {
                return AbstractValue::Ptr();
            }

            return it->second;
        }

        AbstractValue::Ptr operator[](StringViewType member) const override
        {
            auto it = m_values.find(StringType(member));
            if(it == m_values.end())
            {
                return AbstractValue::Ptr();
            }

            return it->second;
        }

        void set(StringViewType key, AbstractValue::Ptr value) override
        {
            m_values[StringType(key)] = value;
        }

        void unset(StringViewType key) override { m_values.erase(StringType(key)); }
    };
} // namespace FDVar

#endif // FDVAR_OBJECTVALUE_H
