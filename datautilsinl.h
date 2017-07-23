#ifndef DATAUTILSINL
#define DATAUTILSINL

#include "structures.h"
#include "searchalg.h"

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

inline unsigned char value(const PlaygroundLinesData *data, unsigned char x, unsigned char y)
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

    Q_ASSERT_X(PlaygroundLinesDataInl::value(data, x, y) == (addBorder ? LINE_EMPTY : LINE_BEGIN)
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
inline void getAvaliableBorderActions(PlaygroundData *data, std::list<PlayerActionAddBorder*> &actions)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_ASSERT_X(actions.empty(), "GameDataInl::getAvaliableBorderActions", "actions is not empty");
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
                PlayerActionAddBorder *item = new PlayerActionAddBorder;
                item->action.type = IPlayerAction::addHorizontalBorder;
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
                PlayerActionAddBorder *item = new PlayerActionAddBorder;
                item->action.type = IPlayerAction::addVerticalBorder;
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


inline void doAction(GameData *gameData, uint playerIndex, const IPlayerAction *playerAction)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(gameData);
    Q_CHECK_PTR(playerAction);
    Q_ASSERT_X(playerIndex < PlayerDataDefines::PlayerCount, "GameDataInl::doAction", "Player is out of range");
#endif

    IPlayerAction::PlayerActionType actionType = static_cast<IPlayerAction::PlayerActionType>(playerAction->type);
    PlayerData &player = gameData->players[playerIndex];

    if (actionType == IPlayerAction::addHorizontalBorder
            || actionType == IPlayerAction::addVerticalBorder)
    {
#ifdef ENABLE_PARAMS_CHECKING
        Q_ASSERT_X(player.borderCount > 0, "GameDataInl::doAction", "Add border failed - no free border avaliable");
#endif
        PlayerActionAddBorder *pAction = const_cast<PlayerActionAddBorder*>(reinterpret_cast<const PlayerActionAddBorder*>(playerAction));

        if (actionType == IPlayerAction::addHorizontalBorder)
            PlaygroundDataInl::addHorizontalBorder(&gameData->playground, pAction->point.x, pAction->point.y);

        if (actionType == IPlayerAction::addVerticalBorder)
            PlaygroundDataInl::addVerticalBorder(&gameData->playground, pAction->point.x, pAction->point.y);

        player.borderCount--;
    }
    else
    {
        const bool horizontalMoovment = actionType == IPlayerAction::moveLeft  || actionType == IPlayerAction::moveRight;
        const bool   positiveMoovment = actionType == IPlayerAction::moveRight || actionType == IPlayerAction::moveBottom;

#ifdef ENABLE_PARAMS_CHECKING
        const unsigned char x = player.x;
        const unsigned char y = player.y;

        Q_UNUSED(x);
        Q_UNUSED(y);

        Q_ASSERT_X(PlaygroundDataInl::canPlayerMooveTo(&gameData->playground, x, y, horizontalMoovment, positiveMoovment),
                   "GameDataInl::doAction", QString("player can't move from [%1,%2] to %3").arg(x).arg(y).arg(actionType).toStdString().c_str());
#endif

        const char dd = positiveMoovment ? 1 : -1;

        if (horizontalMoovment)
        {
            player.x = player.x + dd;
        }
        else
        {
            player.y = player.y + dd;
        }
    }
}

inline void undoAction(GameData *gameData, uint playerIndex, const IPlayerAction *playerAction)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(gameData);
    Q_CHECK_PTR(playerAction);
    Q_ASSERT_X(playerIndex < PlayerDataDefines::PlayerCount, "GameDataInl::undoAction", "Player is out of range");
