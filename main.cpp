#include <QCoreApplication>

#include <QBitArray>
#include "structures.h"
#include "datautils.h"
#include "iostream"

#include "gamedatahash.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    GameData* data = CGameData::createGameDataStructure();

    CPlaygroundLinesData::setValue(&data->playground.hLines, 0, 0, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 0, 1, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 0, 2, 1);


    CPlaygroundLinesData::setValue(&data->playground.hLines, 3, 0, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 3, 4, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 3, 5, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 3, 6, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 3, 8, 1);



    CPlaygroundLinesData::setValue(&data->playground.hLines, 6, 0, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 6, 1, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 6, 6, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 6, 7, 1);
    CPlaygroundLinesData::setValue(&data->playground.hLines, 6, 8, 1);

    CPlaygroundLinesData pData(&data->playground.hLines);



    return 0;
}
