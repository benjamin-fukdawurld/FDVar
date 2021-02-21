#ifndef FDVAR_DYNAMICVARIABLE_STL_H
#define FDVAR_DYNAMICVARIABLE_STL_H

#include <FDVar/AbstractValue_stl.h>
#include <FDVar/DynamicVariable_fwd.h>

namespace FDVar
{
    template<typename T>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<std::is_same_v<std::initializer_list<DynamicVariable>, T>, T> &value)
    {
        DynamicVariable var(ValueType::Array);
        for(auto &p: value)
        {
            var.push(p);
        }

        return var;
    }

    template<typename T>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<
        std::is_same_v<std::vector<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
          std::is_same_v<std::deque<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
          std::is_same_v<std::list<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
          std::is_same_v<std::forward_list<DynamicVariable, std::allocator<DynamicVariable>>, T>,
        T> &value)
    {
        DynamicVariable var(ValueType::Array);
        for(auto &p: value)
        {
            var.push(p);
        }

        return var;
    }

    template<typename T>
    std::optional<std::enable_if_t<
      std::is_same_v<std::vector<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
        std::is_same_v<std::deque<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
        std::is_same_v<std::list<DynamicVariable, std::allocator<DynamicVariable>>, T> ||
        std::is_same_v<std::forward_list<DynamicVariable, std::allocator<DynamicVariable>>, T>,
      T>>
      fromDynamicVariable(const DynamicVariable &value)
    {
        if(!value.isType(ValueType::Array))
        {
            return std::nullopt;
        }

        T result;
        for(ArrayValue::SizeType i = 0, imax = value.size(); i < imax; ++i)
        {
            result.push_back(value[i]);
        }

        return result;
    }

    template<typename T>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<
        std::is_same_v<std::initializer_list<std::pair<ObjectValue::StringType, DynamicVariable>>,
                       T>,
        T> &value)
    {
        DynamicVariable obj(ValueType::Object);
        for(auto &[key, val]: value)
        {
            obj.set(key, val);
        }

        return obj;
    }

    template<typename T>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<
        std::is_same_v<std::map<ObjectValue::StringType, DynamicVariable>, T> ||
          std::is_same_v<std::unordered_map<ObjectValue::StringType, DynamicVariable>, T>,
        T> &value)
    {
        DynamicVariable obj(ValueType::Object);
        for(auto &[key, val]: value)
        {
            obj.set(key, val);
        }

        return obj;
    }

    template<typename T>
    std::optional<std::enable_if_t<
      std::is_same_v<std::map<ObjectValue::StringType, DynamicVariable>, T> ||
        std::is_same_v<std::unordered_map<ObjectValue::StringType, DynamicVariable>, T>,
      T>>
      fromDynamicVariable(const DynamicVariable &value)
    {
        if(!value.isType(ValueType::Object))
        {
            return std::nullopt;
        }

        DynamicVariable keys = value.keys();
        T result;
        for(ArrayValue::SizeType i = 0, imax = keys.size(); i < imax; ++i)
        {
            auto key = static_cast<DynamicVariable::StringType>(keys[i]);
            result[key] = value[key];
        }

        return result;
    }

    template<typename T>
    DynamicVariable toDynamicVariable(const std::enable_if_t<is_DynamicVariable_constructible_v<T>,
                                                             std::initializer_list<T>> &value)
    {
        DynamicVariable var(ValueType::Array);
        for(auto &p: value)
        {
            var.push(p);
        }

        return var;
    }

    template<template<typename, typename> class ContainerType, typename T, typename AllocatorType>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<is_DynamicVariable_constructible_v<T>, ContainerType<T, AllocatorType>>
        &value)
    {
        DynamicVariable var(ValueType::Array);
        for(auto &p: value)
        {
            var.push(p);
        }

        return var;
    }

    template<template<typename, typename> class ContainerType, typename T, typename AllocatorType>
    std::optional<
      std::enable_if_t<is_DynamicVariable_constructible_v<T>, ContainerType<T, AllocatorType>>>
      fromDynamicVariable(const DynamicVariable &value)
    {
        if(!value.isType(ValueType::Array))
        {
            return std::nullopt;
        }

        ContainerType<T, AllocatorType> result;
        for(ArrayValue::SizeType i = 0, imax = value.size(); i < imax; ++i)
        {
            std::optional<T> current = fromDynamicVariable<T>(value[i]);
            if(!current.has_value())
            {
                return std::nullopt;
            }

            result.push_back(current.value);
        }

        return result;
    }

    template<typename T>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<is_DynamicVariable_constructible_v<T>,
                             std::initializer_list<std::pair<ObjectValue::StringType, T>>> &value)
    {
        DynamicVariable obj(ValueType::Object);
        for(auto &[key, val]: value)
        {
            obj.set(key, toDynamicVariable<T>(val));
        }

        return obj;
    }

    template<template<typename, typename, typename, typename> class ContainerType,
             typename Key,
             typename T,
             typename Compare,
             typename AllocatorType>
    DynamicVariable toDynamicVariable(
      const std::enable_if_t<is_DynamicVariable_constructible_v<T>,
                             ContainerType<Key, T, Compare, AllocatorType>> &value)
    {
        DynamicVariable obj(ValueType::Object);
        for(auto &[key, val]: value)
        {
            obj.set(key, toDynamicVariable<T>(val));
        }

        return obj;
    }

    template<template<typename, typename, typename, typename> class ContainerType,
             typename Key,
             typename T,
             typename Compare,
             typename AllocatorType>
    std::optional<std::enable_if_t<is_DynamicVariable_constructible_v<T>,
                                   ContainerType<Key, T, Compare, AllocatorType>>>
      fromDynamicVariable(const DynamicVariable &value)
    {
        if(!value.isType(ValueType::Object))
        {
            return std::nullopt;
        }

        DynamicVariable keys = value.keys();
        ContainerType<Key, T, Compare, AllocatorType> result;
        for(ArrayValue::SizeType i = 0, imax = keys.size(); i < imax; ++i)
        {
            auto key = static_cast<const DynamicVariable::StringType &>(keys[i]);
            T current = fromDynamicVariable<T>(value[key]);
            if(!current.has_value())
            {
                return std::nullopt;
            }

            result[key] = current.value;
        }

        return result;
    }
} // namespace FDVar

#endif // FDVAR_DYNAMICVARIABLE_STL_H
