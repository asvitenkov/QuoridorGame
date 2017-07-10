#include <QApplication>

#include <QBitArray>
#include <QTime>
#include "structures.h"
#include "datautils.h"
#include "iostream"

#include "gamedatahash.h"
#include "datautilsinl.h"
#include "searchalg.h"
#include "playgroundwidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameData *game = CGameData::createGameDataStructure();

//    std::list<PlayerActionAdd*> actions;
//    PlaygroundDataInl::getAvaliableBorderActions(&game->playground, actions);
//    PointData point;
//    point.x = 4;
//    point.y = 0;
//    SearchAlg::checkFinishRoute(&game->playground, &point, FinishPosotionBottom);


    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 0, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 2, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 4, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 6, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 0, 5, 1);

    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 1, 1, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 1, 3, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 1, 5, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 1, 7, 1);

    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 2, 0, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 2, 2, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 2, 4, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 2, 6, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 2, 5, 1);

    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 3, 1, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 3, 3, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 3, 5, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 3, 7, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 3, 7, 1);


    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 6, 0, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 6, 2, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 7, 3, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.horizontalLines, 7, 1, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.verticalLines, 2, 4, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.verticalLines, 4, 6, 1);
    PlaygroundLinesDataInl::setValue(&game->playground.verticalLines, 0, 7, 1);


    SearchAlg::checkFinishRoute(&game->playground, 4, 0, FinishPosotionBottom);

//    CPlaygroundWidget widget;
//    widget.show();

    a.exec();
    //return 0;
}
