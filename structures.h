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
    enum { PlayerCount = PLAYER_COUNT };
} PlayerDataDefines;

typedef struct
{
    unsigned char x : 2;
    unsigned char y : 2;
    unsigned char borderCount : 2;
    unsigned char finishPosition : 2;
} PlayerData;

typedef struct
{
    enum
    {
        ArraySize    = PLAYGROUND_LINES_DATA_ARRAY_SIZE,
        LinesCount   = PLAYGROUND_LINES_MAX_COUNT,
        LineLength   = PLAYGROUND_LINE_MAX_LENGHT,
        ItemsPerByte = PLAYGROUND_LINES_DATA_ITEMS_PER_BYTE,
        ItemBitSize  = PLAYGROUND_LINES_ITEM_BIT_SIZE
    };
} PlaygroundLinesDataDefines;

typedef struct
{
    unsigned char lines[PlaygroundLinesDataDefines::ArraySize];
} PlaygroundLinesData;


typedef struct
{
    PlaygroundLinesData vLines;
    PlaygroundLinesData hLines;
} PlaygroundData;



typedef struct
{
    PlaygroundData playground;
    PlayerData players[PlayerDataDefines::PlayerCount]; // First player is main player for processing
} GameData;


#pragma pack(pop)

#endif // STRUCTURES_H

