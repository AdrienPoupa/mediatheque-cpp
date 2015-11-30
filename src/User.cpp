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
    try
    {
        SQLite::Database    dbPerson("example.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
         // Insert query
        SQLite::Statement   query(dbPerson, "INSERT INTO users VALUES (?, ?, ?, ?, ?, ?, ?)");
        query.bind(2, _firstName);
        query.bind(3, _lastName);
        query.bind(4, _phone);
        query.bind(5, _address.addressDB());
        query.bind(6, _birthDate.dateToDB());
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

bool User::update()
{
    return true;
}

bool User::remove()
{
    return true;
}
