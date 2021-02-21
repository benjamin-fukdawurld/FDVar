#ifndef FDVAR_DYNAMICVARIABLE_CTORS_H
#define FDVAR_DYNAMICVARIABLE_CTORS_H

#include <FDVar/DynamicVariable_fwd.h>
#include <FDVar/DynamicVariable_stl.h>

namespace FDVar
{
    template<typename T>
    DynamicVariable::DynamicVariable(const T &value,
                                     std::enable_if_t<is_DynamicVariable_constructible<T>::value,
                                                      is_DynamicVariable_constructible<T>>
                                     /*unused*/) :
        DynamicVariable(toDynamicVariable<T>(value))
    {
    }

    template<typename T, typename U>
    DynamicVariable::DynamicVariable(const T &value) : m_value(std::make_shared<T>(value))
    {
    }

    template<typename T, typename U>
    DynamicVariable::DynamicVariable(T &&value) :
        m_value(std::make_shared<T>(std::forward<T>(value)))
    {
    }

    DynamicVariable::DynamicVariable(StringViewType value) :
        m_value(std::make_shared<StringValue>(value))
    {
    }

    DynamicVariable::DynamicVariable(ArrayType &&value) :
        m_value(std::make_shared<ArrayValue>(std::move(value)))
    {
    }

    DynamicVariable::DynamicVariable(ObjectType &&value) :
        m_value(std::make_shared<ObjectValue>(std::move(value)))
    {
    }

    DynamicVariable::DynamicVariable(std::initializer_list<AbstractValue::Ptr> l) :
        m_value(std::make_shared<ArrayValue>(l))
    {
    }

    DynamicVariable::DynamicVariable(std::initializer_list<DynamicVariable> l) : DynamicVariable()
    {
        ArrayType arr(l.size());
        std::transform(l.begin(), l.end(), arr.begin(),
                       [](const DynamicVariable &var) { return var.m_value; });
        m_value = std::make_shared<ArrayValue>(std::move(arr));
    }

    DynamicVariable::DynamicVariable(
      std::initializer_list<std::pair<StringViewType, DynamicVariable>> l) :
        DynamicVariable()
    {
        ObjectValue obj;
        for(const auto &[key, value]: l)
        {
            obj.set(key, value.m_value);
        }

        m_value = std::make_shared<ObjectValue>(std::move(obj));
    }

    DynamicVariable::DynamicVariable(const FunctionType &value) :
        m_value(std::make_shared<FunctionValue>(wrapFunction(value)))
    {
    }

    template<typename T>
    std::enable_if_t<is_DynamicVariable_constructible<T>::value, DynamicVariable &>
      DynamicVariable::operator=(const T &value)
    {
        m_value = toAbstractValuePtr<T>(value);
        return *this;
    }

} // namespace FDVar

#endif // FDVAR_DYNAMICVARIABLE_CTORS_H
