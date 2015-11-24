//
//  Person.hpp
//  Mediatheque
//
//  Created by Timote on 13/11/2015.
//  Copyright © 2015 Timote. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <iostream>

#include "Date.hpp"

class Person {
private:
    unsigned int _id;
    std::string _lastName;
    std::string _firstName;
    Date _birthDate;
public:
    Person(std::string lastName = "Inconnu", std::string firstName = "Inconnu");
    Person(int id); // Get a person from an ID provided by DB
    virtual ~Person();
    virtual unsigned int getId();
    virtual std::string getLastName();
    virtual std::string getFirstName();
    virtual Date getBirthDate();
    virtual void setLastName(std::string lastName);
    virtual void setFirstName(std::string firstName);
    virtual void setBirthDate(Date birthDate);
    virtual void addToDB();
    virtual void updateDB();
};

#endif /* Person_hpp */
