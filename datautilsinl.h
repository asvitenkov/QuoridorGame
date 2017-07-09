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

inline unsigned char rawByteValue(const PlaygroundLinesData *data, unsigned int index)
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


inline void convertToPlaygroundLinesBorderMap(const PlaygroundLinesData *data, PlaygroundLinesBorderMap &map)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
#endif

    memset(&map, 0, sizeof(PlaygroundLinesBorderMap));

    unsigned char array[PlaygroundLinesDataDefines::ArraySize] = {0};

    for (size_t i = 0; i < PlaygroundLinesDataDefines::ArraySize; i++)
        array[i] = PlaygroundLinesDataInl::rawByteValue(data, i);

    for (size_t x = 0; x <  PlaygroundLinesDataDefines::LinesCount; x++)
        for (size_t y = 0; y < PlaygroundLinesDataDefines::LineLength; y++)
        {
            const unsigned char index = x * PlaygroundLinesDataDefines::LineLength + y;
            const unsigned char arrayIndex = index / PlaygroundLinesDataDefines::ItemsPerByte;
            const unsigned char byteItemIndex = index % PlaygroundLinesDataDefines::ItemsPerByte;

            const unsigned char itemValue = byteItemValue(array[arrayIndex], byteItemIndex);

            map.lines[x][y] = itemValue;
        }

}

} // namespace PlaygroundLinesDataInl


namespace PlaygroundDataInl
{

inline PlaygroundBorderMap* convertToPlaygroundBorderMap(PlaygroundData *data)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
#endif

    PlaygroundBorderMap *map = new PlaygroundBorderMap;
    memset(map, 0, sizeof(PlaygroundBorderMap));


    PlaygroundLinesDataInl::convertToPlaygroundLinesBorderMap(&data->horizontalLines, map->horizontalBorderMap);
    PlaygroundLinesDataInl::convertToPlaygroundLinesBorderMap(&data->verticalLines, map->verticalBorderMap);

    return map;
}


inline void getAvaliableBorderActions(PlaygroundData *data, std::list<PlayerActionAdd*> &actions)
{
    Q_CHECK_PTR(data);

    std::list<PointData> verticalBorderPositions, horizontalBorderPositions;

    PlaygroundLinesDataInl::getAvaliableBorderPosition(&data->verticalLines, &data->horizontalLines, verticalBorderPositions);
    PlaygroundLinesDataInl::getAvaliableBorderPosition(&data->horizontalLines, &data->verticalLines, horizontalBorderPositions);

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

} // namespace PlaygroundDataInl

namespace GameDataInl
{



inline void getAvaliableMoovments(GameData *data, uint player)
{
    Q_CHECK_PTR(data);

    if (!(player < PlayerDataDefines::PlayerCount))
        return;


}


} //namespace GameDataInl


namespace PlaygroundBorderMapInl
{

inline bool canPlayerMooveTo(PlaygroundBorderMap *map, unsigned char x, unsigned char y, bool horizontal, bool positive)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(map);
    Q_ASSERT_X(x > PlaygroundLinesDataDefines::PlaygroundSize, "PlaygroundBorderMapInl::canPlayerMoove", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y > PlaygroundLinesDataDefines::PlaygroundSize, "PlaygroundBorderMapInl::canPlayerMoove", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
#endif

    const int d = positive ? 1 : -1;
    const int dx = horizontal ? d : 0;
    const int dy = horizontal ? 0 : d;

    const int newX = x + dx;
    const int newY = y + dy;

    if (newX < 0 || newX >= PlaygroundLinesDataDefines::PlaygroundSize)
        return false;

    if (newY < 0 || newY >= PlaygroundLinesDataDefines::PlaygroundSize)
        return false;

    bool result = false;

    if (dx != 0)
    {
        // horizontal moovment
        // check vertical lines
        if ((dx > 0 && map->verticalBorderMap.lines[x][y] != 0)
                || (dx < 0 && map->verticalBorderMap.lines[x - 1][y] != 0))
            result = true;
    }
    else
    {
        // vertical moovment
        // check horizontal line
        if ((dy > 0 && map->horizontalBorderMap.lines[y][x] != 0)
                || (dx < 0 && map->horizontalBorderMap.lines[y - 1][x] != 0))
            result = true;
    }

    return result;
}

} //namespace PlaygroundBorderMapInl

#endif // DATAUTILSINL

