#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "defines.h"

typedef enum{
    FinishPosotionTop       = 0,
    FinishPosotionRight     = 1,
    FinishPosotionTopBottom = 2,
    FinishPosotionTopLeft   = 3,
} FinishPosition;


#pragma pack(push, 1)


typedef struct
{
    unsigned char x : 2;
    unsigned char y : 2;
    unsigned char borderCount : 2;
    unsigned char finishPosition : 2;
} PlayerData;

typedef struct
{
    unsigned char lines[PLAYGROUND_LINES_DATA_ARRAY_SIZE];
} PlaygroundLinesData;

typedef struct
{
    PlaygroundLinesData vLines;
} PlaygroundVLinesData;

typedef struct
{
    PlaygroundLinesData hLines;
} PlaygroundHLinesData;

typedef struct
{
    PlaygroundHLinesData dataHLines;
    PlaygroundVLinesData dataVLines;
    PlayerData players[PLAYER_COUNT]; // First player is main player for processing
} GameData;

#pragma pack(pop)

#endif // STRUCTURES_H

