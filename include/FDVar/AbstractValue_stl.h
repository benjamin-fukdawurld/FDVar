#ifndef FDVAR_ABSTRACTVALUE_STL_H
#define FDVAR_ABSTRACTVALUE_STL_H

#include <deque>
#include <forward_list>
#include <initializer_list>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

#include <FDVar/AbstractValue.h>
#include <FDVar/ArrayValue.h>
#include <FDVar/ObjectValue.h>

namespace FDVar
{
    template<typename T>
    struct is_AbstractValue_constructible<
      T,
      std::enable_if_t<std::is_same_v<std::initializer_list<AbstractValue::Ptr>, T>, T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<std::initializer_list<AbstractValue::Ptr>, T>, T>
        &value)
    {
        auto arr = std::make_unique<ArrayValue>();
        for(auto &p: value)
        {
            arr->push(p);
        }

        return AbstractValue::Ptr(arr.release());
    }

    template<typename T>
    struct is_AbstractValue_constructible<
      T,
      std::enable_if_t<std::is_same_v<std::vector<AbstractValue::Ptr>, T> ||
                         std::is_same_v<std::deque<AbstractValue::Ptr>, T> ||
                         std::is_same_v<std::list<AbstractValue::Ptr>, T> ||
                         std::is_same_v<std::forward_list<AbstractValue::Ptr>, T>,
                       T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<std::vector<AbstractValue::Ptr>, T> ||
                               std::is_same_v<std::deque<AbstractValue::Ptr>, T> ||
                               std::is_same_v<std::list<AbstractValue::Ptr>, T> ||
                               std::is_same_v<std::forward_list<AbstractValue::Ptr>, T>,
                             T> &value)
    {
        auto arr = std::make_unique<ArrayValue>();
        for(auto &p: value)
        {
            arr->push(p);
        }

        return AbstractValue::Ptr(arr.release());
    }

    template<typename T>
    std::optional<std::enable_if_t<std::is_same_v<std::vector<AbstractValue::Ptr>, T> ||
                                     std::is_same_v<std::deque<AbstractValue::Ptr>, T> ||
                                     std::is_same_v<std::list<AbstractValue::Ptr>, T> ||
                                     std::is_same_v<std::forward_list<AbstractValue::Ptr>, T>,
                                   T>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(!value->isType(ValueType::Array))
        {
            return std::nullopt;
        }

        const auto &arr = static_cast<const ArrayValue &>(*value);
        T result;
        for(ArrayValue::SizeType i = 0, imax = arr.size(); i < imax; ++i)
        {
            result.push_back(arr[i]);
        }

        return result;
    }

    template<typename T>
    struct is_AbstractValue_constructible<
      T,
      std::enable_if_t<std::is_same_v<std::initializer_list<
                                        std::pair<ObjectValue::StringType, AbstractValue::Ptr>>,
                                      T>,
                       T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<std::is_same_v<std::initializer_list<std::pair<ObjectValue::StringType,
                                                                            AbstractValue::Ptr>>,
                                            T>,
                             T> &value)
    {
        auto obj = std::make_unique<ObjectValue>();
        for(auto &[key, val]: value)
        {
            obj->set(key, val);
        }

        return AbstractValue::Ptr(obj.release());
    }

    template<typename T>
    struct is_AbstractValue_constructible<
      T,
      std::enable_if_t<
        std::is_same_v<std::map<ObjectValue::StringType, AbstractValue::Ptr>, T> ||
          std::is_same_v<std::unordered_map<ObjectValue::StringType, AbstractValue::Ptr>, T>,
        T>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<
        std::is_same_v<std::map<ObjectValue::StringType, AbstractValue::Ptr>, T> ||
          std::is_same_v<std::unordered_map<ObjectValue::StringType, AbstractValue::Ptr>, T>,
        T> &value)
    {
        auto obj = std::make_unique<ObjectValue>();
        for(auto &[key, val]: value)
        {
            obj->set(key, val);
        }

        return AbstractValue::Ptr(obj.release());
    }

    template<typename T>
    std::optional<std::enable_if_t<
      std::is_same_v<std::map<ObjectValue::StringType, AbstractValue::Ptr>, T> ||
        std::is_same_v<std::unordered_map<ObjectValue::StringType, AbstractValue::Ptr>, T>,
      T>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(!value->isType(ValueType::Object))
        {
            return std::nullopt;
        }

        const auto &obj = static_cast<const ObjectValue &>(*value);
        AbstractValue::Ptr keys = obj.keys();
        const auto &arr = static_cast<const AbstractArrayValue &>(*keys);
        T result;
        for(ArrayValue::SizeType i = 0, imax = arr.size(); i < imax; ++i)
        {
            auto key = static_cast<ObjectValue::StringType>(static_cast<StringValue &>(*(arr[i])));
            result[key] = obj[key];
        }

        return result;
    }

    template<typename T>
    struct is_AbstractValue_constructible<
      std::initializer_list<T>,
      std::enable_if_t<is_AbstractValue_constructible_v<T>, std::initializer_list<T>>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<is_AbstractValue_constructible_v<T>, std::initializer_list<T>> &value)
    {
        auto arr = std::make_unique<ArrayValue>();
        for(auto &p: value)
        {
            arr->push(p);
        }

        return AbstractValue::Ptr(arr.release());
    }

    template<template<typename, typename> class ContainerType, typename T, typename AllocatorType>
    struct is_AbstractValue_constructible<ContainerType<T, AllocatorType>,
                                          std::enable_if_t<is_AbstractValue_constructible_v<T>, T>>
    {
        constexpr static bool value = true;
    };

    template<template<typename, typename> class ContainerType, typename T, typename AllocatorType>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<is_AbstractValue_constructible_v<T>, ContainerType<T, AllocatorType>>
        &value)
    {
        auto arr = std::make_unique<ArrayValue>();
        for(auto &p: value)
        {
            arr->push(p);
        }

        return AbstractValue::Ptr(arr.release());
    }

    template<template<typename, typename> class ContainerType, typename T, typename AllocatorType>
    std::optional<
      std::enable_if_t<is_AbstractValue_constructible_v<T>, ContainerType<T, AllocatorType>>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(!value->isType(ValueType::Array))
        {
            return std::nullopt;
        }

        const auto &arr = static_cast<const ArrayValue &>(*value);
        ContainerType<T, AllocatorType> result;
        for(ArrayValue::SizeType i = 0, imax = arr.size(); i < imax; ++i)
        {
            std::optional<T> current = fromAbstractValuePtr<T>(arr[i]);
            if(!current.has_value())
            {
                return std::nullopt;
            }

            result.push_back(current.value);
        }

        return result;
    }

    template<typename T>
    struct is_AbstractValue_constructible<
      std::initializer_list<std::pair<ObjectValue::StringType, T>>,
      std::enable_if_t<is_AbstractValue_constructible_v<T>,
                       std::initializer_list<std::pair<ObjectValue::StringType, T>>>>
    {
        constexpr static bool value = true;
    };

    template<typename T>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<is_AbstractValue_constructible_v<T>,
                             std::initializer_list<std::pair<ObjectValue::StringType, T>>> &value)
    {
        auto obj = std::make_unique<ObjectValue>();
        for(auto &[key, val]: value)
        {
            obj->set(key, toAbstractValuePtr<T>(val));
        }

        return AbstractValue::Ptr(obj.release());
    }

    template<template<typename, typename, typename, typename> class ContainerType,
             typename Key,
             typename T,
             typename Compare,
             typename AllocatorType>
    struct is_AbstractValue_constructible<
      ContainerType<Key, T, Compare, AllocatorType>,
      std::enable_if_t<is_AbstractValue_constructible_v<T>,
                       ContainerType<Key, T, Compare, AllocatorType>>>
    {
        constexpr static bool value = true;
    };

    template<template<typename, typename, typename, typename> class ContainerType,
             typename Key,
             typename T,
             typename Compare,
             typename AllocatorType>
    AbstractValue::Ptr toAbstractValuePtr(
      const std::enable_if_t<is_AbstractValue_constructible_v<T>,
                             ContainerType<Key, T, Compare, AllocatorType>> &value)
    {
        auto obj = std::make_unique<ObjectValue>();
        for(auto &[key, val]: value)
        {
            obj->set(key, toAbstractValuePtr<T>(val));
        }

        return AbstractValue::Ptr(obj.release());
    }

    template<template<typename, typename, typename, typename> class ContainerType,
             typename Key,
             typename T,
             typename Compare,
             typename AllocatorType>
    std::optional<std::enable_if_t<is_AbstractValue_constructible_v<T>,
                                   ContainerType<Key, T, Compare, AllocatorType>>>
      fromAbstractValuePtr(const AbstractValue::Ptr &value)
    {
        if(!value->isType(ValueType::Object))
        {
            return std::nullopt;
        }

        const auto &obj = static_cast<const ObjectValue &>(*value);
        AbstractValue::Ptr keys = obj.keys();
        const auto &arr = static_cast<const AbstractArrayValue &>(*keys);
        ContainerType<Key, T, Compare, AllocatorType> result;
        for(ArrayValue::SizeType i = 0, imax = arr.size(); i < imax; ++i)
        {
            auto key = static_cast<ObjectValue::StringType>(static_cast<StringValue &>(*(arr[i])));
            T current = fromAbstractValuePtr<T>(obj[key]);
            if(!current.has_value())
            {
                return std::nullopt;
            }

            result[key] = current.value;
        }

        return result;
    }
} // namespace FDVar

#endif // FDVAR_ABSTRACTVALUE_H
