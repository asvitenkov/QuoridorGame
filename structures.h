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
#define VLINE_END         ((unsigned char) (LINE_END << 4))


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
    unsigned char playground[LINES_MAX_COUNT][LINE_MAX_LENGHT];
    PlayerData players[PLAYER_COUNT]; // First player is main player for processing
} GameData;

#pragma pack(pop)

#endif // STRUCTURES_H

