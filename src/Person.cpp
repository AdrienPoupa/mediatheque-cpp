//
//  Personne.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Person.hpp"

Person::Person(std::string lastName, std::string firstName) : _lastName(lastName), _firstName(firstName)
{
    Date(1, 1, 1900);
    _id = 0; // No ID for now
}

Person::Person(int id) // Get a person from an ID provided by DB
{
    // TODO: query to get an existing person
}

Person::~Person()
{
    // Nothing for now
}

unsigned int Person::getId()
{
    return _id;
}

std::string Person::getLastName()
{
    return _lastName;
}

std::string Person::getFirstName()
{
    return _firstName;
}

Date Person::getBirthDate()
{
    return _birthDate;
}

void Person::setLastName(std::string lastName)
{
    _lastName = lastName;
}

void Person::setFirstName(std::string firstName)
{
    _firstName = firstName;
}

void Person::setBirthDate(Date birthDate)
{
    _birthDate = birthDate;
}

void Person::addToDB()
{
    // TODO: query INSERT INTO
}

void Person::updateDB()
{
    // TODO: query INSERT INTO
}
