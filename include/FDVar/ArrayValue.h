#ifndef FDVAR_ARRAYVALUE_H
#define FDVAR_ARRAYVALUE_H

#ifndef FDVAR_CONTAINER_TYPE
    #include <vector>
    #define FDVAR_CONTAINER_TYPE std::vector
#endif // FDVAR_CONTAINER_TYPE

#include <iterator>
#include <optional>

#include <FDVar/AbstractArrayValue.h>

namespace FDVar
{
    class ArrayValue : public AbstractArrayValue
    {
      public:
        typedef FDVAR_CONTAINER_TYPE<AbstractValue::Ptr> ArrayType;

      private:
        ArrayType m_values;

      public:
        ArrayValue() = default;
        ArrayValue(ArrayValue &&) = default;
        ArrayValue(const ArrayValue &) = default;
        ArrayValue(ArrayType &&values) : m_values(std::move(values)) {}
        ArrayValue(const ArrayType &values) : m_values(values) {}

        ArrayValue(std::initializer_list<AbstractValue::Ptr> l) : m_values(l) {}

        ~ArrayValue() override = default;

        explicit operator const ArrayType &() const { return m_values; }

        SizeType size() const override { return m_values.size(); }
        bool isEmpty() const override { return m_values.empty(); }
        AbstractValue::Ptr operator[](SizeType pos) override { return m_values[pos]; }
        const AbstractValue::Ptr &operator[](SizeType pos) const override { return m_values[pos]; }

        void push(AbstractValue::Ptr value) override { m_values.push_back(std::move(value)); }
        AbstractValue::Ptr pop() override;
        void insert(AbstractValue::Ptr value, SizeType pos) override;
        AbstractValue::Ptr removeAt(SizeType pos) override;
        void clear() override { m_values.clear(); }
    };

    void ArrayValue::insert(AbstractValue::Ptr value, ArrayValue::SizeType pos)
    {
        auto where = m_values.begin();
        std::advance(where, pos);
        m_values.insert(where, std::move(value));
    }

    AbstractValue::Ptr ArrayValue::removeAt(ArrayValue::SizeType pos)
    {
        AbstractValue::Ptr result = m_values[pos];
        auto where = m_values.begin();
        std::advance(where, pos);
        m_values.erase(where);
        return result;
    }

    AbstractValue::Ptr ArrayValue::pop()
    {
        FDVar::AbstractValue::Ptr result = m_values.back();
        m_values.pop_back();
        return result;
    }

    template<>
    struct is_AbstractValue_constructible<ArrayValue::ArrayType>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<ArrayValue::ArrayType, T>, T> &value)
    {
        return AbstractValue::Ptr(new ArrayValue(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_same_v<ArrayValue::ArrayType, T>, T>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(value->isType(ValueType::Array))
        {
            T result;
            const auto &arr = static_cast<const AbstractArrayValue &>(*value);
            for(ArrayValue::SizeType i = 0, imax = arr.size(); i < imax; ++i)
            {
                result.emplace_back(arr[i]);
            }

            return result;
        }

        return std::nullopt;
    }
} // namespace FDVar


#endif // FDVAR_ARRAYVALUE_H
