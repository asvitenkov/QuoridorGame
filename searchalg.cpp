#include "searchalg.h"

#include <QtGlobal>

namespace SearchAlg
{

typedef struct
{
    char x : 4;
    char y : 4;
} FinistPointData;


// -1 to skip
static FinistPointData gFinistPointDataArray[4] = {
    {-1, 0},
    {PlaygroundLinesDataDefines::LinesCount, -1},
    {-1, PlaygroundLinesDataDefines::LinesCount},
    {0, -1}
};


bool checkFinishRouteRecursive(PlaygroundData *data, unsigned char x, unsigned char y, FinishPosition finishPosition, PlaygroundBorderMap *map)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_CHECK_PTR(map);

    if (finishPosition < FinishPositionFirst || finishPosition > FinishPositionLast)
    {
        qCritical() << "SearchAlg::checkFinishRouteRecursive error: finishPosition is out of range - " << (unsigned char) finishPosition;
        return false;
    }
#endif

    const FinistPointData &finishPointData = gFinistPointDataArray[static_cast<size_t>(finishPosition)];




}


bool checkFinishRoute(PlaygroundData *data, PointData *point, FinishPosition finishPosition)
{

#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(data);
    Q_CHECK_PTR(point);

    if (finishPosition < FinishPositionFirst || finishPosition > FinishPositionLast)
    {
        qCritical() << "SearchAlg::checkFinishRoute error: finishPosition is out of range - " << (unsigned char) finishPosition;
        return false;
    }
#endif

    PlaygroundBorderMap map;
    memset(&map, 255, sizeof(PlaygroundBorderMap));

    return true;
}


}
