#include "searchalg.h"
#include "datautilsinl.h"

#include <QtGlobal>

namespace SearchAlg
{

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

typedef unsigned char PlaygroundStepsMap[PlaygroundLinesDataDefines::PlaygroundSize][PlaygroundLinesDataDefines::PlaygroundSize];


bool checkFinishRouteRecursive(unsigned char x, unsigned char y, FinishPosition finishPosition, PlaygroundBorderMap *map, unsigned int stepsCount, PlaygroundStepsMap &stepsMap)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(stepsMap);
    Q_CHECK_PTR(map);

    if (finishPosition < FinishPositionFirst || finishPosition > FinishPositionLast)
    {
        qCritical() << "SearchAlg::checkFinishRouteRecursive error: finishPosition is out of range - " << (unsigned char) finishPosition;
        return false;
    }
#endif

    const FinistPointData &finishPointData = gFinistPointDataArray[static_cast<size_t>(finishPosition)];

    if (x == finishPointData.x || y == finishPointData.y)
        return true;

    if (stepsMap[x][y] <= stepsCount)
        return false;

    stepsMap[x][y] = stepsCount;

    bool bRes = false;

    if (!bRes && y - 1 >= 0 && stepsMap[x][y - 1] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(map, x, y, false, false))
        bRes = checkFinishRouteRecursive(x, y - 1, finishPosition, map, stepsCount + 1, stepsMap);

    if (!bRes && y + 1 < PlaygroundLinesDataDefines::PlaygroundSize
            && stepsMap[x][y + 1] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(map, x, y, false, true))
        bRes = checkFinishRouteRecursive(x, y + 1, finishPosition, map, stepsCount + 1, stepsMap);

    if (!bRes && x - 1 >=0 && stepsMap[x - 1][y] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(map, x, y, true, false))
        bRes = checkFinishRouteRecursive(x - 1, y, finishPosition, map, stepsCount + 1, stepsMap);

    if (!bRes && x + 1 < PlaygroundLinesDataDefines::PlaygroundSize
            && stepsMap[x + 1][y] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(map, x, y, true, true))
        bRes = checkFinishRouteRecursive(x + 1, y, finishPosition, map, stepsCount + 1, stepsMap);

    return bRes;
}


bool checkFinishRoute(PlaygroundData *data, unsigned char x, unsigned char y, FinishPosition finishPosition)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_ASSERT_X(x >=0 && x < PlaygroundLinesDataDefines::PlaygroundSize, "SearchAlg::checkFinishRoute", QString("x coord is out of range: %1").arg(x).toStdString().c_str());
    Q_ASSERT_X(y >=0 && y < PlaygroundLinesDataDefines::PlaygroundSize, "SearchAlg::checkFinishRoute", QString("y coord is out of range: %1").arg(y).toStdString().c_str());

    if (finishPosition < FinishPositionFirst || finishPosition > FinishPositionLast)
    {
        qCritical() << "SearchAlg::checkFinishRoute error: finishPosition is out of range - " << (unsigned char) finishPosition;
        return false;
    }
#endif

    PlaygroundBorderMap *map = PlaygroundDataInl::convertToPlaygroundBorderMap(data);

    static PlaygroundStepsMap stepsMap;
    memset(&stepsMap, 255, sizeof(PlaygroundStepsMap));

    bool bRes = false;

    bRes = checkFinishRouteRecursive(x, y, finishPosition, map, 0, stepsMap);

    QString str;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            unsigned char value = stepsMap[j][i];

            if (value < 10)  str += " ";
            if (value < 100) str += " ";
            str += QString::number(value) + " ";
        }
        qDebug() << str;
        str = "";
    }




    return bRes;
}


}
