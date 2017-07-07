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


///
/// \brief getAvaliableBorderPosition check borders position for pair <V,H> or <H,V> as you pass
/// \param first  lines array to set borders
/// \param second lines array to check borders
///
inline void getAvaliableBorderPosition(PlaygroundLinesData *first, PlaygroundLinesData *second, std::list<PointData> &positions)
{
    Q_CHECK_PTR(first);
    Q_CHECK_PTR(second);

    for (unsigned char x = 0; x < PlaygroundLinesDataDefines::LinesCount; x++)
        for (unsigned char y = 0; y < (PlaygroundLinesDataDefines::LineLength - 1); y++)
        {
            // check if first[x,y] and first[x, y + 1] is empty
            // and if second[y,x] is empty (no orthogonal border)
            if (PlaygroundLinesDataInl::value(first, x, y) == LINE_EMPTY
                    && PlaygroundLinesDataInl::value(first, x, y + 1) == LINE_EMPTY
                    && PlaygroundLinesDataInl::value(second, y, x) == LINE_EMPTY)
            {
                PointData point = {x,y};
                positions.push_back(point);
            }
        }
}


}


namespace PlaygroundDataInl
{

inline void getAvaliableBorderActions(PlaygroundData *data, std::list<PlayerActionAdd*> &actions)
{
    Q_CHECK_PTR(data);

    std::list<PointData> verticalBorderPositions, horizontalBorderPositions;

    PlaygroundLinesDataInl::getAvaliableBorderPosition(&data->vLines, &data->hLines, verticalBorderPositions);
    PlaygroundLinesDataInl::getAvaliableBorderPosition(&data->hLines, &data->vLines, horizontalBorderPositions);

    std::list<PointData>::iterator it;

    it = horizontalBorderPositions.begin();

    while (it != horizontalBorderPositions.end())
    {
        PlayerActionAdd *item = new PlayerActionAdd;
        item->action.type = PlayerAction::addHorizontalLine;
        item->point = *it;

        actions.push_back(item);
        ++it;
    }

    it = verticalBorderPositions.begin();

    while (it != verticalBorderPositions.end())
    {
        PlayerActionAdd *item = new PlayerActionAdd;
        item->action.type = PlayerAction::addVerticalLine;
        item->point = *it;

        actions.push_back(item);
        ++it;
    }


}

}

namespace  GameDataInl
{



inline void getAvaliableMoovments(GameData *data, uint player)
{
    Q_CHECK_PTR(data);

    if (!(player < PlayerDataDefines::PlayerCount))
        return;


}


}

#endif // DATAUTILSINL

