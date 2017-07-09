#include "datautils.h"

#include <memory>


bool CPlaygroundLinesData::getPos(unsigned char x, unsigned char y, unsigned int &i, unsigned int &j)
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

void CPlaygroundLinesData::setRawByteValue(PlaygroundLinesData *data, unsigned int index, unsigned char value)
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

unsigned char CPlaygroundLinesData::rawByteValue(PlaygroundLinesData *data, unsigned int index)
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

unsigned char CPlaygroundLinesData::mask(unsigned char valueIndex)
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


unsigned char CPlaygroundLinesData::value(PlaygroundLinesData *data, unsigned char x, unsigned char y)
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

void CPlaygroundLinesData::setValue(PlaygroundLinesData *data, unsigned char x, unsigned char y, unsigned char value)
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

unsigned char CPlaygroundLinesData::byteItemValue(unsigned char byte, unsigned char itemIndex)
{
    const unsigned char valueByteMask = mask(itemIndex);

    byte = byte & valueByteMask;
    byte = byte >> (itemIndex * PlaygroundLinesDataDefines::ItemBitSize);

    return byte;
}

unsigned char CPlaygroundLinesData::setByteItemValue(unsigned char byte, unsigned char itemValue, unsigned char itemIndex)
{
    const unsigned char valueByteMask = mask(itemIndex);
    const unsigned char newValueShifted = (itemValue & ~(0xFF << PlaygroundLinesDataDefines::ItemBitSize)) << (itemIndex * PlaygroundLinesDataDefines::ItemBitSize);

    byte = byte & ~valueByteMask;
    byte = byte | newValueShifted;

    return byte;
}


//CPlaygroundLinesData::CPlaygroundLinesData(PlaygroundLinesData *data)
//{
//    memset(&m_linesData, 0, sizeof(m_linesData));

//    if (data != 0)
//    {
//        unsigned char array[PlaygroundLinesDataDefines::ArraySize] = {0};

//        for (size_t i = 0; i < PlaygroundLinesDataDefines::ArraySize; i++)
//            array[i] = CPlaygroundLinesData::rawByteValue(data, i);

//        for (size_t x = 0; x <  PlaygroundLinesDataDefines::LinesCount; x++)
//            for (size_t y = 0; y < PlaygroundLinesDataDefines::LineLength; y++)
//            {
//                const unsigned char index = x * PlaygroundLinesDataDefines::LineLength + y;
//                const unsigned char arrayIndex = index / PlaygroundLinesDataDefines::ItemsPerByte;
//                const unsigned char byteItemIndex = index % PlaygroundLinesDataDefines::ItemsPerByte;

//                const unsigned char itemValue = byteItemValue(array[arrayIndex], byteItemIndex);

//                m_linesData[x][y] = itemValue;
//            }
//    }
//}

////////////////////////////////////////////////////////////////////////////

CPlayerData::CPlayerData(PlayerData* data)
    : m_x(data->x)
    , m_y(data->y)
    , m_borderCount(data->borderCount)
    , m_finishPosition(static_cast<FinishPosition>(data->finishPosition))
{
    Q_CHECK_PTR(data);
}


////////////////////////////////////////////////////////////////////////////

//CPlaygroundData::CPlaygroundData(PlaygroundData *data)
//    : m_hLines(&data->horizontalLines)
//    , m_vLines(&data->verticalLines)
//{
//    Q_CHECK_PTR(data);
//}

////////////////////////////////////////////////////////////////////////////

GameData* CGameData::createGameDataStructure()
{
    GameData *ptr = new GameData;

    memset(ptr, 0, sizeof(GameData));

    return ptr;
}
