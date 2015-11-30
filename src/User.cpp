//
//  User.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "User.hpp"

using namespace std;

User::User(std::string firstName, std::string lastName, Date birthDate, string phone) :
    Person(firstName, lastName, birthDate), _phone(phone)
{

}

User::User(int id) // Get a person from an ID provided by DB
{
    SQLite::Database    dbUser("example.db3");

    SQLite::Statement query(dbUser, "SELECT name, surname, phone, address, birthdate FROM users WHERE id=?");
    query.bind(1, id);

    while (query.executeStep())
    {
        _id = id;
        _firstName = query.getColumn(0).getText();
        _lastName = query.getColumn(1).getText();
        _phone = query.getColumn(2).getText();
        string addressTmp = query.getColumn(3).getText();
        //_address = "to do";
        string birthDateTmp = query.getColumn(4).getText();
        Date newDate(birthDateTmp);
        _birthDate = newDate;
    }
}

User::~User()
{

}

string User::getPhone()
{
    return _phone;
}

void User::setPhone(string phone)
{
    _phone = phone;
}

Address User::getAddress()
{
    return _address;
}

void User::setAddress(Address address)
{
    _address = address;
}

bool User::save()
{
    // Update
    if (_id != 0) {
        try
        {
            SQLite::Database    dbUser("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbUser, "UPDATE users SET name=?, surname=?, phone=?, address=?, birthdate=? WHERE id=?");
            query.bind(1, _firstName);
            query.bind(2, _lastName);
            query.bind(3, _phone);
            query.bind(4, _address.addressDB());
            query.bind(5, _birthDate.dateToDB());
            query.bind(6, (int) _id);
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
            SQLite::Database    dbUser("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
             // Insert query
            SQLite::Statement   query(dbUser, "INSERT INTO users VALUES (?, ?, ?, ?, ?, ?, ?)");
            query.bind(2, _firstName);
            query.bind(3, _lastName);
            query.bind(4, _phone);
            query.bind(5, _address.addressDB());
            query.bind(6, _birthDate.dateToDB());
            query.exec();

            // Update current ID
            int tmp = dbUser.execAndGet("SELECT last_insert_rowid();");
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

bool User::remove()
{
    // If the user doesn't exist yet, we can't remove it
    if (_id == 0) {
        return false;
    }

    try
    {
        SQLite::Database    dbUser("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Delete query
        SQLite::Statement   query(dbUser, "DELETE FROM users WHERE id=?");
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
