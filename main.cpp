#include <QCoreApplication>

#include <QBitArray>
#include <QTime>
#include "structures.h"
#include "datautils.h"
#include "iostream"

#include "gamedatahash.h"
#include "datautilsinl.h"
#include "searchalg.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameData *game = CGameData::createGameDataStructure();

    std::list<PlayerActionAdd*> actions;

    PlaygroundDataInl::getAvaliableBorderActions(&game->playground, actions);


    PointData point;
    point.x = 4;
    point.y = 0;

    SearchAlg::checkFinishRoute(&game->playground, &point, FinishPosotionBottom);

    return 0;
}
