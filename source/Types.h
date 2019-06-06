#ifndef GBOXTYPES_H
#define GBOXTYPES_H

#include <cstddef>

namespace gbox
{

enum DataType
{
    CharType = 0x1400,
    UCharType = 0x1401,
    ShortType = 0x1402,
    UShortType = 0x1403,
    IntType = 0x1404,
    UIntType = 0x1405,
    FloatType = 0x1406,
    DoubleType = 0x140A
};

extern size_t SizeOf (DataType datatype);

enum PointerButton
{
    NoButton = 0,
    LeftButton,
    MiddleButton,
    RightButton,
    WheelUpButton,
    WheelDownButton
};

enum ButtonState
{
    ButtonUp,
    ButtonDown
};

};

#endif
