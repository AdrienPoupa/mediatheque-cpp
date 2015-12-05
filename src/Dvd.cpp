#include "Dvd.hpp"

/*
 # Database Model
 
 Table: dvds
 
 Columns:
 - id: INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
 - borrowable: BOOLEAN,
 - title: TEXT NOT NULL,
 - director: INTEGER REFERENCES artists (id),
 - release: DATE,
 - length: INTEGER (10),
 - studio: TEXT,
 - genre1: INTEGER REFERENCES genres (id),
 - genre2: INTEGER REFERENCES genres (id)
 */

Dvd::Dvd()
{
    //ctor
}

Dvd::~Dvd()
{
    //dtor
}

Dvd::Dvd(int id)
{
    //ctor
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
