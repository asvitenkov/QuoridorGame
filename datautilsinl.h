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


//inline void convertToPlaygroundLinesBorderMap(const PlaygroundLinesData *data, PlaygroundLinesBorderMap &map)
//{
//#ifdef ENABLE_PARAMS_CHECKING
//    Q_CHECK_PTR(data);
//#endif

//    memset(&map, 0, sizeof(PlaygroundLinesBorderMap));

//    unsigned char array[PlaygroundLinesDataDefines::ArraySize] = {0};

//    for (size_t i = 0; i < PlaygroundLinesDataDefines::ArraySize; i++)
//        array[i] = PlaygroundLinesDataInl::rawByteValue(data, i);

//    for (size_t x = 0; x <  PlaygroundLinesDataDefines::LinesCount; x++)
//        for (size_t y = 0; y < PlaygroundLinesDataDefines::LineLength - 1; y++)
//            // -1 because we store only the beginning point of the border
//        {
//            const unsigned char index = x * PlaygroundLinesDataDefines::LineLength + y;
//            const unsigned char arrayIndex = index / PlaygroundLinesDataDefines::ItemsPerByte;
//            const unsigned char byteItemIndex = index % PlaygroundLinesDataDefines::ItemsPerByte;

//            const unsigned char itemValue = byteItemValue(array[arrayIndex], byteItemIndex);

//            map.lines[x][y] |= itemValue;

//            if (itemValue != 0)
//                map.lines[x][y + 1] = itemValue;
//        }

//}

inline void changeBorder(PlaygroundLinesData *data, unsigned char x, unsigned char y, bool addBorder)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::LinesCount, "PlaygroundLinesDataInl::changeBorder", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    // -1 because we can't add border to the last cell
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::LineLength - 1, "PlaygroundLinesDataInl::changeBorder", QString("y coord is out of range: %1").arg(y).toStdString().c_str());

    Q_ASSERT_X(PlaygroundLinesDataInl::value(data, x, y) == LINE_EMPTY
               && ((y - 1) < 0 || PlaygroundLinesDataInl::value(data, x, y - 1) == LINE_EMPTY), "PlaygroundLinesDataInl::changeBorder", "Can't add border - position failed");
#endif

    const unsigned char value = addBorder ? 1 : 0;

    // we store only start border point
    PlaygroundLinesDataInl::setValue(data, x, y, value);
}

} // namespace PlaygroundLinesDataInl


namespace PlaygroundDataInl
{

//inline PlaygroundBorderMap* convertToPlaygroundBorderMap(PlaygroundData *data)
//{
//#ifdef ENABLE_PARAMS_CHECKING
//    Q_CHECK_PTR(data);
//#endif

//    PlaygroundBorderMap *map = new PlaygroundBorderMap;
//    memset(map, 0, sizeof(PlaygroundBorderMap));


//    PlaygroundLinesDataInl::convertToPlaygroundLinesBorderMap(&data->horizontalLines, map->horizontalBorderMap);
//    PlaygroundLinesDataInl::convertToPlaygroundLinesBorderMap(&data->verticalLines, map->verticalBorderMap);

//    return map;
//}

inline bool canPlayerMooveTo(PlaygroundData *data, unsigned char x, unsigned char y, bool horizontal, bool positive)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::PlaygroundSize, "PlaygroundDataInl::canPlayerMooveTo", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::PlaygroundSize, "PlaygroundDataInl::canPlayerMooveTo", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
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

    // in PlaygroundLinesData stored information only about the start point of border
    // we mush check 2 states - border starts between two cells (x,y) or border start between previous point

    if (dx != 0)
    {
        // horizontal moovment
        // check vertical lines

        if (dx > 0)
        {
            if ((PlaygroundLinesDataInl::value(&data->verticalLines, x, y) == 0 )
                    && ((y - 1 < 0) ||  PlaygroundLinesDataInl::value(&data->verticalLines, x, y - 1) == 0 ))
                result = true;
        }
        else
        {
            // dx < 0
            if ((PlaygroundLinesDataInl::value(&data->verticalLines, x - 1, y) == 0)
                    && ((y - 1 < 0) ||  PlaygroundLinesDataInl::value(&data->verticalLines, x - 1, y - 1) == 0 ))
                result = true;
        }

//        if ((dx > 0 && PlaygroundLinesDataInl::value(&data->verticalLines, x, y) == 0)
//                || (dx < 0 && PlaygroundLinesDataInl::value(&data->verticalLines, x - 1, y) == 0))
//            result = true;
    }
    else
    {
        // vertical moovment
        // check horizontal line

        if (dy > 0)
        {
            if ((PlaygroundLinesDataInl::value(&data->horizontalLines, y, x) == 0 )
                    && ((x - 1 < 0) ||  PlaygroundLinesDataInl::value(&data->horizontalLines, y, x - 1) == 0 ))
                result = true;
        }
        else
        {
            // dy < 0
            if ((PlaygroundLinesDataInl::value(&data->horizontalLines, y - 1, x) == 0)
                    && ((x - 1 < 0) ||  PlaygroundLinesDataInl::value(&data->horizontalLines, y - 1, x - 1) == 0 ))
                result = true;
        }

//        if ((dy > 0 && PlaygroundLinesDataInl::value(&data->horizontalLines, y, x) == 0)
//                || (dy < 0 && PlaygroundLinesDataInl::value(&data->horizontalLines, y - 1, x) == 0))
//            result = true;
    }

