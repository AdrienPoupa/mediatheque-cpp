//
//  Artist.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//
#include <iostream>

#include "Artist.hpp"

using namespace std;

Artist::Artist(const std::string& firstName, const std::string& lastName, const std::string& nationality) :
    Person(firstName, lastName), _nationality(nationality)
{
    // empty
}

Artist::Artist(int id) // Get a person from an ID provided by DB
{
    SQLite::Database    dbArtist("example.db3");

    SQLite::Statement query(dbArtist, "SELECT name, surname, birthdate, nationality FROM artists WHERE id=?");
    query.bind(1, id);

    while (query.executeStep())
    {
        _id = id;
        _firstName = query.getColumn(0).getText();
        _lastName = query.getColumn(1).getText();
        string birthDateTmp = query.getColumn(2).getText();
        Date newDate(birthDateTmp);
        _birthDate = newDate;
        _nationality = query.getColumn(3).getText();
    }
}

std::string Artist::getNationality() const
{
    return _nationality;
}

void Artist::setNationality(const std::string& nationality)
{
    _nationality = nationality;
}

std::set<Article*> Artist::getArticles() const
{
    return _articles;
}


void addArticles(const Article& article, const Position& position){
    
}

void removeArticles(const Article& article)
{
    // TODO
}


std::ostream& operator<<(std::ostream& os, const Artist& me)
{
    os << me._firstName << " " << me._lastName <<" (" << me._nationality << "), ne(e) le " << me.getBirthDate() << endl;
    return os;
}

std::istream& operator>>(std::istream& is, Artist& me)
{
    cout << "Saisie d'un artiste: " << endl;
    cout << " - prenom : ";
    is >> me._firstName;
    cout << " - nom : ";
    is >> me._lastName;
    cout << " - nationalite : ";
    is >> me._nationality;
    cout << " - date de naissance : ";
    is >> me._birthDate;

    return is;
}

// DB method
bool Artist::save()
{
    // Update
    if (_id != 0) {
        try
        {
            SQLite::Database    dbArtist("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbArtist, "UPDATE artists SET name=?, surname=?, birthdate=?, nationality=? WHERE id=?");
            query.bind(1, _firstName);
            query.bind(2, _lastName);
            query.bind(3, _birthDate.dateToDB());
            query.bind(4, _nationality);
            query.bind(5, (int) _id);
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
            SQLite::Database    dbArtist("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbArtist, "INSERT INTO artists VALUES (?, ?, ?, ?, ?, ?)");
            query.bind(2, _firstName);
            query.bind(3, _lastName);
            query.bind(4, _birthDate.dateToDB());
            query.bind(5, _nationality);
            query.exec();

            // Update current ID
            int tmp = dbArtist.execAndGet("SELECT last_insert_rowid();");
            _id = tmp;

            return true;
        }
        catch (std::exception& e)
        {
            std::cout << "SQLite exception: " << e.what() << std::endl;
            return false;
        }
    }

bool Artist::remove()
{
    // If the genre doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbArtist("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbArtist, "DELETE FROM artists WHERE id=?");
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

Artist::~Artist()
{

}


