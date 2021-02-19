#include <FDVar/DynamicVariable.h>
#include <utility>

using namespace FDVar;

DynamicVariable::DynamicVariable() {}


DynamicVariable::DynamicVariable(ValueType type)
{
    switch(type)
    {
        case ValueType::Boolean:
            m_value = std::make_shared<BoolValue>();
            break;

        case ValueType::Integer:
            m_value = std::make_shared<IntValue>();
            break;

        case ValueType::Float:
            m_value = std::make_shared<FloatValue>();
            break;

        case ValueType::String:
            m_value = std::make_shared<StringValue>();
            break;

        case ValueType::Array:
            m_value = std::make_shared<ArrayValue>();
            break;

        case ValueType::Object:
            m_value = std::make_shared<ObjectValue>();
            break;

        case ValueType::Function:
            m_value = std::make_shared<FunctionValue>();
            break;

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable::DynamicVariable(const DynamicVariable &other)
{
    switch(other.getValueType())
    {
        case ValueType::Boolean:
            m_value.reset(new BoolValue(other.toBoolean()));
            break;

        case ValueType::Integer:
            m_value.reset(new IntValue(other.toInteger()));
            break;

        case ValueType::Float:
            m_value.reset(new FloatValue(other.toFloat()));
            break;

        case ValueType::String:
            m_value.reset(new StringValue(other.toString()));
            break;

        default:
            m_value = other.m_value;
            break;
    }
}

DynamicVariable::DynamicVariable(const AbstractValue::Ptr &value) : m_value(value) {}

DynamicVariable::DynamicVariable(AbstractValue::Ptr &&value) : m_value(std::move(value)) {}

DynamicVariable &DynamicVariable::operator=(StringViewType str)
{
    m_value = std::make_shared<StringValue>(str);
    return *this;
}

DynamicVariable &DynamicVariable::operator=(ArrayType &&arr)
{
    m_value = std::make_shared<ArrayValue>(std::move(arr));
    return *this;
}

DynamicVariable &DynamicVariable::operator=(const ArrayType &arr)
{
    m_value = std::make_shared<ArrayValue>(arr);
    return *this;
}

DynamicVariable::operator bool() const
{
    if(!isType(ValueType::Boolean))
    {
        throw generateCastException(__func__);
    }

    return static_cast<bool>(toBoolean());
}

DynamicVariable::operator const StringType &() const
{
    if(!isType(ValueType::String))
    {
        throw generateCastException(__func__);
    }

    return static_cast<const StringType &>(toString());
}

DynamicVariable::operator const ArrayType &() const
{
    if(!isType(ValueType::Array))
    {
        throw generateCastException(__func__);
    }

    return static_cast<const ArrayType &>(static_cast<const ArrayValue &>(toArray()));
}

DynamicVariable::operator StringType() const
{
    if(!isType(ValueType::String))
    {
        throw generateCastException(__func__);
    }

    return static_cast<StringType>(toString());
}

DynamicVariable::operator ArrayType() const
{
    if(!isType(ValueType::Array))
    {
        throw generateCastException(__func__);
    }

    return static_cast<ArrayType>(static_cast<const ArrayValue &>(toArray()));
}

DynamicVariable::operator ObjectType() const
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return static_cast<ObjectType>(static_cast<const ObjectValue &>(toObject()));
}

DynamicVariable::operator const ObjectType &() const
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return static_cast<const ObjectType &>(static_cast<const ObjectValue &>(toObject()));
}


bool DynamicVariable::operator==(const DynamicVariable &value) const
{
    ValueType type = getValueType();
    if(type != value.getValueType())
    {
        return false;
    }

    switch(type)
    {
        case ValueType::None:
            return true;

        case ValueType::Boolean:
            return toBoolean() == value.toBoolean();

        case ValueType::Integer:
            return toInteger() == value.toInteger();

        case ValueType::Float:
            return toFloat() == value.toFloat();

        case ValueType::String:
            return toString() == value.toString();

        default:
            throw generateCastException(__func__);
    }
}

bool DynamicVariable::operator!=(const DynamicVariable &value) const
{
    ValueType type = getValueType();
    if(type != value.getValueType())
    {
        return true;
    }

    switch(type)
    {
        case ValueType::None:
            return false;

        case ValueType::Boolean:
            return toBoolean() != value.toBoolean();

        case ValueType::Integer:
            return toInteger() != value.toInteger();

        case ValueType::Float:
            return toFloat() != value.toFloat();

        case ValueType::String:
            return toString() != value.toString();

        default:
            throw generateCastException(__func__);
    }
}

bool DynamicVariable::operator==(std::nullptr_t) const { return isType(ValueType::None); }

bool DynamicVariable::operator!=(std::nullptr_t) const { return !isType(ValueType::None); }

bool DynamicVariable::operator==(bool value) const
{
    return isType(ValueType::Boolean) && toBoolean() == value;
}

bool DynamicVariable::operator!=(bool value) const
{
    return !isType(ValueType::Boolean) || toBoolean() != value;
}

bool DynamicVariable::operator==(StringViewType value) const
{
    return isType(ValueType::String) && toString() == value;
}

bool DynamicVariable::operator!=(StringViewType value) const
{
    return !isType(ValueType::String) || !(toString() == value);
}

DynamicVariable DynamicVariable::operator-() const
{
    if(isType(ValueType::Integer))
    {
        return DynamicVariable(-toInteger());
    }

    if(isType(ValueType::Float))
    {
        return DynamicVariable(-toFloat());
    }

    throw generateCastException(__func__);
}

