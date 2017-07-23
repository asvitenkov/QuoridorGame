#ifndef GAMEALG_H
#define GAMEALG_H

#include "structures.h"

namespace GameAlg
{
    void processGameStateRec(GameData *gameData, quint64 *totalGamesCount, quint64 *winGamesCount);
}

#endif // GAMEALG_H
