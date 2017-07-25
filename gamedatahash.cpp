#include "gamedatahash.h"

#include "structures.h"
#include "datautils.h"

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
    ~CGameDataHashTablePrivate()
    {
        TGameDataHash::iterator it = m_hash.begin();

        while (it != m_hash.end())
        {
            delete (*it);
            ++it;
        }
    }

    TGameDataHash m_hash;
};




CGameDataHashTable CGameDataHashTable::m_instance;

CGameDataHashTable::CGameDataHashTable()
    : m_lock(QMutex::NonRecursive)
    , m_hashTable(new CGameDataHashTablePrivate)

{

}

CGameDataHashTable::~CGameDataHashTable()
{
    delete m_hashTable;
}


void CGameDataHashTable::insert(const GameData *data)
{
    if (data == 0)
        return;

    TGameDataHash &hash = m_hashTable->m_hash;

    hash.insert(CGameData::copyGameDataStructure(data));

    //delete me
    if (hash.size() % 10000 == 0)
        qDebug() << "hash size: " << hash.size();
}

bool CGameDataHashTable::find(GameData* const &data)
{
    if (data == 0)
        return false;

    const TGameDataHash &hash = m_hashTable->m_hash;

    TGameDataHash::const_iterator it =  hash.find(data);

    return it != hash.end();
}
