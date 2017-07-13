#include "searchalg.h"
#include "datautilsinl.h"

#include "playgroundwidget.h"

#include <QtGlobal>

//delete me
//#include <QMessageBox>
//CPlaygroundWidget *gWidget = NULL;

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


bool checkFinishRouteRecursive(unsigned char x, unsigned char y, FinishPosition finishPosition, PlaygroundBorderMap *borderMap, unsigned int stepsCount, PlaygroundCellsMap &stepsMap)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(borderMap);

    if (finishPosition < FinishPositionFirst || finishPosition > FinishPositionLast)
    {
        qCritical() << "SearchAlg::checkFinishRouteRecursive error: finishPosition is out of range - " << (unsigned char) finishPosition;
        return false;
    }
#endif

    const FinistPointData &finishPointData = gFinistPointDataArray[static_cast<size_t>(finishPosition)];

//    if (stepsMap.map[x][y] <= stepsCount)
//        return false;

    stepsMap.map[x][y] = stepsCount;

    // delete me only for testing
//    gWidget->showRoute(x, y, finishPosition, borderMap, &stepsMap);
//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.exec();

    if (x == finishPointData.x || y == finishPointData.y)
        return true;

    bool bRes = false;

    // up
    if (!bRes && y - 1 >= 0 && stepsMap.map[x][y - 1] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(borderMap, x, y, false, false))
        bRes = checkFinishRouteRecursive(x, y - 1, finishPosition, borderMap, stepsCount + 1, stepsMap);

    // right
    if (!bRes && x + 1 < PlaygroundLinesDataDefines::PlaygroundSize
            && stepsMap.map[x + 1][y] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(borderMap, x, y, true, true))
        bRes = checkFinishRouteRecursive(x + 1, y, finishPosition, borderMap, stepsCount + 1, stepsMap);

    // down
    if (!bRes && y + 1 < PlaygroundLinesDataDefines::PlaygroundSize
            && stepsMap.map[x][y + 1] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(borderMap, x, y, false, true))
        bRes = checkFinishRouteRecursive(x, y + 1, finishPosition, borderMap, stepsCount + 1, stepsMap);

    // left
    if (!bRes && x - 1 >=0 && stepsMap.map[x - 1][y] > stepsCount + 1
            && PlaygroundBorderMapInl::canPlayerMooveTo(borderMap, x, y, true, false))
        bRes = checkFinishRouteRecursive(x - 1, y, finishPosition, borderMap, stepsCount + 1, stepsMap);

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

    PlaygroundBorderMap *borderMap = PlaygroundDataInl::convertToPlaygroundBorderMap(data);

    static PlaygroundCellsMap stepsMap;
    memset(&stepsMap, 255, sizeof(PlaygroundCellsMap));

    bool bRes = false;

    // delete me only for testing
//    gWidget = new CPlaygroundWidget(0);
//    gWidget->show();

    bRes = checkFinishRouteRecursive(x, y, finishPosition, borderMap, 0, stepsMap);

    //delete me
//    CPlaygroundWidget *widget = new CPlaygroundWidget(0);
//    widget->show();
//    widget->showRoute(x, y, finishPosition, borderMap, &stepsMap);


    return bRes;
}


}
