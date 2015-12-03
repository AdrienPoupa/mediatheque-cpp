//
//  Genre.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Genre.hpp"

using namespace std;

Genre::Genre(const std::string name) : _name(name)
{

}

Genre::~Genre()
{

}

Genre::Genre(int id)
{
    SQLite::Database    dbGenres("example.db3");

    SQLite::Statement query(dbGenres, "SELECT genre FROM genres WHERE id=?");
    query.bind(1, id);

    while (query.executeStep())
    {
        _id = id;
        _name = query.getColumn(0).getText();
    }
}

int Genre::getId()
{
    return _id;
}

void Genre::setName(const std::string name)
{
    _name = name;
}

std::string Genre::getName() const
{
    return _name;
}

bool Genre::save()
{
    // Update
    if (_id != 0) {
        try
        {
            SQLite::Database    dbGenres("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbGenres, "UPDATE genres SET genre=? WHERE id=?");
            query.bind(1, _name);
            query.bind(2, (int) _id);
            query.exec();

            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }
    // Insert
    else
    {
        try
        {
            SQLite::Database    dbGenres("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbGenres, "INSERT INTO genres VALUES (?, ?)");
            query.bind(2, _name);
            query.exec();

            // Update current ID
            int tmp = dbGenres.execAndGet("SELECT last_insert_rowid();");
            _id = tmp;

            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }

    return true;
}

bool Genre::remove()
{
    // If the genre doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbGenre("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbGenre, "DELETE FROM genres WHERE id=?");
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

ostream& operator<< (ostream& stream, const Genre& genre)
{
    stream << genre._id << ' ' << genre._name << endl;

    return stream;
}

istream& operator>> (istream& stream, Genre& genre)
{
    stream >> genre._name;

    return stream;
}

