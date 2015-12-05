#include "Dvd.hpp"

Dvd::Dvd()
{
    //ctor
}

Dvd::~Dvd()
{
    //dtor
}

void Dvd::addCasting(Artist* artist)
{
    _casting.insert(artist);
    save();
}

bool Dvd::save()
{
    return true;
}

bool Dvd::remove()
{
    // If the genre doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbGenre("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbGenre, "DELETE FROM dvds WHERE id=?");
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
