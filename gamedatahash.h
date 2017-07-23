#ifndef CGAMEDATAHASH_H
#define CGAMEDATAHASH_H

#include "structures.h"

#include <set>
#include <QMutex>


class CGameDataHashTablePrivate;

//class GameDataComparator;

class CGameDataHashTable
{
public:

    static CGameDataHashTable& instance() { return m_instance; }

    void insert(const GameData *data);
    bool find(GameData * const &data);


private:
    QMutex m_lock;
    CGameDataHashTablePrivate *m_hashTable;

    CGameDataHashTable();


    static CGameDataHashTable m_instance;
};

#endif // CGAMEDATAHASH_H
