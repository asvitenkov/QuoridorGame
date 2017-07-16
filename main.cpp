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

//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 0);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 2);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 4);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 6);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 5);

//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 1);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 3);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 5);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 7);

//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 0);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 2);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 4);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 6);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 5);

//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 1);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 3);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 5);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 7);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 7);


//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 6, 0);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 6, 2);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 1);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 3);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 5);
//    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 7);
//    PlaygroundDataInl::addVerticalBorder(&game->playground, 2, 4);
//    PlaygroundDataInl::addVerticalBorder(&game->playground, 4, 6);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 5, 7);
    PlaygroundDataInl::addVerticalBorder(&game->playground, 6, 5);


    //SearchAlg::checkFinishRoute(&game->playground, 4, 0, FinishPosotionBottom);


    GameDataInl::getAvaliablePlayerActions(game, 0);


//    CPlaygroundWidget widget;
//    widget.show();

    std::list<PlayerActionAdd*> borderActions;

    PlaygroundDataInl::getAvaliableBorderActions(&game->playground, borderActions);

    //borderActions.clear();

    CPlaygroundWidget *pWidget = new CPlaygroundWidget;
    pWidget->show();
    pWidget->showAvaliableBorderPosition(&game->playground, borderActions);

    a.exec();
    //return 0;
}
