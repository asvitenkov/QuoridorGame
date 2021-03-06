#ifndef SEARCHALG_H
#define SEARCHALG_H

#include "structures.h"

namespace SearchAlg
{

bool checkFinishRoute(PlaygroundData *data, unsigned char x, unsigned char y, FinishPosition finishPosition);

bool isPlayerAtFinishPosition(const GameData *gameData, uint playerIndex);

void fillMoovmeentsCellsMap(const PlaygroundData *data, unsigned char x, unsigned char y, FinishPosition finishPosition, PlaygroundCellsMap &map);

}



#endif // SEARCHALG_H
