#include "Cd.h"

Cd::Cd()
{
    //ctor
}

Cd::Cd(int id)
{
    //ctor
}

Cd::~Cd()
{
    //dtor
}

bool Cd::save()
{
    return true;
}

bool Cd::remove()
{
    // If the genre doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbGenre("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbGenre, "DELETE FROM cds WHERE id=?");
        query.bind(1, (int) _id);
        query.exec();

        return true;
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return false;
    }

    return true;
}
