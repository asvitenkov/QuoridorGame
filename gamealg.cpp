#include "gamealg.h"

#include "datautilsinl.h"
#include "gamedatahash.h"
#include "searchalg.h"


//delete me only for testing
#include <QMessageBox>
#include "playgroundwidget.h"

namespace GameAlg
{
void processGameStateRec(GameData *gameData, quint64 *totalGamesCount, quint64 *winGamesCount)
{
#ifdef ENABLE_PARAMS_CHECKING
    Q_CHECK_PTR(gameData);
    Q_CHECK_PTR(totalGamesCount);
    Q_CHECK_PTR(winGamesCount);
#endif

    if (CGameDataHashTable::instance().find(gameData))
        return;

    CGameDataHashTable::instance().insert(gameData);


    //delete me only for tests
    //CPlaygroundWidget::showGameStatic(gameData);
//    static size_t count = 0;
//    static size_t max_count = 500000;
//    if (++count >= max_count && (count % 100000 == 0))
//        CPlaygroundWidget::showGameChangesStatic(gameData);

    // only for 4 players game

    std::list<IPlayerAction*> *pActionsPlayer0 = new std::list<IPlayerAction*>();
    GameDataInl::getAvaliablePlayerActions(gameData, 0, *pActionsPlayer0);
    std::list<IPlayerAction*>::iterator itPlayer0 = pActionsPlayer0->begin();

    for (; itPlayer0 != pActionsPlayer0->end(); ++itPlayer0)
    {
        IPlayerAction* itemAction0 = *itPlayer0;

        GameDataInl::doAction(gameData, 0, itemAction0);

        //delete me only for tests
        //CPlaygroundWidget::showGameStatic(gameData);

        if (itemAction0->type >= IPlayerAction::moveTop
                && itemAction0->type <= IPlayerAction::moveRight
                && SearchAlg::isPlayerAtFinishPosition(gameData, 0))
        {
            (*totalGamesCount)++;
            (*winGamesCount)++;
            //GameDataInl::undoAction(gameData, 0, itemAction0);
            //return;
        }
        else
        {
            std::list<IPlayerAction*> *pActionsPlayer1 = new std::list<IPlayerAction*>();
            GameDataInl::getAvaliablePlayerActions(gameData, 1, *pActionsPlayer1);
            std::list<IPlayerAction*>::iterator itPlayer1 = pActionsPlayer1->begin();

            for (; itPlayer1 != pActionsPlayer1->end(); ++itPlayer1)
            {
                IPlayerAction* itemAction1 = *itPlayer1;

                GameDataInl::doAction(gameData, 1, itemAction1);

                //delete me only for tests
                //CPlaygroundWidget::showGameStatic(gameData);

                if (itemAction1->type >= IPlayerAction::moveTop
                        && itemAction1->type <= IPlayerAction::moveRight
                        && SearchAlg::isPlayerAtFinishPosition(gameData, 1))
                {
                    (*totalGamesCount)++;
                    //GameDataInl::undoAction(gameData, 0, itemAction0);
                    //GameDataInl::undoAction(gameData, 1, itemAction1);
                    //return;
                }
                else
                {
                    std::list<IPlayerAction*> *pActionsPlayer2 = new std::list<IPlayerAction*>();
                    GameDataInl::getAvaliablePlayerActions(gameData, 2, *pActionsPlayer2);
                    std::list<IPlayerAction*>::iterator itPlayer2 = pActionsPlayer2->begin();

                    for (; itPlayer2 != pActionsPlayer2->end(); ++itPlayer2)
                    {
                        IPlayerAction* itemAction2 = *itPlayer2;

                        GameDataInl::doAction(gameData, 2, itemAction2);

                        //delete me only for tests
                        //CPlaygroundWidget::showGameStatic(gameData);

                        if (itemAction2->type >= IPlayerAction::moveTop
                                && itemAction2->type <= IPlayerAction::moveRight
                                && SearchAlg::isPlayerAtFinishPosition(gameData, 2))
                        {
                            (*totalGamesCount)++;
                            //GameDataInl::undoAction(gameData, 0, itemAction0);
                            //GameDataInl::undoAction(gameData, 1, itemAction1);
                            //GameDataInl::undoAction(gameData, 2, itemAction2);
                            //return;
                        }
                        else
                        {
                            std::list<IPlayerAction*> *pActionsPlayer3 = new std::list<IPlayerAction*>();
                            GameDataInl::getAvaliablePlayerActions(gameData, 3, *pActionsPlayer3);
                            std::list<IPlayerAction*>::iterator itPlayer3 = pActionsPlayer3->begin();

                            for (; itPlayer3 != pActionsPlayer3->end(); ++itPlayer3)
                            {
                                IPlayerAction* itemAction3 = *itPlayer3;

                                GameDataInl::doAction(gameData, 3, itemAction3);

                                //delete me only for tests
                                //CPlaygroundWidget::showGameStatic(gameData);

                                if (itemAction3->type >= IPlayerAction::moveTop
                                        && itemAction3->type <= IPlayerAction::moveRight
                                        && SearchAlg::isPlayerAtFinishPosition(gameData, 3))
                                {
                                    (*totalGamesCount)++;
                                    //GameDataInl::undoAction(gameData, 0, itemAction0);
                                    //GameDataInl::undoAction(gameData, 1, itemAction1);
                                    //GameDataInl::undoAction(gameData, 2, itemAction2);
                                    //GameDataInl::undoAction(gameData, 3, itemAction3);
                                    //return;
                                }
                                else
                                {
                                    processGameStateRec(gameData, totalGamesCount, winGamesCount);
                                }

                                GameDataInl::undoAction(gameData, 3, itemAction3);
                                delete itemAction3;
                            }

                            delete pActionsPlayer3;
                        }

                        GameDataInl::undoAction(gameData, 2, itemAction2);
                        delete itemAction2;
                    }

                    delete pActionsPlayer2;
                }

                GameDataInl::undoAction(gameData, 1, itemAction1);
                delete itemAction1;
            }

            delete pActionsPlayer1;
        }

        GameDataInl::undoAction(gameData, 0, itemAction0);
        delete itemAction0;
    }

    delete pActionsPlayer0;
}

}