DynamicVariable DynamicVariable::operator~() const
{
    if(!isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    return DynamicVariable(~toInteger());
}

DynamicVariable DynamicVariable::operator+() const
{
    if(isType(ValueType::Integer))
    {
        return DynamicVariable(+toInteger());
    }

    if(isType(ValueType::Float))
    {
        return DynamicVariable(+toFloat());
    }

    throw generateCastException(__func__);
}

DynamicVariable &DynamicVariable::operator++()
{
    if(!isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    ++toInteger();
    return *this;
}

DynamicVariable DynamicVariable::operator++(int)
{
    if(!isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    return DynamicVariable(toInteger()++);
}

DynamicVariable &DynamicVariable::operator--()
{
    if(!isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    --toInteger();
    return *this;
}

DynamicVariable DynamicVariable::operator--(int)
{
    if(!isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    return DynamicVariable(toInteger()--);
}

DynamicVariable &DynamicVariable::operator+=(StringViewType value)
{
    if(!isType(ValueType::String))
    {
        throw generateCastException(__func__);
    }

    toString() += value;
    return *this;
}

DynamicVariable &DynamicVariable::operator+=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this += static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this += static_cast<FloatType>(value.toFloat());

        case ValueType::String:
            return *this += static_cast<StringType>(value.toString());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable &DynamicVariable::operator-=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this -= static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this -= static_cast<FloatType>(value.toFloat());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable DynamicVariable::operator+(StringViewType value) const
{
    if(!isType(ValueType::String))
    {
        throw generateCastException(__func__);
    }

    return toString() + value;
}

DynamicVariable DynamicVariable::operator+(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this + static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this + static_cast<FloatType>(value.toFloat());

        case ValueType::String:
            return *this + static_cast<StringType>(value.toString());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable DynamicVariable::operator-(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this - static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this - static_cast<FloatType>(value.toFloat());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable &DynamicVariable::operator*=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this *= static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this *= static_cast<FloatType>(value.toFloat());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable DynamicVariable::operator*(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this * static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this * static_cast<FloatType>(value.toFloat());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable &DynamicVariable::operator/=(const DynamicVariable &value)
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this /= static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this /= static_cast<FloatType>(value.toFloat());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable DynamicVariable::operator/(const DynamicVariable &value) const
{
    switch(value.getValueType())
    {
        case ValueType::Integer:
            return *this / static_cast<IntType>(value.toInteger());

        case ValueType::Float:
            return *this / static_cast<FloatType>(value.toFloat());

        default:
            throw generateCastException(__func__);
    }
}

DynamicVariable &DynamicVariable::operator%=(const DynamicVariable &value)
{
    if(!value.isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    return *this %= static_cast<IntType>(value.toInteger());
}

DynamicVariable DynamicVariable::operator%(const DynamicVariable &value) const
{
    if(!value.isType(ValueType::Integer))
    {
        throw generateCastException(__func__);
    }

    return *this % static_cast<IntType>(value.toInteger());
}

DynamicVariable::SizeType DynamicVariable::size() const
{
    if(isType(ValueType::Array))
    {
        return toArray().size();
    }

    if(isType(ValueType::String))
    {
        return toString().size();
    }

    throw generateCastException(__func__);
}

bool DynamicVariable::isEmpty() const
{
    if(isType(ValueType::Array))
    {
        return toArray().isEmpty();
    }

    if(isType(ValueType::String))
    {
        return toString().isEmpty();
    }

    throw generateCastException(__func__);
}


DynamicVariable DynamicVariable::operator[](DynamicVariable::SizeType pos)
{
    if(isType(ValueType::String))
    {
        return DynamicVariable(StringType(1, toString()[pos]));
    }

    if(isType(ValueType::Array))
    {
        return DynamicVariable(toArray()[pos]);
    }

    throw generateCastException(__func__);
}


DynamicVariable DynamicVariable::operator[](StringViewType member)
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return toObject()[member];
}

DynamicVariable DynamicVariable::keys()
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return toObject().keys();
}

DynamicVariable DynamicVariable::get(StringViewType member)
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return toObject().get(member);
}

void DynamicVariable::set(StringViewType key, const DynamicVariable &value)
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return toObject().set(key, value.m_value);
}
void DynamicVariable::unset(StringViewType key)
{
    if(!isType(ValueType::Object))
    {
        throw generateCastException(__func__);
    }

    return toObject().unset(key);
}

void DynamicVariable::push(const DynamicVariable &value) { toArray().push(value.m_value); }

DynamicVariable DynamicVariable::pop() { return toArray().pop(); }

void DynamicVariable::insert(const DynamicVariable &value, DynamicVariable::SizeType pos)
{
    toArray().insert(value.m_value, pos);
}

DynamicVariable DynamicVariable::removeAt(DynamicVariable::SizeType pos)
{
    return toArray().removeAt(pos);
}

void DynamicVariable::clear()
{
    if(isType(ValueType::Array))
    {
        toArray().clear();
    }
    else if(isType(ValueType::String))
    {
        toString().clear();
    }
    else
    {
        throw generateCastException(__func__);
    }
}

void DynamicVariable::append(StringViewType str) { toString().append(str); }

DynamicVariable DynamicVariable::subString(DynamicVariable::SizeType from,
                                           DynamicVariable::SizeType count)
{
    return toString().subString(from, count);
}
