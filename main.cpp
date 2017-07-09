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

//    std::list<PlayerActionAdd*> actions;
//    PlaygroundDataInl::getAvaliableBorderActions(&game->playground, actions);
//    PointData point;
//    point.x = 4;
//    point.y = 0;
//    SearchAlg::checkFinishRoute(&game->playground, &point, FinishPosotionBottom);


    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 3, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 5, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 4, 7, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 4, 5, 1);

    PlaygroundLinesDataInl::setValue(&game->playground.verticalLines, 2, 0, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.verticalLines, 2, 2, 1);
    //PlaygroundLinesDataInl::setValue(&game->playground.verticalLines, 4, 2, 1);


    SearchAlg::checkFinishRoute(&game->playground, 4, 0, FinishPosotionBottom);

    return 0;
}
