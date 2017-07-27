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
#include "gamealg.h"

//delete me
#include <QMessageBox>

//#pragma comment(linker, "/STACK:800000000")


void makeGame()
{
    GameData *game = CGameData::createGameDataStructure();

    game->players[0].x = 4;
    game->players[0].y = 0;
    game->players[0].finishPosition = FinishPosotionBottom;
    game->players[0].borderCount = 7;

    game->players[1].x = 0;
    game->players[1].y = 4;
    game->players[1].finishPosition = FinishPosotionRight;
    game->players[1].borderCount = 7;

    game->players[2].x = 4;
    game->players[2].y = 8;
    game->players[2].finishPosition = FinishPosotionTop;
    game->players[2].borderCount = 7;

    game->players[3].x = 8;
    game->players[3].y = 4;
    game->players[3].finishPosition = FinishPosotionLeft;
    game->players[3].borderCount = 7;

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 2);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 4);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 0);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 3);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 7);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 0);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 2);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 4);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 5);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 7);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 5, 5);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 5, 7);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 6, 0);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 6, 2);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 1);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 3);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 5);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 7);

    PlaygroundDataInl::addVerticalBorder(&game->playground, 1, 4);

    PlaygroundCellsMap map;

    SearchAlg::fillCellsMap(&game->playground, 4, 8, FinishPosotionTop, map);


}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    makeGame();

    GameData *game = CGameData::createGameDataStructure();

    game->players[0].x = 4;
    game->players[0].y = 0;
    game->players[0].finishPosition = FinishPosotionBottom;
    game->players[0].borderCount = 7;

    game->players[1].x = 0;
    game->players[1].y = 4;
    game->players[1].finishPosition = FinishPosotionRight;
    game->players[1].borderCount = 7;

    game->players[2].x = 4;
    game->players[2].y = 8;
    game->players[2].finishPosition = FinishPosotionTop;
    game->players[2].borderCount = 7;

    game->players[3].x = 8;
    game->players[3].y = 4;
    game->players[3].finishPosition = FinishPosotionLeft;
    game->players[3].borderCount = 7;

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 0);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 2);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 4);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 0, 6);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 1);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 3);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 5);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 1, 7);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 0);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 2);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 4);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 2, 6);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 1);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 3);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 5);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 3, 7);


    PlaygroundDataInl::addHorizontalBorder(&game->playground, 6, 0);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 6, 2);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 1);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 3);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 5);
    PlaygroundDataInl::addHorizontalBorder(&game->playground, 7, 7);
    PlaygroundDataInl::addVerticalBorder(&game->playground, 2, 4);
    PlaygroundDataInl::addVerticalBorder(&game->playground, 4, 6);

    PlaygroundDataInl::addHorizontalBorder(&game->playground, 5, 7);
    PlaygroundDataInl::addVerticalBorder(&game->playground, 6, 5);

//    CPlaygroundWidget *pWidget = new CPlaygroundWidget;
//    pWidget->show();
//    pWidget->move(0,0);

//    pWidget->showGame(game);

//    std::list<IPlayerAction*> actions;
//    for (size_t i = 0; i < 4; i++)
//    {
////        CPlaygroundWidget *pWidget = new CPlaygroundWidget;
////        pWidget->show();
////        pWidget->move(0,0);

//        actions.clear();
//        GameDataInl::getAvaliablePlayerActions(game, i, actions);
////        pWidget->showAvaliablePlayerActions(game, i, actions);
////            QMessageBox msgBox;
////            msgBox.setText("The document has been modified.");
////            msgBox.exec();
//    }


    PlaygroundCellsMap map;

    SearchAlg::fillCellsMap(&game->playground, 4, 4, FinishPosotionTop, map);


    quint64 total,win;
    total = win = 0;

    GameAlg::processGameStateRec(game, &total, &win);

    qDebug() << "total: " << total;
    qDebug() << "win: " << win;

    a.exec();
    //return 0;
}
