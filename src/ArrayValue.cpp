#include <FDVar/ArrayValue.h>

void FDVar::ArrayValue::insert(FDVar::AbstractValue::Ptr value, FDVar::ArrayValue::SizeType pos)
{
    auto where = m_values.begin();
    std::advance(where, pos);
    m_values.insert(where, std::move(value));
}

FDVar::AbstractValue::Ptr FDVar::ArrayValue::removeAt(FDVar::ArrayValue::SizeType pos)
{
    AbstractValue::Ptr result = m_values[pos];
    auto where = m_values.begin();
    std::advance(where, pos);
    m_values.erase(where);
    return result;
}

FDVar::AbstractValue::Ptr FDVar::ArrayValue::pop()
{
    FDVar::AbstractValue::Ptr result = m_values.back();
    m_values.pop_back();
    return result;
}