    return result;
}


///
/// \brief getAvaliableBorderPosition check borders position for pair <V,H> or <H,V> as you pass
/// \param first  lines array to set borders
/// \param second lines array to check borders
///
inline void getAvaliableBorderActions(PlaygroundData *data, std::list<PlayerActionAdd*> &actions)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
#endif

    PlaygroundLinesData *first = &data->horizontalLines;
    PlaygroundLinesData *second = &data->verticalLines;

    for (int x = 0; x < PlaygroundLinesDataDefines::LinesCount; x++)
        for (int y = 0; y < (PlaygroundLinesDataDefines::LineLength - 1); y++)
        {
            // check horizontal lines
            // check if first[x,y] and first[x, y + 1] and first[x, y - 1] is empty
            // and if second[y,x] is empty (no orthogonal border)
            if (PlaygroundLinesDataInl::value(first, x, y) == LINE_EMPTY
                    && PlaygroundLinesDataInl::value(first, x, y + 1) == LINE_EMPTY
                    && ( (y - 1 < 0) || PlaygroundLinesDataInl::value(first, x, y - 1) == LINE_EMPTY)
                    && PlaygroundLinesDataInl::value(second, y, x) == LINE_EMPTY)
            {
                PlayerActionAdd *item = new PlayerActionAdd;
                item->action.type = IPlayerAction::addHorizontalLine;
                item->point.x = x;
                item->point.y = y;
                actions.push_back(item);
            }

            // check vertical lines
            // change first with second
            if (PlaygroundLinesDataInl::value(second, x, y) == LINE_EMPTY
                    && PlaygroundLinesDataInl::value(second, x, y + 1) == LINE_EMPTY
                    && ( (y - 1 < 0) || PlaygroundLinesDataInl::value(second, x, y - 1) == LINE_EMPTY)
                    && PlaygroundLinesDataInl::value(first, y, x) == LINE_EMPTY)
            {
                PlayerActionAdd *item = new PlayerActionAdd;
                item->action.type = IPlayerAction::addVerticalLine;
                item->point.x = x;
                item->point.y = y;
                actions.push_back(item);
            }
        }
}

inline void addVerticalBorder(PlaygroundData *data, unsigned char x, unsigned char y)
{
    PlaygroundLinesDataInl::changeBorder(&data->verticalLines, x, y, true);
}

inline void removeVerticalBorder(PlaygroundData *data, unsigned char x, unsigned char y)
{
    PlaygroundLinesDataInl::changeBorder(&data->verticalLines, x, y, false);
}

inline void addHorizontalBorder(PlaygroundData *data, unsigned char x, unsigned char y)
{
    PlaygroundLinesDataInl::changeBorder(&data->horizontalLines, x, y, true);
}

inline void removeHorizontalBorder(PlaygroundData *data, unsigned char x, unsigned char y)
{
    PlaygroundLinesDataInl::changeBorder(&data->horizontalLines, x, y, false);
}

} // namespace PlaygroundDataInl

namespace GameDataInl
{




inline void getAvaliablePlayerActions(GameData *data, uint player)
{
    Q_CHECK_PTR(data);

    if (!(player < PlayerDataDefines::PlayerCount))
        return;

    std::list<PlayerActionAdd*> borderActions;

    PlaygroundDataInl::getAvaliableBorderActions(&data->playground, borderActions);
}


} //namespace GameDataInl


//namespace PlaygroundBorderMapInl
//{

//inline bool canPlayerMooveTo(PlaygroundBorderMap *map, unsigned char x, unsigned char y, bool horizontal, bool positive)
//{
//#ifdef ENABLE_PARAMS_CHECKING
//    Q_CHECK_PTR(map);
//    Q_ASSERT_X(x < PlaygroundLinesDataDefines::PlaygroundSize, "PlaygroundBorderMapInl::canPlayerMooveTo", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
//    Q_ASSERT_X(y < PlaygroundLinesDataDefines::PlaygroundSize, "PlaygroundBorderMapInl::canPlayerMooveTo", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
//#endif

//    const int d = positive ? 1 : -1;
//    const int dx = horizontal ? d : 0;
//    const int dy = horizontal ? 0 : d;

//    const int newX = x + dx;
//    const int newY = y + dy;

//    if (newX < 0 || newX >= PlaygroundLinesDataDefines::PlaygroundSize)
//        return false;

//    if (newY < 0 || newY >= PlaygroundLinesDataDefines::PlaygroundSize)
//        return false;

//    bool result = false;

//    if (dx != 0)
//    {
//        // horizontal moovment
//        // check vertical lines
//        if ((dx > 0 && map->verticalBorderMap.lines[x][y] == 0)
//                || (dx < 0 && map->verticalBorderMap.lines[x - 1][y] == 0))
//            result = true;
//    }
//    else
//    {
//        // vertical moovment
//        // check horizontal line
//        if ((dy > 0 && map->horizontalBorderMap.lines[y][x] == 0)
//                || (dy < 0 && map->horizontalBorderMap.lines[y - 1][x] == 0))
//            result = true;
//    }

//    return result;
//}

//} //namespace PlaygroundBorderMapInl

#endif // DATAUTILSINL

