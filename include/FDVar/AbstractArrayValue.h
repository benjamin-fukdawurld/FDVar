#ifndef FDVAR_ABSTRACTARRAYVALUE_H
#define FDVAR_ABSTRACTARRAYVALUE_H

#include <FDVar/AbstractValue.h>

namespace FDVar
{
    class AbstractArrayValue : public AbstractValue
    {
      public:
        typedef size_t SizeType;


        AbstractArrayValue() = default;
        AbstractArrayValue(AbstractArrayValue &&) = default;
        AbstractArrayValue(const AbstractArrayValue &) = default;

        virtual ~AbstractArrayValue() = default;

        virtual SizeType size() const = 0;
        virtual bool isEmpty() const = 0;
        virtual AbstractValue::Ptr operator[](SizeType pos) = 0;
        virtual const AbstractValue::Ptr &operator[](SizeType pos) const = 0;

        virtual void push(AbstractValue::Ptr value) = 0;
        virtual AbstractValue::Ptr pop() = 0;

        virtual void insert(AbstractValue::Ptr value, SizeType pos) = 0;
        virtual AbstractValue::Ptr removeAt(SizeType pos) = 0;
        virtual void clear() = 0;

        ValueType getValueType() const override { return ValueType::Array; }
    };
} // namespace FDVar


#endif // FDVAR_ABSTRACTARRAYVALUE_H
