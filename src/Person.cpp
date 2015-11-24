//
//  Personne.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "Person.hpp"

using namespace std;

Person::Person(std::string lastName, std::string firstName) :
    _lastName(lastName), _firstName(firstName)
{
    Date(1, 1, 1900);
    _id = 0; // No ID for now
}

Person::Person(std::string lastName, std::string firstName, Date birthDate) :
    _lastName(lastName), _firstName(firstName), _birthDate(birthDate)
{
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

void Person::setLastName(std::string lastName)
{
    _lastName = lastName;
}

void Person::setFirstName(std::string firstName)
{
    _firstName = firstName;
}

std::string Person::getFirstName()
{
    return _firstName;
}

Date Person::getBirthDate()
{
    return _birthDate;
}

void Person::setBirthDate(Date birthDate)
{
    _birthDate = birthDate;
}

ostream& operator<< (ostream& stream, const Person& person)
{
    cout << person._id << ' ' << person._firstName << ' ' << person._lastName << endl;

    return stream;
}

istream& operator>> (istream& stream, Person& person)
{
    stream >> person._firstName >> person._lastName >> person._birthDate;

    return stream;
}
