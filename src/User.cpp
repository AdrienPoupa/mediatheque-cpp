//
//  User.cpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#include "User.hpp"

User::User(std::string firstName, std::string lastName, Date birthDate) :
    Person(firstName, lastName, birthDate)
{

}

User::~User()
{

}

bool User::insertPerson()
{
    return true;
}

bool User::updatePerson()
{
    return true;
}

bool User::deletePerson()
{
    return true;
}
