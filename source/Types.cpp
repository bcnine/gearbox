#include "Types.h"
#include <assert.h>

namespace gbox
{

size_t SizeOf (DataType type)
{
  switch (type)
  {
    case CharType:
    return sizeof(char);

    case UCharType:
    return sizeof(unsigned char);

    case ShortType:
    return sizeof(short);

    case UShortType:
    return sizeof(unsigned short);

    case IntType:
    return sizeof(int);

    case UIntType:
    return sizeof(unsigned int);

    case FloatType:
    return sizeof(float);

    case DoubleType:
    return sizeof(double);
  }

  assert(0);
  return 0;
}

};
