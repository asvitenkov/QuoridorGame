#include "datautils.h"


bool CPlaygroundLinesData::getPos(unsigned char x, unsigned char y, unsigned int &i, unsigned int &j)
{
    if (x >= LINES_MAX_COUNT || y >= LINE_MAX_LENGHT)
        return false;

    const unsigned int z = x * LINE_MAX_LENGHT + y;

    i = z / PLAYGROUND_LINES_DATA_ITEMS_PER_BYTE;
    j = z % PLAYGROUND_LINES_DATA_ITEMS_PER_BYTE;

    return true;
}

void CPlaygroundLinesData::setRawByteValue(PlaygroundLinesData *data, unsigned int index, unsigned char value)
{
    if (data != 0 && index < PLAYGROUND_LINES_DATA_ARRAY_SIZE)
        data->lines[index] = value;
}

unsigned char CPlaygroundLinesData::rawByteValue(PlaygroundLinesData *data, unsigned int index)
{
    unsigned char value = 0;

    if (data != 0 && index < PLAYGROUND_LINES_DATA_ARRAY_SIZE)
        value = data->lines[index];

    return value;
}

unsigned char CPlaygroundLinesData::mask(unsigned char pos)
{
    unsigned char mask = 0;

    if (pos < PLAYGROUND_LINES_DATA_ITEMS_PER_BYTE)
        mask = (0xFF >> (8 - PLAYGROUND_LINES_ITEM_BIT_SIZE)) << (PLAYGROUND_LINES_ITEM_BIT_SIZE * pos);

    return mask;
}


unsigned char CPlaygroundLinesData::value(PlaygroundLinesData *data, unsigned char x, unsigned char y)
{
    unsigned char value = 0;

    unsigned int i = 0, j = 0;
    bool bRes = getPos(x, y, i, j);

    if (data != 0 && bRes)
    {
        unsigned char itemRawData = rawByteValue(data, i);
        const unsigned char valueByteMask = mask(j);

        itemRawData = itemRawData & valueByteMask;

        itemRawData = itemRawData >> (j * PLAYGROUND_LINES_ITEM_BIT_SIZE);

        value = itemRawData;
    }

    return value;
}


void CPlaygroundLinesData::setValue(PlaygroundLinesData *data, unsigned char x, unsigned char y, unsigned char value)
{
    unsigned int i = 0, j = 0;
    bool bRes = getPos(x, y, i, j);

    if (data != 0 && bRes)
    {
        const unsigned char valueByteMask = mask(j);
        const unsigned char newValueShifted = (value & ~(0xFF << PLAYGROUND_LINES_ITEM_BIT_SIZE)) << (j * PLAYGROUND_LINES_ITEM_BIT_SIZE);

        unsigned char itemRawData = rawByteValue(data, i);

        itemRawData = itemRawData & ~valueByteMask;
        itemRawData = itemRawData | newValueShifted;

        setRawByteValue(data, i, itemRawData);
    }
}
