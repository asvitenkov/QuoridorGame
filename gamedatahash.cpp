#include "gamedatahash.h"

#include "structures.h"

struct GameDataComparator
{
    bool operator()(const GameData* lhs, const GameData* rhs) const
    {
        return memcmp(lhs, rhs, sizeof(GameData)) < 0;
    }
};

typedef std::set<GameData*, GameDataComparator> TGameDataHash;

class CGameDataHashTablePrivate
{
public:
    TGameDataHash m_hash;
};




CGameDataHashTable CGameDataHashTable::m_instance;

CGameDataHashTable::CGameDataHashTable()
    : m_lock(QMutex::NonRecursive)
    , m_hashTable(new CGameDataHashTablePrivate)

{

}


void CGameDataHashTable::insert(GameData *data)
{
    if (data == 0)
        return;

    TGameDataHash &hash = m_hashTable->m_hash;

    hash.insert(data);
}

bool CGameDataHashTable::find(GameData* const &data)
{
    if (data == 0)
        return false;

    const TGameDataHash &hash = m_hashTable->m_hash;

    TGameDataHash::const_iterator it =  hash.find(data);

    return it != hash.end();
}
