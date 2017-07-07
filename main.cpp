#include <QCoreApplication>

#include <QBitArray>
#include <QTime>
#include "structures.h"
#include "datautils.h"
#include "iostream"

#include "gamedatahash.h"
#include "datautilsinl.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GameData *game = CGameData::createGameDataStructure();

    std::list<PlayerActionAdd*> actions;

    PlaygroundDataInl::getAvaliableBorderActions(&game->playground, actions);


    return 0;
}
