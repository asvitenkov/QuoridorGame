#ifndef DATAUTILS_H
#define DATAUTILS_H

#include "structures.h"



class CPlaygroundLinesData
{
public:
    static unsigned char value(PlaygroundLinesData *data, unsigned char x, unsigned char y);
    static void setValue(PlaygroundLinesData *data, unsigned char x, unsigned char y, unsigned char value);


private:
    static bool getPos(unsigned char x, unsigned char y, unsigned int &i, unsigned int &j);
    static void setRawByteValue(PlaygroundLinesData *data, unsigned int index, unsigned char value);
    static unsigned char rawByteValue(PlaygroundLinesData *data, unsigned int index);
    static unsigned char mask(unsigned char pos);

};



#endif // DATAUTILS_H
