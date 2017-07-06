#ifndef DATAUTILSINL
#define DATAUTILSINL

#include "structures.h"

#include <QDebug>
#include <memory>


namespace PlaygroundLinesDataInl
{

inline bool getPos(unsigned char x, unsigned char y, unsigned int &i, unsigned int &j)
{
    if (x >= PlaygroundLinesDataDefines::LinesCount || y >= PlaygroundLinesDataDefines::LineLength)
    {
        qWarning() << "CPlaygroundLinesData::getPos: index out of range - " << x << ", " << y;
        return false;
    }

    const unsigned int z = x * PlaygroundLinesDataDefines::LineLength + y;

    i = z / PlaygroundLinesDataDefines::ItemsPerByte;
    j = z % PlaygroundLinesDataDefines::ItemsPerByte;

    return true;
}

inline void setRawByteValue(PlaygroundLinesData *data, unsigned int index, unsigned char value)
{
    Q_CHECK_PTR(data);

    if (index < PlaygroundLinesDataDefines::ArraySize)
    {
        data->lines[index] = value;
    }
    else
    {
        qWarning() << "CPlaygroundLinesData::setRawByteValue: index out of range - " << "max " << PlaygroundLinesDataDefines::ArraySize << ", index " << index;
    }
}

inline unsigned char rawByteValue(PlaygroundLinesData *data, unsigned int index)
{
    Q_CHECK_PTR(data);

    unsigned char value = 0;

    if (index < PlaygroundLinesDataDefines::ArraySize)
    {
        value = data->lines[index];
    }
    else
    {
        qWarning() << "CPlaygroundLinesData::rawByteValue: index out of range - " << "max " << PlaygroundLinesDataDefines::ArraySize << ", index " << index;
    }

    return value;
}

inline unsigned char mask(unsigned char valueIndex)
{
    unsigned char mask = 0;

    if (valueIndex < PlaygroundLinesDataDefines::ItemsPerByte)
    {
        mask = (0xFF >> (8 - PlaygroundLinesDataDefines::ItemBitSize)) << (PlaygroundLinesDataDefines::ItemBitSize * valueIndex);
    }
    else
    {
        qWarning() << "CPlaygroundLinesData::mask: " << "valueIndex out of range - " << "max " << PlaygroundLinesDataDefines::ItemsPerByte << ", index " << valueIndex;
    }

    return mask;
}

inline unsigned char byteItemValue(unsigned char byte, unsigned char itemIndex)
{
    const unsigned char valueByteMask = mask(itemIndex);

    byte = byte & valueByteMask;
    byte = byte >> (itemIndex * PlaygroundLinesDataDefines::ItemBitSize);

    return byte;
}

inline unsigned char setByteItemValue(unsigned char byte, unsigned char itemValue, unsigned char itemIndex)
{
    const unsigned char valueByteMask = mask(itemIndex);
    const unsigned char newValueShifted = (itemValue & ~(0xFF << PlaygroundLinesDataDefines::ItemBitSize)) << (itemIndex * PlaygroundLinesDataDefines::ItemBitSize);

    byte = byte & ~valueByteMask;
    byte = byte | newValueShifted;

    return byte;
}

inline unsigned char value(PlaygroundLinesData *data, unsigned char x, unsigned char y)
{
    Q_CHECK_PTR(data);

    unsigned char value = 0;

    unsigned int i = 0, j = 0;
    bool bRes = getPos(x, y, i, j);

    if (bRes)
    {
        const unsigned char itemRawData = rawByteValue(data, i);

        value = byteItemValue(itemRawData, j);
    }

    return value;
}

inline void setValue(PlaygroundLinesData *data, unsigned char x, unsigned char y, unsigned char value)
{
    Q_CHECK_PTR(data);

    unsigned int i = 0, j = 0;
    bool bRes = getPos(x, y, i, j);

    if (bRes)
    {
        const unsigned char itemRawData = rawByteValue(data, i);
        const unsigned char newItemRawData = setByteItemValue(itemRawData, value, j);

        setRawByteValue(data, i, newItemRawData);
    }
}


}


#endif // DATAUTILSINL

