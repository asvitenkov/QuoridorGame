#ifndef STRUCTURES_H
#define STRUCTURES_H


#define LINES_MAX_COUNT   7
#define LINE_MAX_LENGHT   9
#define PLAYER_COUNT      4

#define LINE_BEGIN
#define LINE_END

#define HLINE_BEGIN       LINE_BEGIN
#define HLINE_END         LINE_END
#define VLINE_BEGIN       ((unsigned char) (LINE_BEGIN << 4))
#define VLINE_BEGIN       ((unsigned char) (LINE_END << 4))


typedef enum{
    FinishPosotionTop       = 0,
    FinishPosotionRight     = 1,
    FinishPosotionTopBottom = 2,
    FinishPosotionTopLeft   = 3,
} FinishPosition;


#pragma pack(push, 1)

typedef struct
{
    unsigned x : 4;
    unsigned y : 4;
    unsigned borderCount : 4;
    unsigned finishPosition : 2;
} PlayerData;

typedef struct
{
    unsigned char playground[LINES_MAX_COUNT][LINE_MAX_LENGHT];
    PlayerData players[PLAYER_COUNT];
} GameData;

#pragma pack(pop)

#endif // STRUCTURES_H

