#include "searchalg.h"
#include "datautilsinl.h"

#include "playgroundwidget.h"

#include <QtGlobal>

//delete me
//#include <QMessageBox>
//CPlaygroundWidget *gWidget = NULL;


typedef struct
{
    char x;
    char y;
} FinistPointData;


// -1 to skip
static FinistPointData gFinistPointDataArray[4] = {
    {-1, 0},
    {PlaygroundLinesDataDefines::LinesCount, -1},
    {-1, PlaygroundLinesDataDefines::LinesCount},
    {0, -1}
};

inline bool isPlayerAtFinishPositionPri(unsigned char x, unsigned char y, FinishPosition finishPosition)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::PlaygroundSize, "SearchAlg::isPlayerAtFinishPosition", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::PlaygroundSize, "SearchAlg::isPlayerAtFinishPosition", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
    Q_ASSERT_X(finishPosition >= FinishPositionFirst && finishPosition <= FinishPositionLast, "SearchAlg::isPlayerAtFinishPosition", QString("finishPosition is out of range: %1").arg(static_cast<size_t>(finishPosition)).toStdString().c_str());
#endif

    const FinistPointData &finishPointData = gFinistPointDataArray[static_cast<size_t>(finishPosition)];

    if (x == finishPointData.x || y == finishPointData.y)
        return true;

    return false;
}


namespace SearchAlg
{


bool checkFinishRouteRecursive(unsigned char x, unsigned char y, FinishPosition finishPosition, PlaygroundData *playgroundData, unsigned int stepsCount, PlaygroundCellsMap &stepsMap)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(playgroundData);

    if (finishPosition < FinishPositionFirst || finishPosition > FinishPositionLast)
    {
        qCritical() << "SearchAlg::checkFinishRouteRecursive error: finishPosition is out of range - " << (unsigned char) finishPosition;
        return false;
    }
#endif

    stepsMap.map[x][y] = stepsCount;

    // delete me only for testing
//    gWidget->showRoute(x, y, finishPosition, playgroundData, &stepsMap);
//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.exec();

    if (isPlayerAtFinishPositionPri(x, y, finishPosition))
        return true;

    bool bRes = false;

    // up
    if (!bRes && y - 1 >= 0 && stepsMap.map[x][y - 1] > stepsCount + 1
            && PlaygroundDataInl::canPlayerMooveTo(playgroundData, x, y, false, false))
        bRes = checkFinishRouteRecursive(x, y - 1, finishPosition, playgroundData, stepsCount + 1, stepsMap);

    // right
    if (!bRes && x + 1 < PlaygroundLinesDataDefines::PlaygroundSize
            && stepsMap.map[x + 1][y] > stepsCount + 1
            && PlaygroundDataInl::canPlayerMooveTo(playgroundData, x, y, true, true))
        bRes = checkFinishRouteRecursive(x + 1, y, finishPosition, playgroundData, stepsCount + 1, stepsMap);

    // down
    if (!bRes && y + 1 < PlaygroundLinesDataDefines::PlaygroundSize
            && stepsMap.map[x][y + 1] > stepsCount + 1
            && PlaygroundDataInl::canPlayerMooveTo(playgroundData, x, y, false, true))
        bRes = checkFinishRouteRecursive(x, y + 1, finishPosition, playgroundData, stepsCount + 1, stepsMap);

    // left
    if (!bRes && x - 1 >=0 && stepsMap.map[x - 1][y] > stepsCount + 1
            && PlaygroundDataInl::canPlayerMooveTo(playgroundData, x, y, true, false))
        bRes = checkFinishRouteRecursive(x - 1, y, finishPosition, playgroundData, stepsCount + 1, stepsMap);

    return bRes;
}


bool checkFinishRoute(PlaygroundData *data, unsigned char x, unsigned char y, FinishPosition finishPosition)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_ASSERT_X(x < PlaygroundLinesDataDefines::PlaygroundSize, "SearchAlg::checkFinishRoute", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y < PlaygroundLinesDataDefines::PlaygroundSize, "SearchAlg::checkFinishRoute", QString("y coord is out of range: %1").arg(y).toStdString().c_str());
    Q_ASSERT_X(finishPosition >= FinishPositionFirst && finishPosition <= FinishPositionLast, "SearchAlg::checkFinishRoute", QString("finishPosition is out of range: %1").arg(static_cast<size_t>(finishPosition)).toStdString().c_str());
#endif

    //PlaygroundBorderMap *borderMap = PlaygroundDataInl::convertToPlaygroundBorderMap(data);

    static PlaygroundCellsMap stepsMap;
    memset(&stepsMap, 255, sizeof(PlaygroundCellsMap));

    bool bRes = false;

    // delete me only for testing
//    gWidget = new CPlaygroundWidget(0);
//    gWidget->move(0, 0);
//    gWidget->show();

    bRes = checkFinishRouteRecursive(x, y, finishPosition, data, 0, stepsMap);

    //delete me
//    CPlaygroundWidget *widget = new CPlaygroundWidget(0);
//    widget->show();
//    widget->showRoute(x, y, finishPosition, data, &stepsMap);


    return bRes;
}



bool isPlayerAtFinishPosition(const GameData *gameData, uint playerIndex)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(gameData);
    Q_ASSERT_X(playerIndex < PlayerDataDefines::PlayerCount, "SearchAlg::isPlayerAtFinishPosition", "Player is out of range");
#endif

    const PlayerData player = gameData->players[playerIndex];

    return isPlayerAtFinishPositionPri(player.x, player.y, static_cast<FinishPosition>(player.finishPosition));
}

}
