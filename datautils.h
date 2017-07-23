#ifndef DATAUTILS_H
#define DATAUTILS_H

#include "structures.h"

class CPlaygroundLinesData
{
public:
    //CPlaygroundLinesData(PlaygroundLinesData *data = 0);


    static unsigned char value(PlaygroundLinesData *data, unsigned char x, unsigned char y);
    static void setValue(PlaygroundLinesData *data, unsigned char x, unsigned char y, unsigned char value);


private:
    static bool getPos(unsigned char x, unsigned char y, unsigned int &i, unsigned int &j);
    static void setRawByteValue(PlaygroundLinesData *data, unsigned int index, unsigned char value);
    static unsigned char rawByteValue(PlaygroundLinesData *data, unsigned int index);
    static unsigned char mask(unsigned char valueIndex); // mask for index according to values per byte

    ///
    /// \brief bitValue return item value of passed byte according to items per byte
    /// \param byte
    /// \param itemIndex - value index
    /// \return
    ///
    static unsigned char byteItemValue(unsigned char byte, unsigned char itemIndex);
    static unsigned char setByteItemValue(unsigned char byte, unsigned char itemValue, unsigned char itemIndex);


    //unsigned char m_linesData[PlaygroundLinesDataDefines::LinesCount][PlaygroundLinesDataDefines::LineLength];
};
/////////////////////////////////////////////////////////////////////////////////////////////

class CPlayerData
{
public:
    CPlayerData(PlayerData* data);
private:
    int m_x;
    int m_y;
    size_t m_borderCount;
    FinishPosition m_finishPosition;
};


/////////////////////////////////////////////////////////////////////////////////////////////

//class CPlaygroundData
//{
//public:
//    CPlaygroundData(PlaygroundData *data);
//private:
//    CPlaygroundLinesData m_hLines;
//    CPlaygroundLinesData m_vLines;
//};


/////////////////////////////////////////////////////////////////////////////////////////////

class CGameData
{
public:
    static GameData* createGameDataStructure();
    static GameData* copyGameDataStructure(const GameData *gameData);

private:
};

/////////////////////////////////////////////////////////////////////////////////////////////

#endif // DATAUTILS_H
