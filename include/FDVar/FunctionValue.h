#ifndef FDVAR_FUNCTIONVALUE_H
#define FDVAR_FUNCTIONVALUE_H

#include <FDVar/AbstractArrayValue.h>
#include <FDVar/AbstractValue.h>

#include <functional>
#include <utility>

namespace FDVar
{
    class FunctionValue : public AbstractValue
    {
      public:
        typedef std::function<AbstractValue::Ptr(AbstractValue::Ptr)> FunctionType;

      private:
        FunctionType m_value;

      public:
        FunctionValue() = default;
        FunctionValue(FunctionValue &&) = default;
        FunctionValue(const FunctionValue &) = default;

        FunctionValue(FunctionType &&func) : m_value(std::move(func)) {}
        FunctionValue(const FunctionType &func) : m_value(func) {}

        ~FunctionValue() override = default;

        FunctionValue &operator=(FunctionValue &&) = default;
        FunctionValue &operator=(const FunctionValue &) = default;

        FunctionValue &operator=(FunctionType &&func)
        {
            m_value = std::move(func);
            return *this;
        }

        FunctionValue &operator=(const FunctionType &func)
        {
            m_value = func;
            return *this;
        }

        ValueType getValueType() const override { return ValueType::Function; }

        explicit operator FunctionType() const { return m_value; }
        explicit operator bool() const { return static_cast<bool>(m_value); }
        bool operator!() const { return !m_value; }


        AbstractValue::Ptr operator()(AbstractValue::Ptr args) const
        {
            return m_value(std::move(args));
        }
    };

    template<>
    struct is_AbstractValue_constructible<FunctionValue::FunctionType>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<FunctionValue::FunctionType, T>, T> &value)
    {
        return AbstractValue::Ptr(new FunctionValue(value));
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_same_v<FunctionValue::FunctionType, T>, T>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(value->isType(ValueType::Function))
        {
            return static_cast<T>(static_cast<const FunctionValue &>(*value));
        }

        return std::nullopt;
    }
} // namespace FDVar

#endif // FDVAR_FUNCTIONVALUE_H
