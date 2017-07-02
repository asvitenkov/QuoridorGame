#ifndef DATAUTILS_H
#define DATAUTILS_H

#include "structures.h"


class CPlaygroundLinesData
{
public:
    CPlaygroundLinesData(PlaygroundLinesData *data = 0);


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
public:
    static unsigned char byteItemValue(unsigned char byte, unsigned char itemIndex);
    static unsigned char setByteItemValue(unsigned char byte, unsigned char itemValue, unsigned char itemIndex);


    unsigned char m_playground[PLAYGROUND_LINES_MAX_COUNT][PLAYGROUND_LINE_MAX_LENGHT];
};

/////////////////////////////////////////////////////////////////////////////////////////////

class CGameData
{
public:
    static GameData* createGameData();
};

/////////////////////////////////////////////////////////////////////////////////////////////

#endif // DATAUTILS_H
