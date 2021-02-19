#ifndef FDVAR_VALUETYPE_H
#define FDVAR_VALUETYPE_H

#include <cstdint>
#include <string>

namespace FDVar
{
    enum class ValueType : uint8_t
    {
        None,
        Boolean,
        Integer,
        Float,
        String,
        Function,
        Array,
        Object
    };
} // namespace FDVar

namespace std
{
    inline string to_string(FDVar::ValueType type)
    {
        switch(type)
        {
            case FDVar::ValueType::None:
                return "None";

            case FDVar::ValueType::Boolean:
                return "Boolean";

            case FDVar::ValueType::Integer:
                return "Integer";

            case FDVar::ValueType::Float:
                return "Float";

            case FDVar::ValueType::String:
                return "String";

            case FDVar::ValueType::Function:
                return "Function";

            case FDVar::ValueType::Array:
                return "Array";

            case FDVar::ValueType::Object:
                return "Object";
        }
    }
} // namespace std

#endif // FDVAR_VALUETYPE_H