#endif

    IPlayerAction::PlayerActionType actionType = static_cast<IPlayerAction::PlayerActionType>(playerAction->type);
    PlayerData &player = gameData->players[playerIndex];

    if (actionType == IPlayerAction::addHorizontalBorder
            || actionType == IPlayerAction::addVerticalBorder)
    {
        PlayerActionAddBorder *pAction = const_cast<PlayerActionAddBorder*>(reinterpret_cast<const PlayerActionAddBorder*>(playerAction));

        if (actionType == IPlayerAction::addHorizontalBorder)
            PlaygroundDataInl::removeHorizontalBorder(&gameData->playground, pAction->point.x, pAction->point.y);

        if (actionType == IPlayerAction::addVerticalBorder)
            PlaygroundDataInl::removeVerticalBorder(&gameData->playground, pAction->point.x, pAction->point.y);

        player.borderCount++;
    }
    else
    {
        const bool horizontalMoovment = actionType == IPlayerAction::moveLeft  || actionType == IPlayerAction::moveRight;
        const bool positiveMoovment = !(actionType == IPlayerAction::moveRight || actionType == IPlayerAction::moveBottom);

#ifdef ENABLE_PARAMS_CHECKING
        const unsigned char x = player.x;
        const unsigned char y = player.y;

        Q_UNUSED(x);
        Q_UNUSED(y);

        Q_ASSERT_X(PlaygroundDataInl::canPlayerMooveTo(&gameData->playground, x, y, horizontalMoovment, positiveMoovment),
                   "GameDataInl::undoAction", QString("player can't move from [%1,%2] to %3").arg(x).arg(y).arg(actionType).toStdString().c_str());
#endif

        const char dd = positiveMoovment ? 1 : -1;

        if (horizontalMoovment)
        {
            player.x = player.x + dd;
        }
        else
        {
            player.y = player.y + dd;
        }
    }
}


inline void getAvaliablePlayerActions(GameData *gameData, uint playerIndex, std::list<IPlayerAction*> &playerActions)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(gameData);
    Q_ASSERT_X(playerIndex < PlayerDataDefines::PlayerCount, "GameDataInl::getAvaliablePlayerActions", "Player is out of range");
    Q_ASSERT_X(playerActions.empty(), "GameDataInl::getAvaliablePlayerActions", "playerActions is not empty");
#endif


    const unsigned char x = gameData->players[playerIndex].x;
    const unsigned char y = gameData->players[playerIndex].y;

    // left moovment
    if (PlaygroundDataInl::canPlayerMooveTo(&gameData->playground, x, y, true, false))
    {
        PlayerActionMove* pAction = new PlayerActionMove;
        pAction->action.type = IPlayerAction::moveLeft;
        playerActions.push_back(reinterpret_cast<IPlayerAction*>(pAction));
    }

    // right moovment
    if (PlaygroundDataInl::canPlayerMooveTo(&gameData->playground, x, y, true, true))
    {
        PlayerActionMove* pAction = new PlayerActionMove;
        pAction->action.type = IPlayerAction::moveRight;
        playerActions.push_back(reinterpret_cast<IPlayerAction*>(pAction));
    }

    // top moovment
    if (PlaygroundDataInl::canPlayerMooveTo(&gameData->playground, x, y, false, false))
    {
        PlayerActionMove* pAction = new PlayerActionMove;
        pAction->action.type = IPlayerAction::moveTop;
        playerActions.push_back(reinterpret_cast<IPlayerAction*>(pAction));
    }

    // bottom moovment
    if (PlaygroundDataInl::canPlayerMooveTo(&gameData->playground, x, y, false, true))
    {
        PlayerActionMove* pAction = new PlayerActionMove;
        pAction->action.type = IPlayerAction::moveBottom;
        playerActions.push_back(reinterpret_cast<IPlayerAction*>(pAction));
    }

    //uncomment me please
    // commented just for testing
    if (gameData->players[playerIndex].borderCount > 0)
    {
        std::list<PlayerActionAddBorder*> borderActions;
        PlaygroundDataInl::getAvaliableBorderActions(&gameData->playground, borderActions);

        std::list<PlayerActionAddBorder*>::iterator it = borderActions.begin();

        while (it != borderActions.end())
        {
            IPlayerAction *pAction = reinterpret_cast<IPlayerAction*>(*it);

            GameDataInl::doAction(gameData, playerIndex, pAction);

            bool flag = true;

            for (size_t i = 0; i < PlayerDataDefines::PlayerCount && flag; i++)
            {
                PlayerData &player = gameData->players[i];
                flag = SearchAlg::checkFinishRoute(&gameData->playground, player.x, player.y, static_cast<FinishPosition>(player.finishPosition));
            }

            if (flag)
                playerActions.push_back(pAction);

            GameDataInl::undoAction(gameData, playerIndex, pAction);
            ++it;
        }
    }
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

