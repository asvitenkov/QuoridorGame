#include <QCoreApplication>

#include "structures.h"
#include "iostream"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << sizeof(PlayerData) << std::endl;
    std::cout << sizeof(GameData);

    //return a.exec();

    return 0;
}
